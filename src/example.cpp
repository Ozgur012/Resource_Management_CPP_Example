#include <iostream>
#include "raylib.h"

int main()
{
    InitWindow(600, 600, "Resource Management Example");
    InitAudioDevice();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);


        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    

    return 0;
}