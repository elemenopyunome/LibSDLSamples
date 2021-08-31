#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "FileHelper.h"
#include "TileVectorHelper.h"
#include "Downloader.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1024
double round(double x, int n) {
    int d = 0;
    if ((x * pow(10, n + 1)) - (floor(x * pow(10, n))) > 4) d = 1;
    x = (floor(x * pow(10, n)) + d) / pow(10, n);
    return x;
}
int main(int argc, char* args[]) {
    double LatValue = -97.01222;
    double LongValue = 33.04583;
    
    TileVectorHelper _tvhelper;
    std::string FileURL = _tvhelper.GetVectorLocationByLatAndLong(LatValue, LongValue);

    HTTPDownloader _dl;
    std::string FilePath = _dl.download_mvt(FileURL);
    FileHelper _helper;
    std::vector<std::string> info = _helper.GetVectors(FilePath);
    int vectsize = info.size();
    int MajorDivider = 3;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Event event;
        int quit = 0;
        double Multiplier = 0.02;
        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_WIDTH, SDL_WINDOW_SHOWN, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            while (!quit)
            {
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_LEFT:
                                LongValue += Multiplier;
                                break;
                            case SDLK_RIGHT:
                                LongValue -= Multiplier;
                                break;
                            case SDLK_UP:
                                LatValue += Multiplier;
                                break;
                            case SDLK_DOWN:
                                LatValue -= Multiplier;
                                break;
                            case SDLK_x:
                                quit = 1;
                                break;
                            default:
                                break;
                            }
                    }
                    FileURL = _tvhelper.GetVectorLocationByLatAndLong(round(LatValue,6), round(LongValue,6));

                    FilePath = _dl.download_mvt(FileURL);
                    std::vector<std::string> infotemp = _helper.GetVectors(FilePath);
                    int vectsize = infotemp.size();
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 51, SDL_ALPHA_OPAQUE);
                    for (int i = 0; i < vectsize; i++)
                    {
                        std::string row = infotemp[i];
                        std::vector<std::string> entirevector = _helper.split(row, ',');
                        int x1 = std::stoi(entirevector[0]) / MajorDivider;
                        int y1 = std::stoi(entirevector[1]) / MajorDivider;
                        int x2 = std::stoi(entirevector[2]) / MajorDivider;
                        int y2 = std::stoi(entirevector[3]) / MajorDivider;
                        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                        
                    }
                    SDL_RenderPresent(renderer);
                    //SDL_Delay(3000);
                        //SDL_Delay(3000);
                }
            }
            //while (!done) 
            //{
            //    SDL_Event event;

            //    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            //    SDL_RenderClear(renderer);

            //    SDL_SetRenderDrawColor(renderer, 255, 255, 51, SDL_ALPHA_OPAQUE);
            //    for (int i = 0; i < vectsize; i++)
            //    {
            //        std::string row = info[i];
            //        std::vector<std::string> entirevector = _helper.split(row, ',');
            //        int x1 = std::stoi(entirevector[0]) / MajorDivider;
            //        int y1 = std::stoi(entirevector[1]) / MajorDivider;
            //        int x2 = std::stoi(entirevector[2]) / MajorDivider;
            //        int y2 = std::stoi(entirevector[3]) / MajorDivider;
            //        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            //        SDL_RenderPresent(renderer);
            //        //SDL_Delay(50);
            //    }
            //    
            //    SDL_Delay(19000);
            //    break;

            //    while (SDL_PollEvent(&event)) {
            //        if (event.type == SDL_QUIT) {
            //            done = SDL_TRUE;
            //        }
            //    }
            //}
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