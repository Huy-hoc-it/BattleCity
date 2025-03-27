#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include <string>

using namespace std;

struct MenuButton
{
    SDL_Rect rect;
    string text;
    SDL_Texture* texture;

    MenuButton(const string& t, int x, int y, int w, int h, SDL_Texture* _texture){
        text = t;
        texture = _texture;
        rect = {x, y, w, h};
    }
    bool isMouseOver(int mouseX, int mouseY);
};

struct Menu
{
    SDL_Renderer* renderer;
    SDL_Texture* titleTexture;
    SDL_Rect titleRect;
    vector<MenuButton> buttons;

    Menu(SDL_Renderer* ren, SDL_Texture* _titleTexture, SDL_Texture* Play_button, SDL_Texture* Exit_button, int x, int y, int w, int h){
        renderer = ren;
        titleTexture = _titleTexture;
        titleRect = {x, y, w, h};
        buttons.push_back(MenuButton("Play", 250, 380, 100, 50, Play_button));
        buttons.push_back(MenuButton("Exit", 250, 450, 100, 50, Exit_button));
    }
    void render();
    string handleMouseEvent(int mouseX, int mouseY);
};


#endif
