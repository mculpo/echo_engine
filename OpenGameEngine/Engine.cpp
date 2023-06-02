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

	Engine::Engine(float width, float height, const char* title, bool fullWidth) : width(width) , height(height)
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

		Vector2 t00 = Vector2(0.0f, 0.0f);  // Bottom left
		Vector2 t01 = Vector2(0.0f, 1.0f);  // Top left
		Vector2 t10 = Vector2(1.0f, 0.0f);  // Bottom right
		Vector2 t11 = Vector2(1.0f, 1.0f);  // Top right

		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), t00));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f), t01));
		vertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f), t10));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f), t11));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), t00));
		vertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f), t10));
		vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f), t01));
		vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f), t11));


		std::vector<unsigned int> indices = {
							  0, 1, 2,
							  1, 3, 4,
							  5, 6, 3,
							  7, 3, 6,
							  2, 4, 7,
							  0, 7, 6,
							  0, 5, 1,
							  1, 5, 3,
							  5, 0, 6,
							  7, 4, 3,
							  2, 1, 4,
							  0, 2, 7
		};

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
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(1.0f),
			Vector3(0.0f)
		);

		mainCamera->addComponent<Camera>(camera);
		mainCamera->addComponent<Transform>(transformCamera);
		

		ref<Mesh> mesh = createRef<Mesh>();
		ref<Material> material = createRef<Material>();

		mesh->setVertices(vertices);
		mesh->setIndices(indices);
		mesh->setup();

		auto texture = createRef<Texture>("resources/texture/container.jpg");
		auto shader = createRef<Shader>("resources/shaders/default.vertex", "resources/shaders/default.frag");

		material->setTexture("texture0", texture);
		material->setShader(shader);
		material->setup();
		EntityManager::getInstance().addEntity<GameObject>(mainCamera);


		for (int i = 0; i < 20; ++i) {
			
			ref<GameObject> box = createRef<GameObject>(i, "Box", "Box");
			ref<Transform> transformBox = createRef<Transform>(
				glm::vec3(
					Random::getInstance().Range(-5.0f, 5.0f), 
					Random::getInstance().Range(-5.0f, 5.0f), 
					Random::getInstance().Range(-5.0f, 5.0f)), 
					Vector3(1.0f), 
					Vector3(0.0f)
				);

			std::shared_ptr<Renderer>meshRenderer = createRef<Renderer>();
			
			meshRenderer->setMesh(mesh);
			meshRenderer->setMaterial(material);

			box->addComponent<Transform>(transformBox);
			box->addComponent<Mesh>(mesh);
			box->addComponent<Renderer>(meshRenderer);


			EntityManager::getInstance().addEntity<GameObject>(box);
		}

		


		while (!glfwWindowShouldClose(m_window)) {

			Time::getInstance().updateDeltaTime();
			Mouse::getInstance().update();

			//Input Mouse and Keyboard
			{
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
				mainCamera->getComponent<Camera>()->setFront(glm::normalize(front));


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

			GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
			glClearColor(Red, Green, Blue, Alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			std::vector<std::shared_ptr<GameObject>> entities = EntityManager::getInstance().findGameObjectsByTag<GameObject>("Box");

			for (const auto& entity : entities)
			{

				Renderer* render = entity->getComponent<Renderer>().get();

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


