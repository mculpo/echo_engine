#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>


namespace openge {
	class Engine
	{
	public:
		Engine(float width, float height, const char* title, bool fullWidth);
		~Engine();
		void run();
	private:
		GLFWwindow* m_window;
		float width;
		float height;
	};
}

