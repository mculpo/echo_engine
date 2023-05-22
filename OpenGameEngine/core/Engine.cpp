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
		float vertices[] = {
					// positions			// colors			// texture coords
					0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
					0.5f,  -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,		// bottom right
					-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,		// bottom left
					-0.5f, 0.5f,  0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// top left
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		VertexArrayObject *vao = new VertexArrayObject();
		VertexBufferObject *vbo = new VertexBufferObject(vertices, sizeof(vertices), GL_STATIC_DRAW);
		ElementBufferObject *ebo = new ElementBufferObject(indices, sizeof(indices), GL_STATIC_DRAW);


		vao->AddLayout(3, VP_FLOAT);
		vao->AddLayout(3, VP_FLOAT);
		vao->AddLayout(2, VP_FLOAT);

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
			glClear(GL_COLOR_BUFFER_BIT);

			//bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			texture1->Bind();
			glActiveTexture(GL_TEXTURE1);
			texture2->Bind();

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

			shader->setUniformMatrix4fv("transform", transform);
			//render container
			shader->Bind();
			vao->Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

			transform = glm::mat4(1.0f); //reset
			transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
			float scaleAmount = static_cast<float>(sin(glfwGetTime()));
			transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

			shader->setUniformMatrix4fv("transform", transform);

			//render container
			shader->Bind();
			vao->Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		delete shader;
		delete texture1;
		delete texture2;
		delete vbo;
		delete ebo;
		delete vao;
	}
}

