#include "User_interface.h"

UI::UI(SDL_Renderer* ren, TTF_Font* font_, SDL_Texture* pauseTexture)
    : renderer(ren), font(font_), pauseButton("Pause", 650, 200, 100, 100, pauseTexture) {}

void UI::renderText(const string& text, int x, int y, int w, int h)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {x, y, w, h};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void UI::render(int& score, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    SDL_Rect sidebar = {SCREEN_HEIGHT, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &sidebar);

    pauseButton.render(renderer);

    renderText("Score: " + to_string(score), 650, 50, 100, 50);
}

