#include <Engine.h>

#include <gl/VertexArrayObject.h>
#include <gl/VertexBufferObject.h>
#include <gl/ElementBufferObject.h>

#include <base/Mesh.h>
#include <base/Material.h>
#include <base/Shader.h>
#include <base/Texture.h>
#include <base/Model.h>

#include <entity/GameObject.h>

#include <manager/EntityManager.h>
#include <manager/ShapeVerticesManager.h>

#include <component/Camera.h>
#include <component/Transform.h>
#include <component/Light.h>
#include <component/Renderer.h>
#include <component/RendererCube.h>
#include <component/RendererModel.h>

#include <core/Input.h>
#include <core/Mouse.h>
#include <core/Time.h>
#include <core/Vertex.h>
#include <core/Random.h>
#include <core/FileSystem.h>
#include <component/RendererPlane.h>
#include <base/FrameBufferTexture.h>


namespace openge {
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = WIDTH / 2.0;
	float lastY = HEIGHT / 2.0;

	void mouse_input(ref<GameObject> mainCamera, float width, float height, GLFWwindow* m_window) {
		//Input Mouse and Keyboard
		{
			ref<Camera> camera = mainCamera->getComponent<Camera>();
			ref<Transform> cameraTranform = mainCamera->getComponent<Transform>();

			if (firstMouse)
			{
				lastX = width / 2.0;
				lastY = height / 2.0;
				firstMouse = false;
			}

			float xpos = Mouse::getInstance().getX();
			float ypos = Mouse::getInstance().getY();

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
			lastX = xpos;
			lastY = ypos;

			float sensitivity = 0.1f; // change this value to your liking
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			// make sure that when pitch is out of bounds, screen doesn't get flipped
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 front;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			camera->setFront(glm::normalize(front));

			if (Input::IsKeyPressed(KEYCODE_ESCAPE))
				glfwSetWindowShouldClose(m_window, true);

			float cameraSpeed = static_cast<float>(5 * Time::deltaTime());

			if (Input::IsKeyHeld(KEYCODE_W))
				cameraTranform->translate(cameraSpeed * camera->getFront());
			if (Input::IsKeyHeld(KEYCODE_S))
				cameraTranform->translate(-(cameraSpeed * camera->getFront()));
			if (Input::IsKeyHeld(KEYCODE_A))
				cameraTranform->translate(-glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * cameraSpeed);
			if (Input::IsKeyHeld(KEYCODE_D))
				cameraTranform->translate(glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * cameraSpeed);
		}
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	Engine::Engine(float width, float height, const char* title, bool fullWidth) : width(width), height(height)
	{
		if (glfwInit()) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			m_window = glfwCreateWindow(width, height, title, fullWidth ? glfwGetPrimaryMonitor() : NULL, NULL);
			if (!m_window) {
				glfwTerminate();
			}
		}
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		// Criar uma instância da classe Mouse
		Mouse::getInstance().setWindow(m_window);
		// tell GLFW to capture our mouse
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// configure global opengl state
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		//https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		//https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		/*
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);*/
	}

	Engine::~Engine()
	{
		glfwTerminate();
	}

	void Engine::run()
	{
		initializeCamera();
		ref<GameObject> mainCamera = EntityManager::getInstance().getMainCamera<GameObject>();
		ref<Camera> camera = mainCamera->getComponent<Camera>();
		
		stbi_set_flip_vertically_on_load(true);
		initializeObjects();
		ref<FrameBufferTexture> framebuffer = initializeFrameBuffer();
		
		Vector3 _directionCamera = camera->getFront();
		Vector3 _postitionCamera = mainCamera->getComponent<Transform>()->getPosition();
		std::vector<ref<GameObject>> cubos = EntityManager::getInstance().findGameObjectsByTag<GameObject>("cubo");

		while (!glfwWindowShouldClose(m_window)) {

			Time::updateDeltaTime();
			Mouse::getInstance().update();
			mouse_input(mainCamera, width, height, m_window);

			framebuffer->Bind();
			glEnable(GL_DEPTH_TEST);

			GLclampf Red = 0.5f, Green = 0.5f, Blue = 0.5f, Alpha = 0.0f;
			glClearColor(Red, Green, Blue, Alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/**
			* Renderer Box's GameObject
			*/
			{
				for (unsigned int i = 0; i < cubos.size(); i++) {
					ref<GameObject> cubo = cubos[i];
					ref<Renderer> cuboRenderer = cubo->getRenderer();
					ref<Transform> cuboTransform = cubo->getTransform();
					ref<Shader> shaderCubo = cuboRenderer->getMaterial()->getShader();
					shaderCubo->Bind();
					cuboTransform->rotate(Vector3(0.0f, -0.5f, 0.0f) * (float)(Time::deltaTime()));

					cuboRenderer->bind();
					cuboRenderer->render();
				}
			}

			framebuffer->Draw();
			Time::toStringFpsAndMs();
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

	void Engine::initializeObjects()
	{
		ref<Camera> camera = EntityManager::getInstance().getMainCamera<GameObject>()->getComponent<Camera>();
		ref<Shader> shader = createRef<Shader>(
			"resources/shaders/uniform/uniform.vertex",
			"resources/shaders/uniform/uniform.frag"
		);	

		ref<Texture> crystal = createRef<Texture>(
			FileSystem::path("resources/texture/Crystal-diffuse.jpg"),
			TextureType::Diffuse,
			"diffuse",
			false
		);

		unsigned int crystalIndex;

		TextureManager::getInstance().add(crystal, crystalIndex);

		/*
		*	Configuração dos Cubos com Container2
		*/
		{
			// positions all containers
			std::vector<Vector3> vegetation;

			const int totalNewPositions = 500;
			const float range = 5.0f;

			for (int i = 0; i < totalNewPositions; ++i) {
				float x = Random::Range(-range, range);
				float y = Random::Range(-range, range);
				float z = Random::Range(-range, range);
				Vector3 newPosition(x, y, z);

				vegetation.push_back(newPosition);
			}

			std::vector<unsigned int> grass_index = { crystalIndex };

			ref<Material> materialCubo = createRef<Material>();
			Mesh meshCubo;
			meshCubo.setVertices(ShapeVerticesManager::getInstance().getCubeVertices());
			meshCubo.setTextures(grass_index);
			meshCubo.setup();

			materialCubo->setShader(shader);

			for (unsigned int i = 0; i < vegetation.size(); i++) {

				ref<GameObject> cubo = createRef<GameObject>(i, "cubo", "cubo");
				ref<Renderer> rendererCubo = createRef<RendererCube>();
				ref<Transform> transformCubo = createRef<Transform>(
					Vector3(vegetation[i]),
					Vector3(1.0f),
					Vector3(vegetation[i])
				);
				
				rendererCubo->setMaterial(materialCubo);
				rendererCubo->setTransform(transformCubo);
				rendererCubo->setMainCamera(camera);
				rendererCubo->addMesh(meshCubo);

				cubo->addComponent<Transform>(transformCubo);
				cubo->addComponent<Renderer>(rendererCubo);
				cubo->setTransform(transformCubo);
				cubo->setRenderer(rendererCubo);
				EntityManager::getInstance().addEntity<GameObject>(cubo);
			}
		}
		/*
		*	Configuração do Model
		*/
		/*
		{
			// positions all containers
			std::vector<Vector3> cubePositions;

			const int totalNewPositions = 1;
			const float range = 5.0f;

			for (int i = 0; i < totalNewPositions; ++i) {
				float x = Random::Range(-range, range);
				float y = Random::Range(-range, range);
				float z = Random::Range(-range, range);
				Vector3 newPosition(x, y, z);

				cubePositions.push_back(newPosition);
			}

			std::vector<unsigned int> array_index = { textureDiffuseIndex };
			std::vector<unsigned int> array_index_1 = {  textureContainer2DiffuseIndex };

			ref<Model> ourModel = createRef<Model>(FileSystem::path("resources/models/M4A1/M4A1.obj"));

			for (Mesh& mesh : ourModel->m_meshs) {
				mesh.setTextures(Random::Range(0, 10) > 5 ? array_index : array_index_1);
			}

			for (unsigned int i = 0; i < cubePositions.size(); i++) {

				ref<GameObject> cubo = createRef<GameObject>(i, "cubo", "cubo");

				ref<Material> materialCubo = createRef<Material>();
				ref<Renderer> rendererCubo = createRef<RendererModel>();
				ref<Transform> transformCubo = createRef<Transform>(
					Vector3(cubePositions[i]),
					Vector3(.5f),
					Vector3(0.0f)
				);
				//
				materialCubo->setShader(shader);

				rendererCubo->setMaterial(materialCubo);
				rendererCubo->setTransform(transformCubo);
				rendererCubo->setMainCamera(camera);
				rendererCubo->setMeshs(ourModel->m_meshs);

				cubo->addComponent<Transform>(transformCubo);
				cubo->addComponent<Renderer>(rendererCubo);
				cubo->setTransform(transformCubo);
				cubo->setRenderer(rendererCubo);
				EntityManager::getInstance().addEntity<GameObject>(cubo);
			}
		}
		*/
	}

	ref<FrameBufferTexture> Engine::initializeFrameBuffer()
	{
		ref<Shader> shaderFrameBuffer = createRef<Shader>(
			"resources/shaders/framebuffer/framebuffer.vertex",
			"resources/shaders/framebuffer/framebuffer.frag"
			);

		ref<FrameBufferTexture> framebuffer = createRef<FrameBufferTexture>();
		framebuffer->setShader(shaderFrameBuffer);
		return framebuffer;
	}

	void Engine::initializeSkybox()
	{
	}

	void Engine::initializeLights()
	{
		ref<Shader> shaderLight = createRef<Shader>("resources/shaders/light.vertex", "resources/shaders/light.frag");
		ref<Camera> camera = EntityManager::getInstance().getMainCamera<GameObject>()->getComponent<Camera>();
		std::vector<Vertex> vertices = ShapeVerticesManager::getInstance().getCubeVertices();
		/*
		* Directional Light Configuration
		*/
		{
			ref<GameObject> light = createRef<GameObject>(1, "light", "light");
			ref<Light> dirLight = createRef<Light>(LightType::Directional);

			dirLight->setDirection(Vector3(-0.2f, -1.0f, -0.3f));
			dirLight->setAmbient(Vector3(0.05f, 0.05f, 0.05f));
			dirLight->setDiffuse(Vector3(0.4f, 0.4f, 0.4f));
			dirLight->setSpecular(Vector3(0.5f, 0.5f, 0.5f));
			dirLight->setColor(Vector3(1.0f, 1.0f, 1.0f));

			Mesh meshLight;
			ref<Material> materialLight = createRef<Material>();
			ref<Renderer> rendererLight = createRef<RendererCube>();
			ref<Transform> transformLight = createRef<Transform>(Vector3(0.7f, 0.2f, 2.0f), Vector3(0.2f), Vector3(0.0f));

			meshLight.setVertices(vertices);
			meshLight.setup();

			materialLight->setShader(shaderLight);

			rendererLight->setMaterial(materialLight);
			rendererLight->setTransform(transformLight);
			rendererLight->setMainCamera(camera);
			rendererLight->addMesh(meshLight);

			light->addComponent<Transform>(transformLight);
			light->addComponent<Light>(dirLight);
			light->addComponent<Renderer>(rendererLight);
			EntityManager::getInstance().addEntity<GameObject>(light);
		}

		/*
		* SpotLight Configuration
		*/
		{
			ref<GameObject> light = createRef<GameObject>(1, "light", "light");
			ref<Light> spotLight = createRef<Light>(LightType::Spot);

			Mesh meshLight;
			ref<Material> materialLight = createRef<Material>();
			ref<Renderer> rendererLight = createRef<RendererCube>();
			ref<Transform> transformLight = createRef<Transform>(Vector3(0.0f, 0.0f, -3.0f), Vector3(0.2f), Vector3(0.0f));

			spotLight->setAmbient(Vector3(0.0f, 0.0f, 0.0f));
			spotLight->setDiffuse(Vector3(1.0f, 1.0f, 1.0f));
			spotLight->setSpecular(Vector3(1.0f, 1.0f, 1.0f));
			spotLight->setConstant(1.0f);
			spotLight->setLinear(0.09f);
			spotLight->setQuadratic(0.032f);
			spotLight->setCutOff(glm::cos(glm::radians(0.0f)));
			spotLight->setOuterCutOff(glm::cos(glm::radians(0.0f)));
			spotLight->setColor(Vector3(1.0f, 1.0f, 1.0f));


			meshLight.setVertices(vertices);
			meshLight.setup();

			materialLight->setShader(shaderLight);

			rendererLight->setMaterial(materialLight);
			rendererLight->setTransform(transformLight);
			rendererLight->setMainCamera(camera);
			rendererLight->addMesh(meshLight);

			light->addComponent<Transform>(transformLight);
			light->addComponent<Light>(spotLight);
			light->addComponent<Renderer>(rendererLight);
			EntityManager::getInstance().addEntity<GameObject>(light);
		}

		/**
		* PointLights Configuration ( Four Lights )
		*/
		{

			std::vector<Vector3> pointLightPositions = {
					   Vector3(0.7f,  0.2f,  2.0f),
					   Vector3(2.3f, -3.3f, -4.0f),
					   Vector3(-4.0f,  2.0f, -12.0f),
					   Vector3(0.0f,  0.0f, -3.0f)
			};

			for (unsigned int i = 0; i < pointLightPositions.size(); i++) {
				ref<GameObject> light = createRef<GameObject>(1, "light", "light");
				ref<Light> pointLight = createRef<Light>(LightType::Point);

				Mesh meshLight;
				ref<Material> materialLight = createRef<Material>();
				ref<Renderer> rendererLight = createRef<RendererCube>();
				ref<Transform> transformLight = createRef<Transform>(pointLightPositions[i], Vector3(0.2f), Vector3(0.0f));

				pointLight->setPosition(pointLightPositions[i]);
				pointLight->setAmbient(Vector3(0.05f, 0.05f, 0.05f));
				pointLight->setDiffuse(Vector3(0.8f, 0.8f, 0.8f));
				pointLight->setSpecular(Vector3(1.0f, 1.0f, 1.0f));
				pointLight->setConstant(1.0f);
				pointLight->setLinear(0.09f);
				pointLight->setQuadratic(0.032f);
				pointLight->setColor(Vector3(1.0f, 1.0f, 1.0f));

				meshLight.setVertices(vertices);
				meshLight.setup();

				materialLight->setShader(shaderLight);

				rendererLight->setMaterial(materialLight);
				rendererLight->setTransform(transformLight);
				rendererLight->setMainCamera(camera);
				rendererLight->addMesh(meshLight);

				light->addComponent<Transform>(transformLight);
				light->addComponent<Light>(pointLight);
				light->addComponent<Renderer>(rendererLight);
				EntityManager::getInstance().addEntity<GameObject>(light);
			}
		}
	}

	void Engine::initializeCamera()
	{
		ref<GameObject> mainCamera = createRef<GameObject>(0, "MainCamera", "MainCamera");

		ref<Camera> camera = createRef<Camera>();
		camera->setCameraType(CameraType::Perpective);
		camera->setAspectRatio(width / height);
		camera->setFov(45.0f);
		camera->setFront(Vector3(0.0f, 0.0f, -1.0f));
		camera->setUp(Vector3(0.0f, 1.0f, 0.0f));
		camera->setFarPlane(100.0f);
		camera->setNearPlane(0.1f);

		ref<Transform> transformCamera = createRef <Transform>(
			Vector3(0.0f, 0.0f, 3.0f),
			Vector3(1.0f),
			Vector3(0.0f)
		);

		mainCamera->addComponent<Camera>(camera);
		mainCamera->addComponent<Transform>(transformCamera);
		EntityManager::getInstance().addEntity<GameObject>(mainCamera);
		EntityManager::getInstance().setMainCamera(mainCamera);
	}
}


