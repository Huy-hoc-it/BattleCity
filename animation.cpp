#include "animation.h"

Explosion::Explosion(int x_, int y_, vector<SDL_Texture*>& explosionTextures)
    : x(x_), y(y_), currentFrame(0), totalFrames(explosionTextures.size()),
      frameDelay(10), delayCounter(0), active(true), textures(explosionTextures) {}

void Explosion::update()
{
    if (!active) return;

    delayCounter++;
    if (delayCounter >= frameDelay)
    {
        delayCounter = 0;
        currentFrame++;

        if (currentFrame >= totalFrames)
        {
            active = false;
        }
    }
}

void Explosion::render(SDL_Renderer* renderer)
{
    if (!active) return;

    SDL_Rect rect = {x, y, 30, 30};
    SDL_RenderCopy(renderer, textures[currentFrame], nullptr, &rect);
}

void ExplosionManager::addExplosion(int x, int y, vector<SDL_Texture*>& explosionTextures)
{
    explosions.push_back(Explosion(x, y, explosionTextures));
}

void ExplosionManager::updateExplosions()
{
    for (size_t i = 0; i < explosions.size(); )
    {
        explosions[i].update();
        if (!explosions[i].active)
        {
            explosions.erase(explosions.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void ExplosionManager::renderExplosions(SDL_Renderer* renderer)
{
    for (Explosion& exp : explosions)
    {
        exp.render(renderer);
    }
}
