#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/Engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/ecs/Transform.h"
int main(void) {
	openge::Engine* engine = new openge::Engine(800, 600, "OpenGameEngine", false);
	engine->run();
	return 0;
}