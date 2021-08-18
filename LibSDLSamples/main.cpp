#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "FileHelper.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        
        if (SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 51, SDL_ALPHA_OPAQUE);
                for (int i = 0; i < 500; i++)
                {
                    SDL_SetRenderDrawColor(renderer, 94, 155, 159, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 330+i, 260+i, 129, 359 + i);
                    SDL_SetRenderDrawColor(renderer, 233, 155, 66, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 230 + i, 359 + i, 228, 258 + i);
                    SDL_SetRenderDrawColor(renderer, 156, 78, 45, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 130 + i, 160 + i, 329, 159 + i);
                    SDL_SetRenderDrawColor(renderer, 75, 155, 88, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 230 + i, 360 + i, 329, 259 + i);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 11, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 330 + i, 159 + i, 128, 358 + i);
                    SDL_SetRenderDrawColor(renderer, 76, 34, 65, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, 130 + i, 260 + i, 229, 159 + i);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                }
                break;

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
	return 0;
}