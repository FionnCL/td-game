#include "include/raylib.h"
#include <cstdio>
#include <math.h> 

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float GRAVITY = 9.8f / 4;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Entity {
    public:
        float x;
        float y;
        float width;
        float height;
        float rightx;
        float bottomy;

        Entity() {}

        Entity(float x, float y, float width, float height){
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->rightx = x + width;
            this->bottomy = y + height;
        }

        void draw(){ DrawRectangle(x, y, width, height, MAROON); }

        bool hasCollided(Entity entity){ return withinYBounds(entity) && withinXBounds(entity); }

        bool withinYBounds(Entity entity){ return ((entity.bottomy >= y && y >= entity.y) || (entity.bottomy >= bottomy && entity.y <= bottomy)); }

        bool withinXBounds(Entity entity){ return ((entity.rightx >= x && x >= entity.x) || (entity.rightx >= rightx && rightx >= entity.x)); }
};

class Structure : public Entity {
    public:
        Structure() {}

        Structure(float x, float y, float width, float height) : Entity(x, y, width, height){ }
};

const int structureCount = 2;
Structure structures[structureCount];

class Player : public Entity {
    public:
        int credits = 0;
        int damage = 8;
        int health = 65;

        Player(float x, float y, float width, float height) : Entity(x, y, width, height){ }

        bool canMove(Direction dir, Structure structures[]){
            bool ableToMove = true;
            for(int i = 0; i < structureCount; i++){
                    Structure currEntity = structures[i];
                    switch(dir){
                        case UP:
                            withinXBounds(currEntity) && (currEntity.bottomy >= bottomy && currEntity.y <= bottomy) ? ableToMove = false: ableToMove = true;
                            break;
                        case DOWN:
                            withinXBounds(currEntity) && (currEntity.bottomy >= y && y >= currEntity.y) ? ableToMove = false: ableToMove = true;
                            break;
                        case LEFT:
                            withinYBounds(currEntity) && (currEntity.rightx >= x && x >= currEntity.x) ? ableToMove = false: ableToMove = true;
                            break;
                        case RIGHT:
                            withinYBounds(currEntity) && (currEntity.rightx >= rightx && rightx >= currEntity.x) ? ableToMove = false: ableToMove = true;
                            break;
                }
                if(!ableToMove){ return false; }
            }
            return true;
        }

        void update(Structure structures[]){
            if(IsKeyDown(KEY_D)) { if(canMove(RIGHT, structures)) { x+=1; rightx+=1; } }
            if(IsKeyDown(KEY_A)) { if(canMove(LEFT, structures)) { x-=1; rightx-=1; } }
            if(IsKeyDown(KEY_S)) { if(canMove(DOWN, structures)) { y+=1; bottomy+=1; } }
            if(IsKeyDown(KEY_W)) { if(canMove(UP, structures)) { y-=1; bottomy-=1; } }
        }
};

void inititializeStructures(){
    Structure floor((float)0, (float)SCREEN_HEIGHT - 50, (float)SCREEN_WIDTH, (float)50);
    Structure wall1((float)SCREEN_WIDTH / 2 + 200, (float) SCREEN_HEIGHT / 2, 50, 200);

    structures[0] = floor;
    structures[1] = wall1;
}

void drawStructures(){
    for(int i = 0; i < structureCount; i++){
        structures[i].draw();
    }
}

int main(void) {
    Player player((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2, 25, 50);

    inititializeStructures();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defensington!?");
    SetTargetFPS(165);

    InitAudioDevice();

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            drawStructures();
            player.update(structures);
            player.draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
