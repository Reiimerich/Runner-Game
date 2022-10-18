#include "raylib.h"

struct AnimData
{
    Rectangle Rec;
    Vector2 Pos;
    int Frame;
    float UpdateTime;
    float RunningTime;
    int Velocity;
};

bool IsOnGround(AnimData data, int WindowHeight)
{
    return data.Pos.y >= WindowHeight - data.Rec.height;
}

AnimData UpdateAnimData(AnimData data, float DeltaTime, int MaxFrame)
{
    //Update Running Time
    data.RunningTime += DeltaTime;
    if (data.RunningTime >= data.UpdateTime)
    {
        data.RunningTime = 0.0;
        //Update Animation Frame
        data.Rec.x = data.Frame * data.Rec.width;
        data.Frame++;
        if (data.Frame > MaxFrame)
        {
            data.Frame = 0;
        }
    }
    return data;
}

int main()
{
    int WindowDimensions[2]{};
    WindowDimensions[0] = 512; //Width
    WindowDimensions[1] = 380; //Height

    //Create Window
    InitWindow(WindowDimensions[0],WindowDimensions[1],"Runner Game");

    //Player Movement
    int Velocity{0};

    //Background Textures
    Texture2D ScrollingBG = LoadTexture("textures/far-buildings.png");
    Texture2D ScrollingMG = LoadTexture("textures/back-buildings.png");
    Texture2D ScrollingFG = LoadTexture("textures/foreground.png");
    float BGSpeed{};
    float MGSpeed{};
    float FGSpeed{};

    //Physics
    const int Gravity{1'000};
    bool IsJumping{};

    //Obstacle Sprites
    Texture2D Obstacle = LoadTexture("textures/12_nebula_spritesheet.png");

    const int NumberOfObstacleArray{3};
    AnimData ObstacleArray[NumberOfObstacleArray]{};

    for (int i = 0; i < NumberOfObstacleArray; i++)
    {
        ObstacleArray[i].Rec.x = 0.0;
        ObstacleArray[i].Rec.y = 0.0;
        ObstacleArray[i].Rec.width = Obstacle.width/8;
        ObstacleArray[i].Rec.height = Obstacle.height/8;
        ObstacleArray[i].Pos.y = WindowDimensions[1] - Obstacle.height/8;
        ObstacleArray[i].Frame = 0;
        ObstacleArray[i].RunningTime = 0.0;
        ObstacleArray[i].Velocity = -200;
        ObstacleArray[i].UpdateTime = 0.0;
        ObstacleArray[i].Pos.x = WindowDimensions[0] + i * 300;
    }

    float FinishLine{ ObstacleArray[NumberOfObstacleArray - 1].Pos.x};

    //Player Sprites
    Texture2D Player = LoadTexture("textures/scarfy.png");

    AnimData PlayerData{{0.0, 0.0, Player.width/6, Player.height}, //Rectangle Rect
    {WindowDimensions[0]/2 - PlayerData.Rec.width/2, WindowDimensions[1] - PlayerData.Rec.height}, //Vector 2 Position
    0, //Int Frame
    1.0/12.0, //Float Update Time
    0, //Float Running Time
    0}; //Velocity
    //Jump Height (Pixels/Second)
    const int JumpHeight{500};
    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Add DeltaTime to balance framerate
        const float DeltaTime{GetFrameTime()};

        //Start Drawing
        BeginDrawing();
        ClearBackground(BLUE);

        //Draw the Background
        BGSpeed -= 10 * DeltaTime;
        MGSpeed -= 20 * DeltaTime;
        FGSpeed -= 30 * DeltaTime;

        Vector2 BGPos{BGSpeed, 0.0};
        Vector2 BG2Pos{BGSpeed + ScrollingBG.width * 2, 0.0};
        DrawTextureEx(ScrollingBG, BGPos, 0.0, 2.0, WHITE);
        DrawTextureEx(ScrollingBG, BG2Pos, 0.0, 2.0, WHITE);
        Vector2 MGPos{MGSpeed, 0.0};
        Vector2 MG2Pos{MGSpeed + ScrollingBG.width * 2, 0.0};
        DrawTextureEx(ScrollingMG, MGPos, 0.0, 2.0, WHITE);
        DrawTextureEx(ScrollingMG, MG2Pos, 0.0, 2.0, WHITE);
        Vector2 FGPos{FGSpeed, 0.0};
        Vector2 FG2Pos{FGSpeed + ScrollingBG.width * 2, 0.0};
        DrawTextureEx(ScrollingFG, FGPos, 0.0, 2.0, WHITE);
        DrawTextureEx(ScrollingFG, FG2Pos, 0.0, 2.0, WHITE);

        if (BGSpeed <= -ScrollingBG.width*2)
        {
            BGSpeed = 0.0;
        }

        if (FGSpeed <= -ScrollingFG.width*2)
        {
            FGSpeed = 0.0;
        }

        if (MGSpeed <= -ScrollingMG.width*2)
        {
            MGSpeed = 0.0;
        }

        //Apply gravity
        if(IsOnGround(PlayerData, WindowDimensions[1]))
        {
            PlayerData.Velocity = 0;
            IsJumping = false;
        }
        else
        {
            PlayerData.Velocity += Gravity * DeltaTime;
            IsJumping = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !IsJumping)
        {
            PlayerData.Velocity -= JumpHeight;
        }

        //Update Each Obstacle Position
        for (int i = 0; i < NumberOfObstacleArray; i++)
        {
            ObstacleArray[i].Pos.x += ObstacleArray[i].Velocity * DeltaTime;
        }

        //Update Finish Line
        FinishLine += ObstacleArray[0].Velocity * DeltaTime;
        
        //Update X position
        PlayerData.Pos.y += PlayerData.Velocity * DeltaTime;

        //Update running time
        if(!IsJumping)
        {
            PlayerData = UpdateAnimData(PlayerData,DeltaTime,5);
        }

        for (int i = 0; i < NumberOfObstacleArray; i++)
        {
            ObstacleArray[i] = UpdateAnimData(ObstacleArray[i],DeltaTime,7);
        }
        
        for(AnimData Obstacle : ObstacleArray)
        {
            float pad{50};
            Rectangle ObsRec{
                Obstacle.Pos.x + pad,
                Obstacle.Pos.y + pad,
                Obstacle.Rec.width - 2*pad,
                Obstacle.Rec.height - 2*pad
            };

            Rectangle PlayerRec{
                PlayerData.Pos.x,
                PlayerData.Pos.y,
                PlayerData.Rec.width,
                PlayerData.Rec.height
            };

            if(CheckCollisionRecs(ObsRec, PlayerRec))
            {
                collision = true;
            }
        }

        if(collision)
        {
            DrawText("Game Over!", WindowDimensions[0]/3, WindowDimensions[1]/2, 32, YELLOW);
        }
        else if (PlayerData.Pos.x >= FinishLine)
        {
            DrawText("You Win!", WindowDimensions[0]/3, WindowDimensions[1]/2, 32, GREEN);
        }
        else
        {
            //Draw Player
             DrawTextureRec(Player, PlayerData.Rec, PlayerData.Pos, WHITE);

            //Draw Obstacle
            for (int i = 0; i < NumberOfObstacleArray; i++)
            {
                DrawTextureRec(Obstacle, ObstacleArray[i].Rec, ObstacleArray[i].Pos, WHITE);
            }
        }

        //End Drawing
        EndDrawing();
    }
    UnloadTexture(Player);
    UnloadTexture(Obstacle);
    UnloadTexture(ScrollingBG);
    UnloadTexture(ScrollingMG);
    UnloadTexture(ScrollingFG);
    CloseWindow();
}