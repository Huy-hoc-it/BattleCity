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
    SDL_Color color;
    SDL_Texture* texture;

    MenuButton(const string& t, int x, int y, int w, int h, SDL_Color c){
        text = t;
        color = c;
        texture = nullptr;
        rect = {x, y, w, h};
    }
    bool isMouseOver(int mouseX, int mouseY);
};

struct Menu
{
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color titleColor;
    SDL_Texture* titleTexture;
    SDL_Rect titleRect;
    vector<MenuButton> buttons;

    Menu(SDL_Renderer* ren, TTF_Font* f){
        renderer = ren;
        font = f;
        titleTexture = nullptr;


        titleColor = {255, 255, 0};  // Màu vàng
        createTitle("Battle City", 100, 50);

        buttons.push_back(MenuButton("Start", 150, 200, 200, 50, {255, 255, 255}));
        buttons.push_back(MenuButton("Exit", 150, 300, 200, 50, {255, 255, 255}));

        for (auto& button : buttons) {
            createButtonTexture(button);
        }
    }

    void createTitle(const string& text, int x, int y);
    void createButtonTexture(MenuButton& button);
    void render();
    string handleMouseEvent(int mouseX, int mouseY);
};


#endif
