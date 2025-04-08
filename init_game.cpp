#include "init_game.h"

using namespace std;

enum Direction;

void Bullet::move()
{
    switch (dir)
    {
    case LEFT:
        x -= Bullet_speed;
        break;
    case RIGHT:
        x += Bullet_speed;
        break;
    case UP:
        y -= Bullet_speed;
        break;
    case DOWN:
        y += Bullet_speed;
        break;
    }
}

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_Rect bullet_rect = { x, y, size_b, size_b };
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); // Màu xám
    SDL_RenderFillRect(renderer, &bullet_rect);
}

bool Bullet::isInside(int minX, int minY, int maxX, int maxY)
{
    return (x >= minX && y >= minY && x + size_b <= maxX && y + size_b <= maxY);
}

bool Bullet::collision_bullet_wall(vector < vector <int> >& tiles, int tileSize)
{
    int tileX_upon = x / tileSize;
    int tileY_upon = y / tileSize;
    int tileX_bottom = (x + size_b - 1) / tileSize;
    int tileY_bottom = (y + size_b - 1) / tileSize;

    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= int(tiles.size()) || tileY_bottom >= int(tiles.size())) return false;
    if((tiles[tileX_upon][tileY_upon] >= 1 && tiles[tileX_upon][tileY_upon] != 3) ||
       (tiles[tileX_bottom][tileY_bottom] >= 1 && tiles[tileX_bottom][tileY_bottom] != 3) ||
       (tiles[tileX_upon][tileY_bottom] >= 1 && tiles[tileX_upon][tileY_bottom] != 3) ||
       (tiles[tileX_bottom][tileY_upon] >= 1 && tiles[tileX_bottom][tileY_upon] != 3)){

        if(tiles[tileX_upon][tileY_upon] == 1) tiles[tileX_upon][tileY_upon] = 0;
        if(tiles[tileX_bottom][tileY_bottom] == 1) tiles[tileX_bottom][tileY_bottom] = 0;
        if(tiles[tileX_upon][tileY_bottom] == 1) tiles[tileX_upon][tileY_bottom] = 0;
        if(tiles[tileX_bottom][tileY_upon] == 1) tiles[tileX_bottom][tileY_upon] = 0;
        return true; // đụng tường
    }
    return false;
}

bool Bullet::collision_bullet_tank_enemy(Enemy& enemy)
{
    SDL_Rect bulletRect = {x, y, size_b, size_b};
    SDL_Rect enemyRect = {enemy.x, enemy.y, enemy.size_enemy, enemy.size_enemy};

    if(SDL_HasIntersection(&bulletRect, &enemyRect) && enemy.alive == true){
        return true;
    }

    return false;
}

bool Bullet::collision_bullet_tank_main(Box& box)
{
    SDL_Rect bulletRect = {x, y, size_b, size_b};
    SDL_Rect boxRect = {box.x, box.y, box.sizea, box.sizea};

    if(SDL_HasIntersection(&bulletRect, &boxRect) && box.alive == true){
        return true;
    }

    return false;
}

void Box::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    if(alive){
        renderTexture(texture, x, y, sizea, sizea, dir_img, flip, renderer);
    }
    else{
        return;
    }
}

bool Box::checkCollision(Tilemap& tilemap)
{
    int tileX_upon = x / tilemap.tileSize;
    int tileY_upon = y / tilemap.tileSize;
    int tileX_bottom = (x + sizea - 1) / tilemap.tileSize;
    int tileY_bottom = (y + sizea - 1) / tilemap.tileSize;
    //cout << tileX_upon << " " << tileY_upon << " " << tileX_bottom << " " << tileY_bottom << endl;
    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= int(tilemap.tiles.size()) || tileY_bottom >= int(tilemap.tiles.size())) return false;
    if((tilemap.tiles[tileX_upon][tileY_upon] > 0 && tilemap.tiles[tileX_upon][tileY_upon] != 3) ||
       (tilemap.tiles[tileX_bottom][tileY_bottom] > 0 && tilemap.tiles[tileX_bottom][tileY_bottom] != 3) ||
       (tilemap.tiles[tileX_upon][tileY_bottom] > 0 && tilemap.tiles[tileX_upon][tileY_bottom] != 3) ||
       (tilemap.tiles[tileX_bottom][tileY_upon] > 0 && tilemap.tiles[tileX_bottom][tileY_upon] != 3)){
        return true; // đụng tường
    }
    return false;
}

