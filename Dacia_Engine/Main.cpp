#include <Utilities\Common.hpp>
#include <Utilities\EngineUtilities.hpp>
#include <Launchers\CrossPlatform\GLFWApp.hpp>
#include <fstream>
#include <random>

#include <Dacia.Math\Definitions.hpp>

#include "ARO/Counters/Stopwatch.hpp"

using namespace Dacia;

int main(int argc, char ** argv)
{
#ifdef _WIN32
	//FreeConsole();
#endif
	ApplicationPtr app = 
		std::make_unique<GLFWApp>(GLFWApp("Game", 1200, 1200, false));

	app->Init();

	void * ptr = nullptr;
	NULL_ASSERT(ptr);

	std::random_device rnd;
	std::mt19937 twst;
	twst.seed(rnd());

	std::uniform_real_distribution<> dist(0.0f, 1.0f);
	dist(twst);

	while (!app->WindowShouldClose())
	{
		glEnable(GL_DEPTH_TEST);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		glClearColor(GLfloat(dist(twst)), GLfloat(dist(twst)), GLfloat(dist(twst)), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		app->Update();
	}

	return EXIT_SUCCESS;
}