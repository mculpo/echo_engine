#pragma once
#include <core/core.h>
namespace openge {
	class Engine
	{
	public:
		Engine(float width, float height, const char* title, bool fullWidth);
		~Engine();
		void run();
		void initializeObjects();
		void initializeLights();
		void initializeCamera();
	private:
		GLFWwindow* m_window;
		float width;
		float height;
	};
}

