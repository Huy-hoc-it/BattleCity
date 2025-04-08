#include "game.h"

using namespace std;

const int Tank_speed = 3;
const int BULLET_SPEED = 8;

void remake(Box& box, Tilemap& tilemap, vector <Enemy>& enemies, ExplosionManager& explosionManager,
            int& enemy_alive, bool& active, int& shoot_timer, int& enemy_direc_timer, int& score, bool& victory,
            bool& defeat, bool& isPause, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount)
{
    active = false;
    box.x = 0;
    box.y = 0;
    shoot_timer = 0;
    enemy_direc_timer = 0;
    score = 0;
    victory = false;
    defeat = false;
    box.alive = true;
    isPause = false;
    enemy_alive = enemyCount;
    for(int i = 0; i < enemyCount; i++)
    {
        enemies[i].alive = true;
        enemies[i].bullets_enemy.clear();
    }
    box.bullets_main.clear();
    explosionManager.explosions.clear();
    tilemap.loadFromFile("map/map_2.txt");
    enemies.clear();
    spawnEnemies(enemies, enemyCount, tilemap, Tank_speed, SCREEN_HEIGHT, SCREEN_HEIGHT);
}

void game(SDL_Renderer* renderer, TTF_Font* font, map<string, SDL_Texture*>& texture, vector <SDL_Texture*>& explosionTextures,
          map<string, Mix_Chunk*>& media, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount)
{
    srand(time(nullptr));
    SDL_Event e;
    Box box(0, 0, Tank_speed);

    Tilemap tilemap;
    tilemap.loadFromFile("map/map_2.txt");
    tilemap.loadTileTextures(renderer);
    bool running = true;

    vector <Enemy> enemies;

    spawnEnemies(enemies, enemyCount, tilemap, Tank_speed, SCREEN_HEIGHT, SCREEN_HEIGHT);

    int shoot_timer = 0;
    int enemy_direc_timer = 0;
    int delay_timer = 0;

    Menu menu(renderer, texture["Menu_name"], 200, 100, 400, 200);
    menu.buttons.push_back(Button("Start", 350, 380, 100, 50, texture["Start_button"]));
    menu.buttons.push_back(Button("Exit", 350, 450, 100, 50, texture["Exit_button"]));
    Button Try_again = Button("Try_again",200, 380, 100, 50, texture["Try_again"]);
    Button Exit = Button("Exit_end", 500, 380, 100, 50, texture["Exit_button"]);
    Button Play("Play", 200, 380, 100, 50, texture["Play_button"]);
    UI U_Inter(renderer, font, texture["Pause_button"]);

    ExplosionManager explosionManager;
    SoundManager soundManager(media["Start"], media["Exit"], media["Hit"], media["Win"], media["Lose"]);

    int enemy_alive = enemyCount;
    bool victory = false;
    bool defeat = false;

    bool active = false;

    bool isPause = false;
    int score = 0;

    int exit_timer = 0;
    bool exit_clicked = false;

    while(running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        soundManager.resetSoundStates();
        if(active == false){
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    string buttonClicked = menu.handleMouseEvent(mouseX, mouseY);
                    if (buttonClicked == "Start") {
                        cout << "Start game!" << endl;
                        soundManager.playStartButtonSound();
                        active = true;
                    } else if (buttonClicked == "Exit") {
                        cout << "Exit game!" << endl;
                        soundManager.playExitButtonSound();
                        exit_clicked = true;
                    }
                }
            }

            if(exit_clicked == true){
                if(exit_timer < 60){
                    exit_timer++;
                }
                else{
                    exit_timer = 0;
                    running = false;
                }
            }
            soundManager.resetSoundStates();
            SDL_RenderClear(renderer);
            menu.render();
        }
        else{
            if(victory == false && defeat == false){
                if(isPause == false){
                    U_Inter.render(score, SCREEN_WIDTH, SCREEN_HEIGHT);
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
                            case SDLK_SPACE:
                                if(box.alive)box.bullets_main.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2,
                                                                               box.y + box.sizea / 2 - 10 / 2,
                                                                               BULLET_SPEED, box.lastDir));
                            default:
                                break;
                            }
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN){
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;

                            if (U_Inter.pauseButton.isMouseOver(mouseX, mouseY))
                            {
                                isPause = true;
                                soundManager.playExitButtonSound();
                            }
                        }
                    }
                    if (!isPause) {
                        const Uint8* keyState = SDL_GetKeyboardState(NULL);

                        if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]){
                            box.move_left(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        }
                        if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]){
                            box.move_right(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        }
                        if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]){
                            box.move_up(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        }
                        if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]){
                            box.move_down(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        }
                    }

                    box.main_shoot(renderer, enemies, tilemap, explosionManager, explosionTextures, soundManager,
                                   enemyCount, enemy_alive, victory, score, SCREEN_HEIGHT, SCREEN_HEIGHT);
                    if(enemy_alive == 0){
                        if(delay_timer < 60){
                            delay_timer++;
                        }
                        else{
                            delay_timer = 0;
                            victory = true;
                            soundManager.playWinSound();
                        }
                    }

                    for(int i = 0; i < enemyCount; i++){
                        enemies[i].move_enemy(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                    }
                    if(shoot_timer > 60){
                        for(int i = 0; i < enemyCount; i++){
                            enemies[i].enemy_shoot(BULLET_SPEED);
                        }
                        shoot_timer = 0;
                    }
                    if(enemy_direc_timer > 180){
                        for(int i = 0; i < enemyCount; i++){
                            enemies[i].move_direc(tilemap, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        }
                        enemy_direc_timer = 0;
                    }
                    for(int i = 0; i < enemyCount; i++){
                        enemies[i].update_bullets(renderer, box, tilemap, explosionManager, explosionTextures, SCREEN_HEIGHT, SCREEN_HEIGHT);
                    }
                    if(box.alive == false){
                        if(delay_timer < 60){
                            delay_timer++;
                        }
                        else{
                            defeat = true;
                            soundManager.playLoseSound();
                            delay_timer = 0;
                        }
                    }

                    box.render(renderer, texture["tank_main"]);
                    for(int i = 0; i < enemyCount; i++){
                        enemies[i].render_enemy(renderer, texture["tank_enemy"]);
                    }
                    tilemap.render_map(renderer);
                    explosionManager.updateExplosions();
                    explosionManager.renderExplosions(renderer);
                }
                else{
                    Play.render(renderer);
                    Exit.render(renderer);
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_QUIT) running = false;
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;

                            if (Play.isMouseOver(mouseX, mouseY)) {
                                cout << "Try again!" << endl;
                                soundManager.playExitButtonSound();
                                isPause = false;
                            }
                            else if (Exit.isMouseOver(mouseX, mouseY)) {
                                cout << "Exit game!" << endl;
                                soundManager.playExitButtonSound();
                                exit_clicked = true;
                            }
                        }
                    }
                    if(exit_clicked == true){
                        if(exit_timer < 60){
                            exit_timer++;
                        }
                        else{
                            exit_timer = 0;
                            running = false;
                        }
                    }
                }
            }
            else if(victory == true){
                renderTexture(texture["You_win"], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FLIP_NONE, renderer);
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
                            remake(box, tilemap, enemies, explosionManager, enemy_alive, active,
                                   shoot_timer, enemy_direc_timer, score, victory,
                                   defeat, isPause, SCREEN_HEIGHT, SCREEN_HEIGHT, enemyCount);
                            soundManager.playExitButtonSound();
                        }
                        else if (Exit.isMouseOver(mouseX, mouseY)) {
                            cout << "Exit game!" << endl;
                            soundManager.playExitButtonSound();
                            exit_clicked = true;
                        }
                    }
                }
                if(exit_clicked == true){
                    if(exit_timer < 60){
                        exit_timer++;
                    }
                    else{
                        exit_timer = 0;
                        running = false;
                    }
                }
            }
            else if(defeat == true){
                renderTexture(texture["You_lose"], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FLIP_NONE, renderer);
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
                            remake(box, tilemap, enemies, explosionManager, enemy_alive, active,
                                   shoot_timer, enemy_direc_timer, score, victory,
                                   defeat, isPause, SCREEN_HEIGHT, SCREEN_HEIGHT, enemyCount);
                            soundManager.playExitButtonSound();
                        }
                        else if (Exit.isMouseOver(mouseX, mouseY)) {
                            cout << "Exit game!" << endl;
                            soundManager.playExitButtonSound();
                            exit_clicked = true;
                        }
                    }
                }
                if(exit_clicked == true){
                    if(exit_timer < 60){
                        exit_timer++;
                    }
                    else{
                        exit_timer = 0;
                        running = false;
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    for(int i = 1; i <= tilemap.numTile; i++)
    {
        SDL_DestroyTexture(tilemap.tileTextures[i]);
    }
    tilemap.tileTextures.clear();
}
