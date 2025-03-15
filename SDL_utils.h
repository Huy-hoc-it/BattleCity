#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char* WINDOW_TITLE);

void renderTexture(SDL_Texture *texture, int x, int y, int witch, int height, double direc, SDL_RendererFlip flip, SDL_Renderer* renderer);

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

void logErrorAndExit(const char* msg, const char* error);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);

void waitUntilKeyPressed();

#endif // UTILS_H
