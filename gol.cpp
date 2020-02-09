#include "gol.h"

int main(int argc, char** argv)

{

	if (!SDL_Init(SDL_INIT_VIDEO))

	{

		SDL_Window* window;

		SDL_Renderer* renderer;

		SDL_Event event;

		SDL_bool done = SDL_FALSE;

		

		//creating window and renderer

		if (!SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer))

		{

			//initializing alive cells

			INIT_ALIVECELLS();

			while (!done)

			{

				//updating each cell by the game rules

				UPDATE_CELLS();

				//drawing grid by each cell's state

				UPDATE_GRID(renderer);

				SDL_PollEvent(&event);

				if (event.type == SDL_QUIT)

				{

					done = SDL_TRUE;

				}

				SDL_Delay(100);

			}

		}

		else

		{

			std::cerr << "Failed to create window or renderer" << std::endl;

			exit(EXIT_FAILURE);

		}

		//destroying window,renderer and quiting

		SDL_DestroyWindow(window);

		SDL_DestroyRenderer(renderer);

		SDL_Quit();

	}

	else

	{

		std::cerr << "Failed to initialize SDL2" << std::endl;

		exit(EXIT_FAILURE);

	}

	return 0;

}
