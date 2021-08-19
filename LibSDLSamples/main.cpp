#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "FileHelper.h"
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

int main(int argc, char* args[]) {
    FileHelper _helper;
    std::vector<std::string> info = _helper.GetVectorsFromFile("D:\\Files\\bla.txt");
    int vectsize = info.size();
    
    /*for (int i = 0; i < vectsize; i++)
    {
        std::string row = info[i];
        std::vector<std::string> entirevector = _helper.split(row, ',');
    }*/

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        
        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_WIDTH, SDL_WINDOW_FULLSCREEN, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 51, SDL_ALPHA_OPAQUE);
                for (int i = 0; i < vectsize; i++)
                {
                    std::string row = info[i];
                    std::vector<std::string> entirevector = _helper.split(row, ',');
                    int x1 = std::stoi(entirevector[0]);
                    int y1 = std::stoi(entirevector[1]);
                    int x2 = std::stoi(entirevector[2]);
                    int y2 = std::stoi(entirevector[3]);
                    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                }
                /*for (int i = 0; i < 500; i++)
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
                }*/
                //SDL_Delay(9000);
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