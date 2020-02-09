#pragma once

#include <SDL.h>

#include <iostream>

#define ALIVE 1

#define DEAD 0

const int WindowHeight = 800;

const int WindowWidth = 1200;

const int cellWidth = 10;

const int cellHeight = 10;

const int ROWS = WindowWidth / cellWidth;

const int COLS = WindowHeight / cellHeight;

int GRID[ROWS][COLS] = { DEAD };



//initializing alive cells

void INIT_ALIVECELLS()

{

	for (auto i = 0; i < ROWS; i++)

	{

		GRID[i][0] = ALIVE;

	}

	for (auto i = 0; i < ROWS; i++)

	{

		GRID[i][COLS - 1] = ALIVE;

	}

	for (auto i = 0; i < COLS; i++)

	{

		GRID[0][i] = ALIVE;



	}

	for (auto i = 0; i < COLS; i++)

	{

		GRID[ROWS - 1][i] = ALIVE;

	}

}

//counting number of a cell's alive neighbors

inline int GET_NUMBEROF_LIVENEIGHBORS(int x, int y)

{

	int neighbors = 0;

	for (auto i = x - 1; i <= x + 1; i++)

	{

		for (auto j = y - 1; j <= y + 1; j++)

		{

			if ((i == x && j == y))

			{

				continue;

			}

			if (i < ROWS && j < COLS && i >= 0 && j >= 0)

			{

				if (GRID[i][j] == ALIVE)

				{

					neighbors++;

				}

			}

		}

	}

	return neighbors;

}

void UPDATE_CELLS()

{

	//an array to hold number of each cell's alive neighbors

	int NEIGHBORS[ROWS][COLS] = { 0 };

	// filling neighbors array with number of each cell's alive neighbors

	for (auto i = 0; i < ROWS; i++)

	{

		for (auto j = 0; j < COLS; j++)

		{

			NEIGHBORS[i][j] = GET_NUMBEROF_LIVENEIGHBORS(i, j);

		}

	}



	//updating every cell by game rules

	for (auto i = 0; i < ROWS; i++)

	{

		for (auto j = 0; j < COLS; j++)

		{

			if (NEIGHBORS[i][j] <= 1)

			{

				GRID[i][j] = DEAD;

			}

			if (GRID[i][j] == ALIVE && (NEIGHBORS[i][j] == 2 || NEIGHBORS[i][j] == 3))

			{

				GRID[i][j] = ALIVE;

			}

			if (GRID[i][j] == ALIVE && NEIGHBORS[i][j] > 3)

			{

				GRID[i][j] = DEAD;

			}

			if (GRID[i][j] == DEAD && NEIGHBORS[i][j] == 3)

			{

				GRID[i][j] = ALIVE;

			}

		}

	}

}

void UPDATE_GRID(SDL_Renderer* renderer)

{

	for (auto i = 0; i < ROWS; i++)

	{

		for (auto j = 0; j < COLS; j++)

		{

			//filling cell with white if it's alive

			if (GRID[i][j] == ALIVE)

			{

				SDL_SetRenderDrawColor(renderer, 25, 255, 255, SDL_ALPHA_TRANSPARENT);

				SDL_Rect rect{i* cellWidth,j* cellHeight,cellWidth,cellHeight };

				SDL_RenderFillRect(renderer, &rect);

			}

			//filling cell with black if it's dead

			if (GRID[i][j] == DEAD)

			{

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);

				SDL_Rect rect{ i * cellWidth,j * cellHeight,cellWidth,cellHeight };

				SDL_RenderFillRect(renderer, &rect);

			}

		}

	}

	//drawing grid

	SDL_SetRenderDrawColor(renderer, 255, 17, 41, SDL_ALPHA_OPAQUE);

	for (auto i = 0; i < ROWS; i++)

	{

		for (auto j = 0; j < COLS; j++)

		{

			SDL_Rect rect{ i * cellWidth,j * cellHeight,cellWidth,cellHeight };

			SDL_RenderDrawRect(renderer, &rect);

		}

	}

	SDL_RenderPresent(renderer);

}
