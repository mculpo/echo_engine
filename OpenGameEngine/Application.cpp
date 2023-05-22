#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/Engine.h"

int main(void) {
	openge::Engine* engine = new openge::Engine(800, 600, "OpenGameEngine", false);
	engine->run();
}