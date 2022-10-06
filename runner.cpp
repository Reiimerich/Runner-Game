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

    //Physics
    const int Gravity{1};

    //Create Window
    InitWindow(WindowWidth,WindowHeight,"Runner Game");
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(BLUE);

        //Apply gravity
        if(InitialPositionY >= WindowHeight - height)
        {
            Velocity = 0;
        }
        else
        {
            Velocity += Gravity;
        }

        //Draw Rectangle
        DrawRectangle(WindowWidth/2, InitialPositionY, width,height,RED);

        if(IsKeyPressed(KEY_SPACE))
        {
            Velocity = -10;
        }

        //Update X position
        InitialPositionY += Velocity;

        //End Drawing
        EndDrawing();
    }
    CloseWindow();
}