#include "Engine.h"
#include <Core/tspch.h>

#include <Renderer/VertexArrayObject.h>
#include <Renderer/VertexBufferObject.h>
#include <Renderer/Texture.h>
#include <Renderer/ElementBufferObject.h>
#include <Renderer/Renderer.h>
#include <Renderer/Camera.h>
#include <Renderer/Shader.h>

#include <Entity/GameObject.h>
#include <Entity/EntityManager.h>

#include <Component/Mesh.h>
#include <Component/Material.h>
#include <Component/Transform.h>

#include <Core/Input.h>
#include <Core/Mouse.h>
#include <Core/Time.h>
#include <Core/Vertex.h>
#include <Core/Random.h>


namespace openge {

	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;

	void mouse_input(ref<GameObject> mainCamera, float width, float height, GLFWwindow* m_window) {
		//Input Mouse and Keyboard
		{
			ref<Camera> camera = mainCamera->getComponent<Camera>();
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

			float cameraSpeed = static_cast<float>(2.5 * Time::getInstance().deltaTime());
			if (Input::IsKeyHeld(KEYCODE_W))
				mainCamera->getComponent<Transform>()->translate(cameraSpeed * mainCamera->getComponent<Camera>()->getFront());
			if (Input::IsKeyHeld(KEYCODE_S))
				mainCamera->getComponent<Transform>()->translate(-(cameraSpeed * mainCamera->getComponent<Camera>()->getFront()));
			if (Input::IsKeyHeld(KEYCODE_A))
				mainCamera->getComponent<Transform>()->translate(-glm::normalize(glm::cross(mainCamera->getComponent<Camera>()->getFront(), mainCamera->getComponent<Camera>()->getUp())) * cameraSpeed);
			if (Input::IsKeyHeld(KEYCODE_D))
				mainCamera->getComponent<Transform>()->translate(glm::normalize(glm::cross(mainCamera->getComponent<Camera>()->getFront(), mainCamera->getComponent<Camera>()->getUp())) * cameraSpeed);

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
			glfwMakeContextCurrent(m_window);
		}
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		// Criar uma instância da classe Mouse
		Mouse::getInstance().setWindow(m_window);
		// tell GLFW to capture our mouse
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);
		if (GLEW_OK != glewInit())
		{
			std::cout << "Error inicialized GLEW!" << std::endl;
		}
	}

	Engine::~Engine()
	{
		glfwTerminate();
	}

	void Engine::run()
	{
		std::vector<Vertex> vertices;

		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f),	Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f),	Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f),	Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f),	Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f,  0.0f)));

		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f),	Vector3(0.0f, 0.0f, 1.0f),	Vector2(0.0f,  0.0f)));

		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f),	Vector3(-1.0f, 0.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f),	Vector3(-1.0f, 0.0f, 0.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f),	Vector3(-1.0f, 0.0f, 0.0f),	Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f),	Vector3(-1.0f, 0.0f, 0.0f),	Vector2(1.0f,  0.0f)));

		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(1.0f, 0.0f, 0.0f),	Vector2(1.0f,  0.0f)));

		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f),	Vector3(0.0f, -1.0f, 0.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f),	Vector3(0.0f, -1.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f),	Vector3(0.0f, -1.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f),	Vector3(0.0f, -1.0f, 0.0f),	Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f,  1.0f)));

		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(1.0f,  1.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(1.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f,  0.0f)));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f),  Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f,  1.0f)));


		stbi_set_flip_vertically_on_load(true);

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

		/*
		*	Configuração do Objeto que vai Iluminar ( Light )
		*/
		ref<GameObject> light = createRef<GameObject>(1, "light", "light");
		{
			ref<Shader> shaderLight = createRef<Shader>("resources/shaders/light.vertex", "resources/shaders/light.frag");

			ref<Mesh> meshLight = createRef<Mesh>();
			ref<Material> materialLight = createRef<Material>();
			ref<Renderer> rendererLight = createRef<Renderer>();
			ref<Transform> transformLight = createRef<Transform>(
				Vector3(1.0f, 1.0f, 3.0f),
				Vector3(0.2f),
				Vector3(0.0f)
				);

			meshLight->setVertices(vertices);
			meshLight->setup();

			materialLight->setShader(shaderLight);
			materialLight->setup();

			rendererLight->setMaterial(materialLight);
			rendererLight->setMesh(meshLight);

			light->addComponent<Transform>(transformLight);
			light->addComponent<Mesh>(meshLight);
			light->addComponent<Renderer>(rendererLight);
			EntityManager::getInstance().addEntity<GameObject>(light);
		}

		/*
		*	Configuração do Cubo de Exemplo que vai ser iluminado
		*/
		ref<GameObject> cubo = createRef<GameObject>(2, "light", "light");
		{
			ref<Shader> shaderReceptorLight = createRef<Shader>("resources/shaders/default.vertex", "resources/shaders/default.frag");
			ref<Texture> diffuse = createRef<Texture>("resources/texture/container2.png", true);
			ref<Texture> specular = createRef<Texture>("resources/texture/container2_specular.png", true);
			ref<Mesh> meshCubo = createRef<Mesh>();
			ref<Material> materialCubo = createRef<Material>();
			ref<Renderer> rendererCubo = createRef<Renderer>();
			ref<Transform> transformCubo = createRef<Transform>(
				Vector3(1.0f),
				Vector3(1.0f),
				Vector3(0.0f)
			);

			meshCubo->setVertices(vertices);
			meshCubo->setup();

			materialCubo->setShader(shaderReceptorLight);
			materialCubo->setTexture("material.diffuse", diffuse);
			materialCubo->setTexture("material.specular", specular);
			materialCubo->setup();

			rendererCubo->setMaterial(materialCubo);
			rendererCubo->setMesh(meshCubo);

			cubo->addComponent<Transform>(transformCubo);
			cubo->addComponent<Mesh>(meshCubo);
			cubo->addComponent<Renderer>(rendererCubo);
			EntityManager::getInstance().addEntity<GameObject>(cubo);
		}

		while (!glfwWindowShouldClose(m_window)) {

			Time::getInstance().updateDeltaTime();
			Mouse::getInstance().update();

			mouse_input(mainCamera, width, height, m_window);

			GLclampf Red = 0.2f, Green = 0.2f, Blue = 0.2f, Alpha = 0.0f;
			glClearColor(Red, Green, Blue, Alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			{
				Vector3 _positionLight = light->getComponent<Transform>()->getPosition();
				Vector3 _postitionCamera = mainCamera->getComponent<Transform>()->getPosition();

				ref<Renderer> cuboRenderer = cubo->getComponent<Renderer>();
				ref<Transform> cuboTransform = cubo->getComponent<Transform>();
				ref<Shader> shaderCubo = cuboRenderer->getMaterial()->getShader();
				shaderCubo->Bind();

				shaderCubo->setUniform3f("light.position", _positionLight.x, _positionLight.y, _positionLight.z);
				shaderCubo->setUniform3f("viewPos", _postitionCamera.x, _postitionCamera.y, _postitionCamera.z);

				// light properties
				shaderCubo->setUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
				shaderCubo->setUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
				shaderCubo->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

				// material properties
				shaderCubo->setUniform1f("material.shininess", 32.0f);
				
				Matrix3 transpose = cuboTransform->getTransposeMatrix();
				shaderCubo->setUniformMatrix3fv("modelTranspose", transpose);
				cuboTransform->rotate(Vector3(0.0f, -0.5f, 0.0f) * (float)(Time::getInstance().deltaTime()));

				cuboRenderer->bind();
				cuboRenderer->render();
			}

			{
				ref<Renderer> lightRenderer = light->getComponent<Renderer>();
				ref<Shader> shader = lightRenderer->getMaterial()->getShader();

				lightRenderer->bind();
				lightRenderer->render();
			}

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}
}


