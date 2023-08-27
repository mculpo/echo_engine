#pragma once
#include <core/core.h>
#include <base/FrameBufferTexture.h>
#include <base/Skybox.h>
namespace openge {
	class Engine
	{
	public:
		Engine(float width, float height, const char* title, bool fullWidth);
		~Engine();
		void run();
		void initializeObjects();
		ref<FrameBufferTexture> initializeFrameBuffer();
		ref<Skybox> initializeSkybox();
		void initializeLights();
		void initializeCamera();
	private:
		GLFWwindow* m_window;
		float width;
		float height;
	};
}

