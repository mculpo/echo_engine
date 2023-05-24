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
namespace openge {

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
		//float vertices[] = {
		//			// positions			// colors			// texture coords
		//			0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
		//			0.5f,  -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,		// bottom right
		//			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,		// bottom left
		//			-0.5f, 0.5f,  0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// top left
		//};

		//unsigned int indices[] = {
		//	0, 1, 3,
		//	1, 2, 3
		//};

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		// world space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		VertexArrayObject *vao = new VertexArrayObject();
		VertexBufferObject *vbo = new VertexBufferObject(vertices, sizeof(vertices), GL_STATIC_DRAW);
		//ElementBufferObject *ebo = new ElementBufferObject(indices, sizeof(indices), GL_STATIC_DRAW);


		vao->AddLayout(3, VP_FLOAT); // position
		//vao->AddLayout(3, VP_FLOAT); // color
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

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			texture1->Bind();
			glActiveTexture(GL_TEXTURE1);
			texture2->Bind();

			shader->Bind(); 
			//glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			
			//Transformation around the model ( Plane with texture )
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
			// Transformation about de View Inspect Camera
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			// Create a Perpective Projection
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			//shader->setUniformMatrix4fv("model", model);
			shader->setUniformMatrix4fv("view", view);
			shader->setUniformMatrix4fv("projection", projection);
			//render container
			
			vao->Bind();
			for (unsigned int i = 0; i < 10; i++) {
				glm::mat4  model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = (float)glfwGetTime()  * 20.0f * (i == 0 ? 1.5f : i);
				model = glm::rotate(model, glm::radians(angle) , glm::vec3(1.0f, 1.0f, 1.0f));
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

