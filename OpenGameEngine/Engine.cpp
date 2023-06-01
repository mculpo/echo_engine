#include "Engine.h"
#include <Core/tspch.h>

#include <Renderer/VertexArrayObject.h>
#include <Renderer/VertexBufferObject.h>
#include <Renderer/Texture.h>
#include <Renderer/ElementBufferObject.h>
#include <Renderer/MeshRenderer.h>
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


namespace openge {
	
	

	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;

	// Custom implementation of the LookAt function
	glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
	{
		// 1. Position = known
		// 2. Calculate cameraDirection
		glm::vec3 zaxis = glm::normalize(position - target);
		// 3. Get positive right axis vector
		glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
		// 4. Calculate camera up vector
		glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		// Create translation and rotation matrix
		// In glm we access elements as mat[col][row] due to column-major layout
		glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
		translation[3][0] = -position.x; // Third column, first row
		translation[3][1] = -position.y;
		translation[3][2] = -position.z;
		glm::mat4 rotation = glm::mat4(1.0f);
		rotation[0][0] = xaxis.x; // First column, first row
		rotation[1][0] = xaxis.y;
		rotation[2][0] = xaxis.z;
		rotation[0][1] = yaxis.x; // First column, second row
		rotation[1][1] = yaxis.y;
		rotation[2][1] = yaxis.z;
		rotation[0][2] = zaxis.x; // First column, third row
		rotation[1][2] = zaxis.y;
		rotation[2][2] = zaxis.z;

		// Return lookAt matrix as combination of translation and rotation matrix
		return rotation * translation; // Remember to read from right to left (first translation then rotation)
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	Engine::Engine(int width, int height, const char* title, bool fullWidth)
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
		//Time::getInstance().setTargetFps(120);
		std::vector<float>vertices = {
				-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,		0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 1.0f,		0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,		1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,		1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,		0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 1.0f,		0.0f, 1.0f
		};

		stbi_set_flip_vertically_on_load(true);
		std::shared_ptr<GameObject> mainCamera = std::make_shared<GameObject>(0, "MainCamera", "MainCamera");

		std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		camera->setCameraType(CameraType::Perpective);
		camera->setAspectRatio(800.0f/600.0f);
		camera->setFov(45.0f);
		camera->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
		camera->setUp(glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setFarPlane(100.0f);
		camera->setNearPlane(0.1f);

		std::shared_ptr<Transform> transformCamera = std::make_shared <Transform>(
			glm::vec3(0.0f, 0.0f, 3.0f), 
			glm::vec3(1.0f), 
			glm::vec3(0.0f)
		);

		mainCamera->addComponent<Camera>(camera);
		mainCamera->addComponent<Transform>(transformCamera);
		
		
		std::random_device rd;   // Obtém uma seed aleatória do dispositivo
		std::mt19937 gen(rd());  // Gera números aleatórios usando o algoritmo Mersenne Twister
		std::uniform_real_distribution<float> dist(-10.0f, 10.0f);  // Distribuição uniforme entre -10 e 10
		std::uniform_real_distribution<float> distA(-10.0f, 0.0f);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		std::shared_ptr<Material> material = std::make_shared<Material>();

		mesh->setVertices(vertices);
		mesh->setup();

		material->setTexture("texture1", std::make_shared<Texture>("resources/texture/container.jpg"));
		material->setTexture("texture2", std::make_shared<Texture>("resources/texture/awesomeface.png", true));
		material->setShader(std::make_shared <Shader>("resources/shaders/uniform.vertex", "resources/shaders/uniform.frag"));
		material->setup();

		for (int i = 0; i < 30; ++i) {

			std::shared_ptr<GameObject> box = std::make_shared<GameObject>(i, "Box", "Box");
			std::shared_ptr<Transform> transformBox = std::make_shared<Transform>(
				glm::vec3(dist(gen), dist(gen), distA(gen)), glm::vec3(1.0f), glm::vec3(0.0f)
				);

			std::shared_ptr<MeshRenderer>meshRenderer = std::make_shared<MeshRenderer>();
			
			meshRenderer->setMesh(mesh);
			meshRenderer->setMaterial(material);

			box->addComponent<Transform>(transformBox);
			box->addComponent<Mesh>(mesh);
			box->addComponent<MeshRenderer>(meshRenderer);


			EntityManager::getInstance().addEntity<GameObject>(box);
		}

		EntityManager::getInstance().addEntity<GameObject>(mainCamera);


		while (!glfwWindowShouldClose(m_window)) {

			Time::getInstance().updateDeltaTime();
			Mouse::getInstance().update();

			//Input Mouse and Keyboard
			{
				//float xpos = Mouse::getInstance().getX();
				//float ypos = Mouse::getInstance().getY();
				//float xoffset = xpos - lastX;
				//float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
				//lastX = xpos;
				//lastY = ypos;

				//float sensitivity = 0.1f; // change this value to your liking
				//xoffset *= sensitivity;
				//yoffset *= sensitivity;

				//yaw += xoffset;
				//pitch += yoffset;

				//// make sure that when pitch is out of bounds, screen doesn't get flipped
				//if (pitch > 89.0f)
				//	pitch = 89.0f;
				//if (pitch < -89.0f)
				//	pitch = -89.0f;

				//glm::vec3 front;
				//front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
				//front.y = sin(glm::radians(pitch));
				//front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
				//mainCamera->getComponent<Camera>()->setFront(glm::normalize(front));


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

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			std::vector<std::shared_ptr<GameObject>> entities = EntityManager::getInstance().findGameObjectsByTag<GameObject>("Box");

			for (const auto& entity : entities)
			{

				MeshRenderer* render = entity->getComponent<MeshRenderer>().get();

				render->bind();
				render->render();
			}

			//double fps = 1.0 / deltaTime;
			//std::cout << "FPS: " << fps << std::endl;
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}
}