void Box::move_left(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        if(x - speed >= 0)x -= speed;
        lastDir = LEFT;
        dir_img = 270;
        if(checkCollision(tilemap)){
            x += speed;
            return;
        }
    }
    else{
        return;
    }
}

void Box::move_right(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        if(x + sizea + speed <= SCREEN_WIDTH)x += speed;
        lastDir = RIGHT;
        dir_img = 90;
        if(checkCollision(tilemap)){
            x -= speed;
            return;
        }
    }
    else{
        return;
    }
}

void Box::move_up(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        if(y - speed >= 0)y -= speed;
        lastDir = UP;
        dir_img = 0;
        if(checkCollision(tilemap)){
            y += speed;
            return;
        }
    }
    else{
        return;
    }
}

void Box::move_down(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        if(y + sizea + speed <= SCREEN_HEIGHT)y += speed;
        lastDir = DOWN;
        dir_img = 180;
        if(checkCollision(tilemap)){
            y -= speed;
            return;
        }
    }
    else{
        return;
    }
}

void Box::main_shoot(SDL_Renderer* renderer,vector<Enemy>& enemies, Tilemap& tilemap, ExplosionManager& explosionManager,
                     vector <SDL_Texture*>& explosionTextures, SoundManager& soundManager, int enemyCount, int& enemy_alive,
                     bool& victory, int& score, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        for (size_t i = 0; i < bullets_main.size(); ) // size_t: kieu du lieu unsigned, khong am
        {
            bullets_main[i].move();
            if (!bullets_main[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) || bullets_main[i].collision_bullet_wall(tilemap.tiles, tilemap.tileSize))
            {
                bullets_main.erase(bullets_main.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình hoặc chạm vào tường gạch
            }
            else
            {
                for(int j = 0; j < enemyCount; j++){
                    if(bullets_main[i].collision_bullet_tank_enemy(enemies[j])){
                        explosionManager.addExplosion(enemies[j].x, enemies[j].y, explosionTextures);
                        enemies[j].alive = false;
                        enemy_alive--;
                        bullets_main.erase(bullets_main.begin() + i);
                        soundManager.playHitEnemySound();
                        score += 100;
                    }
                }
                bullets_main[i].render(renderer);
                ++i;
            }
        }
    }
}

bool Box::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + sizea <= maxX && y + sizea <= maxY);
}

bool Enemy::Collision_Enemy_Wall(Tilemap& tilemap){
    int tileX_upon = x / tilemap.tileSize;
    int tileY_upon = y / tilemap.tileSize;
    int tileX_bottom = (x + size_enemy - 1) / tilemap.tileSize;
    int tileY_bottom = (y + size_enemy - 1) / tilemap.tileSize;
    //cout << tileX_upon << " " << tileY_upon << " " << tileX_bottom << " " << tileY_bottom << endl;
    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= int(tilemap.tiles.size()) || tileY_bottom >= int(tilemap.tiles.size())) return false;
    if((tilemap.tiles[tileX_upon][tileY_upon] > 0 && tilemap.tiles[tileX_upon][tileY_upon] != 3) ||
       (tilemap.tiles[tileX_bottom][tileY_bottom] > 0 && tilemap.tiles[tileX_bottom][tileY_bottom] != 3) ||
       (tilemap.tiles[tileX_upon][tileY_bottom] > 0 && tilemap.tiles[tileX_upon][tileY_bottom] != 3) ||
       (tilemap.tiles[tileX_bottom][tileY_upon] > 0 && tilemap.tiles[tileX_bottom][tileY_upon] != 3)){
        return true; // đụng tường
    }
    return false;
}

bool Enemy::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + size_enemy <= maxX && y + size_enemy <= maxY);
}

void Enemy::move_enemy(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive == true){
        x = x + dx;
        y = y + dy;

        if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
            x -= dx;
            y -= dy;

            Direction direc = (Direction)(rand() % 4);
            if(direc == LEFT){
                dx = -speed;
                dy = 0;
                lastDir = LEFT;
                dir_img = 270;
            }
            else if(direc == RIGHT){
                dx = speed;
                dy = 0;
                lastDir = RIGHT;
                dir_img = 90;
            }
            else if(direc == UP){
                dx = 0;
                dy = -speed;
                lastDir = UP;
                dir_img = 0;
            }
            else{
                dx = 0;
                dy = speed;
                lastDir = DOWN;
                dir_img = 180;
            }
        }
    }
    else{
        return;
    }
}

