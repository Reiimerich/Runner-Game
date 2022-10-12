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
    const int Gravity{1000};
    bool IsJumping{};

    //Player Animation Frame
    int Frame{};
    const float UpdateTime{1.0/12.0};
    float RunningTime{};

    //Obstacle Sprites
    Texture2D Obstacle = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle ObstacleRec{0.0, 0.0, Obstacle.width/8, Obstacle.height/8};
    Vector2 ObstaclePos{WindowWidth, WindowHeight - ObstacleRec.height};

    Rectangle Obstacle2Rec{0.0, 0.0, Obstacle.width/8, Obstacle.height/8};
    Vector2 Obstacle2Pos{WindowWidth + 300, WindowHeight - ObstacleRec.height};

    //Obstacle Animation Frame
    int ObsFrame{};
    const float ObstacleUpdateTime{1.0/12.0};
    float ObstacleRunningTime{};

    int ObsFrame2{};
    const float Obstacle2UpdateTime{1.0/16.0};
    float Obstacle2RunningTime{};

    //Obstacle velocity
    int ObstacleVel{-600};
    
    //Player Sprites
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

        if(IsKeyPressed(KEY_SPACE) && !IsJumping)
        {
            Velocity -= JumpHeight;
        }

        //Update Obstacle Position
        ObstaclePos.x += ObstacleVel * DeltaTime;

        //Update X position
        PlayerPos.y += Velocity * DeltaTime;

        //Update running time
        RunningTime += DeltaTime;
        ObstacleRunningTime += DeltaTime;

        if (RunningTime >= UpdateTime)
        {
            RunningTime = 0.0;
            if (!IsJumping)
            {
                // update animation frame
                PlayerRec.x = Frame * PlayerRec.width;
                Frame++;
                if (Frame > 5)
                {
                    Frame = 0;
                }
            }
        }

        if (ObstacleRunningTime >= ObstacleUpdateTime)
        {
            ObstacleRunningTime = 0.0;
            ObstacleRec.x = ObsFrame * ObstacleRec.width;
            ObsFrame++;
            if (ObsFrame > 7)
            {
                ObsFrame = 0;
            }
        }

        if (Obstacle2RunningTime >= Obstacle2UpdateTime)
        {
            Obstacle2RunningTime = 0.0;
            Obstacle2Rec.x = ObsFrame2 * Obstacle2Rec.width;
            ObsFrame2++;
            if (ObsFrame2 > 7)
            {
                ObsFrame2 = 0;
            }
        }

        //Draw Player
        DrawTextureRec(Player, PlayerRec, PlayerPos, WHITE);

        //Draw Obstacle
        DrawTextureRec(Obstacle, ObstacleRec, ObstaclePos, WHITE);
        DrawTextureRec(Obstacle, Obstacle2Rec, Obstacle2Pos, WHITE);
        
        //End Drawing
        EndDrawing();
    }
    UnloadTexture(Player);
    UnloadTexture(Obstacle);
    CloseWindow();
}