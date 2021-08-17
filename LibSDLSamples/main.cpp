#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xF9, 0xFF, 0x33));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(6000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}