void Enemy::render_enemy(SDL_Renderer* renderer, SDL_Texture* texture)
{
    if(alive == true){
        renderTexture(texture, x, y, size_enemy, size_enemy, dir_img, flip, renderer);
    }
    else{
        return;
    }
}

void Enemy::enemy_shoot(const int BULLET_SPEED)
{
    if(alive == true) bullets_enemy.push_back(Bullet(x + size_enemy / 2 - 10 / 2, y + size_enemy / 2 - 10 / 2, BULLET_SPEED, lastDir));
    else{
        return;
    }
}

void Enemy::update_bullets(SDL_Renderer* renderer, Box& box, Tilemap& tilemap, ExplosionManager& explosionManager,
                     vector <SDL_Texture*>& explosionTextures, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive){
        for (size_t i = 0; i < bullets_enemy.size(); ) // size_t: kieu du lieu unsigned, khong am
        {
            bullets_enemy[i].move();
            if (!bullets_enemy[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) || bullets_enemy[i].collision_bullet_wall(tilemap.tiles, tilemap.tileSize))
            {
                bullets_enemy.erase(bullets_enemy.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình hoặc chạm vào tường gạch
            }
            else
            {
                if(bullets_enemy[i].collision_bullet_tank_main(box)){
                    explosionManager.addExplosion(box.x, box.y, explosionTextures);
                    box.alive = false;
                    bullets_enemy.erase(bullets_enemy.begin() + i);
                }
                bullets_enemy[i].render(renderer);
                ++i;
            }
        }
    }
    else{
        return;
    }
}

void Enemy::move_direc(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(alive == true){
        Direction direc = (Direction)(rand() % 4);
        if(direc == LEFT)
        {
            int dx_old = dx;
            int dy_old = dy;
            dx = -speed;
            dy = 0;
            x += dx;
            y += dy;
            if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
                x -= dx;
                y -= dy;
                dx = dx_old;
                dy = dy_old;
                return;
            }
            else{
                x -= dx;
                y -= dy;
            }
            lastDir = LEFT;
            dir_img = 270;
        }
        else if(direc == RIGHT)
        {
            int dx_old = dx;
            int dy_old = dy;
            dx = speed;
            dy = 0;
            x += dx;
            y += dy;
            if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
                x -= dx;
                y -= dy;
                dx = dx_old;
                dy = dy_old;
                return;
            }
            else{
                x -= dx;
                y -= dy;
            }
            lastDir = RIGHT;
            dir_img = 90;
        }
        else if(direc == UP)
        {
            int dx_old = dx;
            int dy_old = dy;
            dx = 0;
            dy = -speed;
            x += dx;
            y += dy;
            if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
                x -= dx;
                y -= dy;
                dx = dx_old;
                dy = dy_old;
                return;
            }
            else{
                x -= dx;
                y -= dy;
            }
            lastDir = UP;
            dir_img = 0;
        }
        else
        {
            int dx_old = dx;
            int dy_old = dy;
            dx = 0;
            dy = speed;
            x += dx;
            y += dy;
            if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
                x -= dx;
                y -= dy;
                dx = dx_old;
                dy = dy_old;
                return;
            }
            else{
                x -= dx;
                y -= dy;
            }
            lastDir = DOWN;
            dir_img = 180;
        }
    }
    else{
        return;
    }
}

void getRandomPosition(Tilemap& tilemap, int& x, int& y, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    while(true){
        x = rand() % (SCREEN_WIDTH / tilemap.tileSize);
        y = rand() % (SCREEN_HEIGHT / tilemap.tileSize);

        if(tilemap.tiles[x][y] == 0 && x >= 5 && y >= 5){
            break;
        }
    }
    x *=tilemap.tileSize;
    y *=tilemap.tileSize;
}

void spawnEnemies(vector <Enemy>& enemies, int enemyCount, Tilemap tilemap, const int Tank_speed, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    enemies.clear();

    for(int i = 0; i < enemyCount; i++){
        int x, y;
        getRandomPosition(tilemap, x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
        enemies.push_back(Enemy(x, y, Tank_speed));
    }
}
