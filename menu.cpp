#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include <string>
#include "menu.h"
using namespace std;

bool MenuButton::isMouseOver(int mouseX, int mouseY)
{
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
               mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void Menu::render()
{
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

    for (const auto& button : buttons) {
        SDL_RenderCopy(renderer, button.texture, nullptr, &button.rect);
    }
}

string Menu::handleMouseEvent(int mouseX, int mouseY)
{
    for (auto& button : buttons) {
        if (button.isMouseOver(mouseX, mouseY)) {
            return button.text; // Trả về tên của nút được click
        }
    }
    return "";
}
