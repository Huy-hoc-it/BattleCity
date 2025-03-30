#include "game.h"

using namespace std;

void remake(Box& box, Tilemap& tilemap, vector <Enemy>& enemies, bool& active,int& shoot_timer,
             int& enemy_direc_timer, bool& victory, bool& defeat, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount)
{
    active = false;
    box.x = 0;
    box.y = 0;
    shoot_timer = 0;
    enemy_direc_timer = 0;
    victory = false;
    defeat = false;
    box.alive = true;
    for(int i = 0; i < enemyCount; i++)
    {
        enemies[i].alive = true;
    }
    tilemap.loadFromFile("map_1.txt");
    enemies.clear();
    spawnEnemies(enemies, enemyCount, tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void game(SDL_Renderer* renderer, vector <SDL_Texture*>& texture, vector <SDL_Texture*>& explosionTextures,
          const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount)
{
    srand(time(nullptr));
    SDL_Event e;
    Box box;
    box.x = 0;
    box.y = 0;

    Tilemap tilemap;
    tilemap.loadFromFile("map_1.txt");
    tilemap.loadTileTextures(renderer);
    bool running = true;

    vector <Enemy> enemies;

    spawnEnemies(enemies, enemyCount, tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);

    int shoot_timer = 0;
    int enemy_direc_timer = 0;

    Menu menu(renderer, texture[2], 100, 100, 400, 200);
    menu.buttons.push_back(MenuButton("Play", 250, 380, 100, 50, texture[5]));
    menu.buttons.push_back(MenuButton("Exit", 250, 450, 100, 50, texture[6]));
    MenuButton Try_again = MenuButton("Try_again",200, 380, 100, 50, texture[7]);
    MenuButton Exit = MenuButton("Exit_end", 350, 380, 100, 50, texture[6]);

    ExplosionManager explosionManager;

    int enemy_alive = enemyCount;
    bool victory = false;
    bool defeat = false;

    bool active = false;

    while(running)
    {
        if(active == false){
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    string buttonClicked = menu.handleMouseEvent(mouseX, mouseY);
                    if (buttonClicked == "Play") {
                        cout << "Start game!" << endl;
                        active = true;
                    } else if (buttonClicked == "Exit") {
                        cout << "Exit game!" << endl;
                        running = false;
                    }
                }
            }
            SDL_RenderClear(renderer);

            menu.render();

            SDL_RenderPresent(renderer);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            if(victory == false && defeat == false){
                shoot_timer++;
                enemy_direc_timer++;

                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT) running = false;
                    if(e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_LEFT:
                            box.move_left(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                            break;
                        case SDLK_RIGHT:
                            box.move_right(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                            break;
                        case SDLK_UP:
                            box.move_up(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                            break;
                        case SDLK_DOWN:
                            box.move_down(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                            break;
                        case SDLK_SPACE:
                            if(box.alive)box.bullets_main.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2, box.y + box.sizea / 2 - 10 / 2, box.lastDir));
                        default:
                            break;
                        }
                    }
                }

                box.main_shoot(renderer, enemies, tilemap, explosionManager, explosionTextures, enemyCount, enemy_alive, victory, SCREEN_WIDTH, SCREEN_HEIGHT);

                for(int i = 0; i < enemyCount; i++){
                    enemies[i].move_enemy(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                if(shoot_timer > 60){
                    for(int i = 0; i < enemyCount; i++){
                        enemies[i].enemy_shoot();
                    }
                    shoot_timer = 0;
                }
                if(enemy_direc_timer > 180){
                    for(int i = 0; i < enemyCount; i++){
                        enemies[i].move_direc(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    enemy_direc_timer = 0;
                }
                for(int i = 0; i < enemyCount; i++){
                    enemies[i].update_bullets(renderer, box, tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                if(box.alive == false)defeat = true;

                tilemap.render_map(renderer);
                box.render(renderer, texture[0]);
                for(int i = 0; i < enemyCount; i++){
                    enemies[i].render_enemy(renderer, texture[1]);
                }

                explosionManager.updateExplosions();
                explosionManager.renderExplosions(renderer);
            }
            else if(victory == true){
                renderTexture(texture[3], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FLIP_NONE, renderer);
                Try_again.render(renderer);
                Exit.render(renderer);
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT) running = false;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;

                        if (Try_again.isMouseOver(mouseX, mouseY)) {
                            cout << "Try again!" << endl;
                            remake(box, tilemap, enemies, active, shoot_timer, enemy_direc_timer, victory,
                                   defeat, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);
                        }
                        else if (Exit.isMouseOver(mouseX, mouseY)) {
                            cout << "Exit game!" << endl;
                            running = false;
                        }
                    }
                }
            }
            else if(defeat == true){
                renderTexture(texture[4], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FLIP_NONE, renderer);
                Try_again.render(renderer);
                Exit.render(renderer);
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT) running = false;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;

                        if (Try_again.isMouseOver(mouseX, mouseY)) {
                            cout << "Try again!" << endl;
                            remake(box, tilemap, enemies, active, shoot_timer, enemy_direc_timer, victory,
                                   defeat, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);
                        }
                        else if (Exit.isMouseOver(mouseX, mouseY)) {
                            cout << "Exit game!" << endl;
                            running = false;
                        }
                    }
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
    for(int i = 1; i <= tilemap.numTile; i++)
    {
        SDL_DestroyTexture(tilemap.tileTextures[i]);
    }
}
