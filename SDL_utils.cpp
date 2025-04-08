#include "SDL_utils.h"

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char* WINDOW_TITLE){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    if (TTF_Init() == -1) {
        logErrorAndExit("TTF_Init", TTF_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        logErrorAndExit("Mix_OpenAudio", Mix_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    if (TTF_Init() == -1) {
        logErrorAndExit("TTF_Init", TTF_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void renderTexture(SDL_Texture *texture, int x, int y, int width, int height, double direc, SDL_RendererFlip flip, SDL_Renderer* renderer)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = width;
	dest.h = height;
	//SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopyEx(renderer, texture, NULL, &dest, direc, NULL, flip);
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

TTF_Font* loadFont(const char* filename, int fontSize) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading font %s", filename);

    TTF_Font* font = TTF_OpenFont(filename, fontSize);
    if (font == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Failed to load font %s: %s", filename, TTF_GetError());
    }

    return font;
}

Mix_Chunk* loadMedia(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading media %s", filename);

    Mix_Chunk* media = Mix_LoadWAV(filename);
    if (media == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Failed to load media %s: %s", filename, Mix_GetError());
    }

    return media;
}

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, map<string, SDL_Texture*>& texture,
             vector <SDL_Texture*>& explosionTextures, TTF_Font* font, map<string, Mix_Chunk*>& media)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for (auto& pair : texture) {
        SDL_DestroyTexture(pair.second);
    }
    texture.clear();

    for(int i = 0; i < int(explosionTextures.size()); i++){
        SDL_DestroyTexture(explosionTextures[i]);
    }
    explosionTextures.clear();

    for (auto& pair : media) {
        Mix_FreeChunk(pair.second);
    }
    media.clear();

    TTF_CloseFont(font);

    SDL_Quit();
    TTF_Quit();
    Mix_CloseAudio();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
