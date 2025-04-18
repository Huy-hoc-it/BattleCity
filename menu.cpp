#include "menu.h"
using namespace std;

bool Button::isMouseOver(int mouseX, int mouseY)
{
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
               mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void Button::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
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
