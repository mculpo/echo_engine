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
#include <component/RendererPrimitiveMesh.h>
#include <component/RendererModelMesh.h>

#include <core/Input.h>
#include <core/Mouse.h>
#include <core/Time.h>
#include <core/Vertex.h>
#include <core/Random.h>
#include <core/FileSystem.h>


namespace openge {
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = WIDTH / 2.0;
	float lastY = HEIGHT / 2.0;

	void create_lights() {
		ref<Shader> shaderLight = createRef<Shader>("resources/shaders/light.vertex", "resources/shaders/light.frag");
		ref<Camera> camera = EntityManager::getInstance().getMainCamera()->getComponent<Camera>();
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
			ref<Renderer> rendererLight = createRef<RendererPrimitiveMesh>();
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
			ref<Renderer> rendererLight = createRef<RendererPrimitiveMesh>();
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
				ref<Renderer> rendererLight = createRef<RendererPrimitiveMesh>();
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

	ref<GameObject> create_camera(float width, float height) {
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
		return mainCamera;
	}

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
	}

	Engine::~Engine()
	{
		glfwTerminate();
	}

	void Engine::run()
	{

		ref<GameObject> mainCamera = create_camera(width, height);
		ref<Camera> camera = mainCamera->getComponent<Camera>();
		std::vector<ref<GameObject>> cubos;

		stbi_set_flip_vertically_on_load(true);
		create_lights();
		/*
		*	Configuração dos Cubos de Exemplo que vai ser iluminado
		*/
		{
			// positions all containers
			std::vector<Vector3> cubePositions;

			const int totalNewPositions = 10;
			const float range = 3.0f;

			for (int i = 0; i < totalNewPositions; ++i) {
				float x = Random::Range(-range, range);
				float y = Random::Range(-range, range);
				float z = Random::Range(-range, range);
				Vector3 newPosition(x, y, z);

				// Add the new position to the vector
				cubePositions.push_back(newPosition);
			}


			//ref<Model> modelo = createRef<Model>(FileSystem::path("resources/models/backpack/backpack.obj"));
			ref<Shader> shaderReceptorLight = createRef<Shader>("resources/shaders/uniform.vertex", "resources/shaders/uniform.frag");
			ref<Texture> textureDiffuse = createRef<Texture>("resources/texture/Crystal-diffuse.jpg", TextureType::Diffuse);
			textureDiffuse->SetName("diffuse");
			unsigned int textureDiffuseIndex;

			TextureManager::getInstance().add(textureDiffuse, textureDiffuseIndex);
			//Texture diffuse("resources/texture/Crystal-diffuse.jpg", TextureType::Diffuse);
			//Texture specular("resources/texture/Crystal-spec.jpg", TextureType::Specular);
			Mesh meshCubo;
			std::vector<unsigned int> array_index = { textureDiffuseIndex };
			meshCubo.setVertices(ShapeVerticesManager::getInstance().getCubeVertices());
			meshCubo.setTextures(array_index);
			meshCubo.setup();
			for (unsigned int i = 0; i < cubePositions.size(); i++) {

				ref<GameObject> cubo = createRef<GameObject>(i, "cubo", "cubo");
				
				ref<Material> materialCubo = createRef<Material>();
				ref<Renderer> rendererCubo = createRef<RendererPrimitiveMesh>();
				ref<Transform> transformCubo = createRef<Transform>(
					Vector3(cubePositions[i]),
					Vector3(1.0f),
					Vector3(0.0f)
				);
				//
				materialCubo->setShader(shaderReceptorLight);

				rendererCubo->setMaterial(materialCubo);
				rendererCubo->setTransform(transformCubo);
				rendererCubo->setMainCamera(camera);
				rendererCubo->addMesh(meshCubo);
				//rendererCubo->setMeshs(modelo->m_meshs);

				cubo->addComponent<Transform>(transformCubo);
				cubo->addComponent<Renderer>(rendererCubo);
				cubo->setTransform(transformCubo);
				cubo->setRenderer(rendererCubo);
				EntityManager::getInstance().addEntity<GameObject>(cubo);

				cubos.push_back(cubo);
			}
		}

		Vector3 _directionCamera = camera->getFront();
		Vector3 _postitionCamera = mainCamera->getComponent<Transform>()->getPosition();
		std::vector<ref<GameObject>> lights = EntityManager::getInstance().findGameObjectsByTag<GameObject>("light");

		while (!glfwWindowShouldClose(m_window)) {

			Time::updateDeltaTime();
			Mouse::getInstance().update();
			mouse_input(mainCamera, width, height, m_window);

			GLclampf Red = 0.1f, Green = 0.1f, Blue = 0.1f, Alpha = 0.0f;
			glClearColor(Red, Green, Blue, Alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ref<Light> dirLight;
			ref<Light> spotLight;
			std::vector<ref<Light>> pointLight;

			/**
			* Configuration and registers all lights in scene
			*/
			{

				for (const auto& gameObject : lights) {
					ref<Light> lightComponent = gameObject->getComponent<Light>();

					if (lightComponent && lightComponent->getLightType() == LightType::Point) {
						pointLight.push_back(lightComponent);
					}
					else if (lightComponent && lightComponent->getLightType() == LightType::Spot) {
						spotLight = lightComponent;
					}
					else if (lightComponent && lightComponent->getLightType() == LightType::Directional) {
						dirLight = lightComponent;
					}
				}
			}
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
					/*
					// material properties
					shaderCubo->setUniform3fv("viewPos", _postitionCamera);
					shaderCubo->setUniform1i("numPointLights", pointLight.size());

					shaderCubo->setUniform1f("material.shininess", 32.0f);

					// shader directional
					shaderCubo->setUniform3fv("dirLight.direction", dirLight->getDirection());
					shaderCubo->setUniform3fv("dirLight.ambient", dirLight->getAmbient());
					shaderCubo->setUniform3fv("dirLight.diffuse", dirLight->getDiffuse());
					shaderCubo->setUniform3fv("dirLight.specular", dirLight->getSpecular());
					shaderCubo->setUniform3fv("dirLight.color", dirLight->getColor());

					// shader spot
					shaderCubo->setUniform3fv("spotLight.position", _postitionCamera);
					shaderCubo->setUniform3fv("spotLight.direction", _directionCamera);
					shaderCubo->setUniform3fv("spotLight.ambient", spotLight->getAmbient());
					shaderCubo->setUniform3fv("spotLight.diffuse", spotLight->getDiffuse());
					shaderCubo->setUniform3fv("spotLight.specular", spotLight->getSpecular());
					shaderCubo->setUniform1f("spotLight.constant", spotLight->getConstant());
					shaderCubo->setUniform1f("spotLight.linear", spotLight->getLinear());
					shaderCubo->setUniform1f("spotLight.quadratic", spotLight->getQuadratic());
					shaderCubo->setUniform1f("spotLight.cutOff", spotLight->getCutOff());
					shaderCubo->setUniform1f("spotLight.outerCutOff", spotLight->getOuterCutOff());
					shaderCubo->setUniform3fv("spotLight.color", spotLight->getColor());

					// shader point
					for (unsigned int i = 0; i < pointLight.size(); i++) {

						shaderCubo->setUniform3fv("pointLights[" + std::to_string(i) + "].position", pointLight[i]->getPosition());
						shaderCubo->setUniform3fv("pointLights[" + std::to_string(i) + "].ambient", pointLight[i]->getAmbient());
						shaderCubo->setUniform3fv("pointLights[" + std::to_string(i) + "].diffuse", pointLight[i]->getDiffuse());
						shaderCubo->setUniform3fv("pointLights[" + std::to_string(i) + "].specular", pointLight[i]->getSpecular());
						shaderCubo->setUniform1f("pointLights[" + std::to_string(i) + "].constant", pointLight[i]->getConstant());
						shaderCubo->setUniform1f("pointLights[" + std::to_string(i) + "].linear", pointLight[i]->getLinear());
						shaderCubo->setUniform1f("pointLights[" + std::to_string(i) + "].quadratic", pointLight[i]->getQuadratic());
						shaderCubo->setUniform3fv("pointLights[" + std::to_string(i) + "].color", pointLight[i]->getColor());
					}
					*/
					//Matrix3 transpose = cuboTransform->getTransposeMatrix();
					//shaderCubo->setUniformMatrix3fv("modelTranspose", transpose);
					cuboTransform->rotate(Vector3(0.0f, -0.5f, 0.0f) * (float)(Time::deltaTime()));

					cuboRenderer->bind();
					cuboRenderer->render();
				}
			}

			/**
			* Renderer Light's GameObject
			
			{
				for (unsigned int i = 0; i < lights.size(); i++) {
					ref<Renderer> lightRenderer = lights[i]->getComponent<Renderer>();
					ref<Shader> shader = lightRenderer->getMaterial()->getShader();
					shader->Bind();
					shader->setUniform3f("color", 1.0f, 1.0f, 1.0f);
					lightRenderer->bind();
					lightRenderer->render();
				}
			}*/

			// Exibe o FPS e o MS no console
			Time::toStringFpsAndMs();
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}
}


