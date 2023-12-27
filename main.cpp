#include "include/raylib.h"
#include <cstdio>
#include <math.h> 

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float GRAVITY = 9.8f / 4;

enum TurretType {
    RANGED,
    MELEE
};

struct Entity {
    public:
        float damage;
        float x;
        float y;
        float width;
        float height;

        Entity(){}
};

struct Player : public Entity{
    public:
        float dy = 0;

        Player(float x, float y, float width, float height){
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->damage = damage;
        }

        void update(){
            if(this->y + height < SCREEN_HEIGHT - 50) dy += min(this->y + height - SCREEN_HEIGHT - 50, GRAVITY);
            y+=dy;

            DrawRectangle(this->x, this->y, this->width, this->height, MAROON);
        }

        void jump(){
            dy = -10.0f;
        }
};

struct Turret : public Entity {
    public:
        TurretType type;

        Turret(float x, float y, float damage, TurretType type){
            this->type = type;
        }
        
};

struct Structure {
    public:
        float x;
        float y;
        float width;
        float height;

        Structure(float x, float y, float width, float height){
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        void draw(){
            DrawRectangle(this->x, this->y, this->width, this->height, WHITE);
        }

        bool objectHasCollided(float objectx, float objecty, float objectHeight, float objectWidth){
            float objectBottom = objecty + objectHeight;
            float objectRight = objectx + objectWidth;
            return (objectBottom > x || objectx < x + height) && (objectRight > x || objectx < x + width);
        }
};

Structure ground(0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50);
void drawScene(){
    ClearBackground(BLACK);
    ground.draw();
}

Player player(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, 20, 40);
void drawPlayer(bool alive){
    if(!alive) return;

    if(IsKeyPressed(KEY_SPACE)) player.jump();
    // if(IsKeyDown(KEY_S)) player.y++;
    if(IsKeyDown(KEY_D)) player.x++;
    if(IsKeyDown(KEY_A)) player.x--;

    player.update();
}

int main(void) {
    bool playerAlive = true;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Frvr");
    SetTargetFPS(165);

    InitAudioDevice();

    while (!WindowShouldClose()) {
        BeginDrawing();
            drawScene();
            drawPlayer(playerAlive);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}