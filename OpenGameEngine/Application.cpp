#include <Engine.h>
using namespace openge;
int main(void) {
	openge::Engine* engine = new openge::Engine(WIDTH, HEIGHT, "OpenGameEngine", false);
	engine->run();
	return 0;
}