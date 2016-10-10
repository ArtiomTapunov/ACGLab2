//
#include "stdafx.h"
#include "draw.h"

bool init();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* loadedSurface = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("AOKG Lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		loadedSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
			0x00FF0000,  // R
			0x0000FF00,  // G
			0x000000FF,  // B
			0x00000000); // alpha

		gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if ( NULL == gTexture )
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			double step = 0.01;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if ( SDL_QUIT == e.type )
					{
						quit = true;
					}
					if ( SDL_KEYDOWN == e.type )
					{
						switch (e.key.keysym.scancode)
						{
						case SDL_SCANCODE_KP_PLUS:
							printf("SDL_SCANCODE_KP_PLUS have been presssed\n %i", step);
							step += 0.01;
							break;
						case SDL_SCANCODE_KP_MINUS:
							printf("SDL_SCANCODE_KP_MINUS have been presssed\n %i", step);
							step -= 0.01;
							break;
						default:
							break;
						}
					}
				}
				SDL_RenderClear(gRenderer);
				if (step <= 0.01) {
					step = 0.01;
				}
				if (step >= 0.15) {
					step = 0.15;
				}
				SDL_FillRect(loadedSurface, NULL, 0x00000000);
				draw(loadedSurface, step);

				SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}