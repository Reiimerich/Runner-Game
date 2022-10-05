#include "raylib.h"

int main()
{
    //Window Dimensions
    const int WindowHeight{600};
    const int WindowWidth{900};

    //Rectangle Dimensions
    const int width{50};
    const int height{80};

    //Player Movement
    int InitialPositionY{WindowHeight - height};
    int Velocity{0};

    //Create Window
    InitWindow(WindowWidth,WindowHeight,"Runner Game");
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(BLUE);

        //Update X position
        InitialPositionY += Velocity;

        //Draw Rectangle
        DrawRectangle(WindowWidth/2, InitialPositionY, width,height,RED);

        if(IsKeyPressed(KEY_SPACE))
        {
            Velocity = -10;
        }

        //End Drawing
        EndDrawing();
    }
    CloseWindow();
}