#include <Core/tspch.h>
#include "Engine.h"
using namespace openge;
int main(void) {

	openge::Engine* engine = new openge::Engine(800.0f, 600.0f, "OpenGameEngine", false);
	engine->run();
	return 0;
}