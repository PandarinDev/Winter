#include "Engine.h"

int main(int argc, char** argv) {
	using namespace winter;
	Configuration config = {
		"Winter v0.1", 1600, 900, true, false, // Window configuration
		60.0f, 0.1f, 100.0f // Renderer configuration
	};

	Engine& engine = Engine::getInstance();
	engine.init(config);
	engine.start();
	return 0;
}