#include "raylib.h"

int main()
{
    //Window Dimensions
    const int WindowHeight{600};
    const int WindowWidth{900};
    //Create Window
    InitWindow(WindowWidth,WindowHeight,"Runner Game");

    //Player Movement
    int Velocity{0};

    //Physics
    const int Gravity{1'000};
    bool IsJumping{};

    //Sprites
    Texture2D Player = LoadTexture("textures/scarfy.png");
    Rectangle PlayerRec;
    PlayerRec.width = Player.width/6;
    PlayerRec.height = Player.height;
    PlayerRec.x = 0;
    PlayerRec.y = 0;

    //Sprite position
    Vector2 PlayerPos;
    PlayerPos.x = WindowWidth/2 - PlayerRec.width/2;
    PlayerPos.y = WindowHeight - PlayerRec.height;

    //Jump Height (Pixels/Second)
    const int JumpHeight{600};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Add DeltaTime to balance framerate
        const float DeltaTime{GetFrameTime()};

        //Start Drawing
        BeginDrawing();
        ClearBackground(BLUE);

        

        //Apply gravity
        if(PlayerPos.y >= WindowHeight - PlayerRec.height)
        {
            Velocity = 0;
            IsJumping = false;
        }
        else
        {
            Velocity += Gravity * DeltaTime;
            IsJumping = true;
        }

        //Draw Player
        DrawTextureRec(Player, PlayerRec, PlayerPos, WHITE);

        if(IsKeyPressed(KEY_SPACE) && !IsJumping)
        {
            Velocity -= JumpHeight;
        }

        //Update X position
        PlayerPos.y += Velocity * DeltaTime;

        //End Drawing
        EndDrawing();
    }
    UnloadTexture(Player);
    CloseWindow();
}