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
    bool IsJumping{};

    //Sprites
    Texture2D Player = LoadTexture("textures/monster.png");
    Rectangle PlayerRec;
    Vector2 PlayerPos;

    //Jump Height
    const int JumpHeight{20};

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
            IsJumping = false;
        }
        else
        {
            Velocity += Gravity;
            IsJumping = true;
        }

        //Draw Rectangle
        DrawRectangle(WindowWidth/2, InitialPositionY, width,height,RED);

        if(IsKeyPressed(KEY_SPACE) && !IsJumping)
        {
            Velocity -= JumpHeight;
        }

        //Update X position
        InitialPositionY += Velocity;

        //End Drawing
        EndDrawing();
    }
    CloseWindow();
}