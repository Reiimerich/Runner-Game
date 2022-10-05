#include "raylib.h"

int main()
{
    //Window Dimensions
    int WindowHeight{600};
    int WindowWidth{900};

    //Create Window
    InitWindow(WindowWidth,WindowHeight,"Runner Game");
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(BLUE);

        //End Drawing
        EndDrawing();
    }
    CloseWindow();
}