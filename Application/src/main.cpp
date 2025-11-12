#include <game.h>

float lastFrame = 0;
float deltaTime = 0;

int main(int argc, const char* argv[]) {
	Core::Game* game = new Core::Game("OpenGL", 800, 600);

    //Core::MeshLoader
	
	game->run();

	return 0;
}
