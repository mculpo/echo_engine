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
		Engine(int width, int height, const char* title, bool fullWidth);
		~Engine();
		void run();
	private:
		GLFWwindow* m_window;
	};
}

