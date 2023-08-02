#include <Engine.h>
using namespace openge;
int main(void) {
	openge::Engine* engine = new openge::Engine(1000.0f, 800.0f, "OpenGameEngine", false);
	engine->run();
	return 0;
}