#include "Engine.h"
#include "Shader.h"
#include "VertexBufferObject.h"
#include <stb_image.h>
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexAttribPointerLayout.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"
#include "ecs/Transform.h"
#include "ecs/Camera.h"
#include "ecs/Model.h"
#include "Input.h"
#include "Mouse.h"
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

		Model mainCamera = Model(1, "MainCamera", "MainCamera");

		Camera camera = Camera(mainCamera, 1);
		camera.setCameraType(CameraType::Perpective);
		camera.setAspectRatio(800.0f/600.0f);
		camera.setFov(45.0f);
		camera.setFront(glm::vec3(0.0f, 0.0f, -1.0f));
		camera.setUp(glm::vec3(0.0f, 1.0f, 0.0f));
		camera.setFarPlane(100.0f);
		camera.setNearPlane(0.1f);

		Transform transformCamera = Transform(mainCamera, 2, 
			glm::vec3(0.0f, 0.0f, 3.0f), 
			glm::vec3(1.0f), 
			glm::vec3(0.0f)
		);

		mainCamera.addComponent<Camera>(camera);
		mainCamera.addComponent<Transform>(transformCamera);

		float vertices[] = {
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

		std::vector<openge::Transform> transforms = {
			openge::Transform(mainCamera, 0, glm::vec3(0.0f,  0.0f,  0.0f),  glm::vec3(1.0f),  glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(2.0f,  5.0f, -15.0f),  glm::vec3(1.0f), glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(-1.5f, -2.2f, -2.5f),  glm::vec3(1.0f), glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(-3.8f, -2.0f, -12.3f),  glm::vec3(1.0f),glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(1.0f),  glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(-1.7f,  3.0f, -7.5f),  glm::vec3(1.0f), glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.0f),  glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(1.5f,   2.0f, -2.5f),  glm::vec3(1.0f), glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(1.5f,   0.2f, -1.5f),  glm::vec3(1.0f), glm::vec3(0.0f)),
			openge::Transform(mainCamera, 0, glm::vec3(-1.3f,  1.0f, -1.5f),  glm::vec3(1.0f), glm::vec3(0.0f))
		};

		VertexArrayObject *vao = new VertexArrayObject();
		VertexBufferObject *vbo = new VertexBufferObject(vertices, sizeof(vertices), GL_STATIC_DRAW);
		//ElementBufferObject *ebo = new ElementBufferObject(indices, sizeof(indices), GL_STATIC_DRAW);


		vao->AddLayout(3, VP_FLOAT); // position
		vao->AddLayout(3, VP_FLOAT); // color
		vao->AddLayout(2, VP_FLOAT); // texture

		vao->runLayout();

		vbo->Unbind();
		vao->Unbind();

		stbi_set_flip_vertically_on_load(true);

		Texture* texture1 = new Texture("resources/texture/container.jpg");
		Texture* texture2 = new Texture("resources/texture/awesomeface.png", true);

		/*
		* Shaders Vertex and Fragment configuration
		* create and use its
		*/
		Shader* shader = new Shader("resources/shaders/uniform.vertex", "resources/shaders/uniform.frag");

		shader->Bind();
		shader->setUniform1i("texture1", 0);
		shader->setUniform1i("texture2", 1);

		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

		while (!glfwWindowShouldClose(m_window)) {

			Time::getInstance().updateDeltaTime();
			Mouse::getInstance().update();
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
			mainCamera.getComponent<Camera>()->setFront( glm::normalize(front) );


			if (Input::IsKeyPressed(KEYCODE_ESCAPE))
				glfwSetWindowShouldClose(m_window, true);

			float cameraSpeed = static_cast<float>(2.5 * Time::getInstance().deltaTime());
			if (Input::IsKeyHeld(KEYCODE_W))
				mainCamera.getComponent<Transform>()->translate(cameraSpeed * mainCamera.getComponent<Camera>()->getFront());
			if (Input::IsKeyHeld(KEYCODE_S))
				mainCamera.getComponent<Transform>()->translate(-(cameraSpeed * mainCamera.getComponent<Camera>()->getFront()));
			if (Input::IsKeyHeld(KEYCODE_A))
				mainCamera.getComponent<Transform>()->translate(-glm::normalize(glm::cross(mainCamera.getComponent<Camera>()->getFront(), mainCamera.getComponent<Camera>()->getUp())) * cameraSpeed);
			if (Input::IsKeyHeld(KEYCODE_D))
				mainCamera.getComponent<Transform>()->translate(glm::normalize(glm::cross(mainCamera.getComponent<Camera>()->getFront(), mainCamera.getComponent<Camera>()->getUp())) * cameraSpeed);


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			texture1->Bind();
			glActiveTexture(GL_TEXTURE1);
			texture2->Bind();

			shader->Bind(); 
			////glm::mat4 model = glm::mat4(1.0f);
			//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			//glm::mat4 projection = glm::mat4(1.0f);

			//// Create a Perpective Projection
			//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			//shader->setUniformMatrix4fv("model", model);
			std::shared_ptr<Camera> camera = mainCamera.getComponent<Camera>();
			glm::mat4 view = camera->getViewMatrix();
			glm::mat4 projection = camera->getProjectionMatrix();
			shader->setUniformMatrix4fv("view", view);
			shader->setUniformMatrix4fv("projection", projection);
			//render container 
			
			vao->Bind();
			for (unsigned int i = 0; i < transforms.size(); i++) {
				openge::Transform& transform = transforms[i];
				transform.rotate(glm::vec3(0.0f, 0.0f, 1.0f) * (float)(1 * Time::getInstance().deltaTime()));
				transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f) * (float)(2 * Time::getInstance().deltaTime()));
				
				//transform.lookAt(cameraPos, 20 * Time::getInstance().deltaTime());
				transform.scale(glm::vec3(0.5f));
				glm::mat4 model = transform.getModelMatrix();
				shader->setUniformMatrix4fv("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			//glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
			
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		delete shader;
		delete texture1;
		delete texture2;
		delete vbo;
		//delete ebo;
		delete vao;
	}
}


