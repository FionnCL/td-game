#include "include/raylib.h"
#include <cstdio>
#include <math.h> 

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Pong Frvr");
    SetTargetFPS(165);

    InitAudioDevice();

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}