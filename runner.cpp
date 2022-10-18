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


int main()
{
    int WindowDimensions[2]{};
    WindowDimensions[0] = 512; //Width
    WindowDimensions[1] = 380; //Height

    //Create Window
    InitWindow(WindowDimensions[0],WindowDimensions[1],"Runner Game");

    //Player Movement
    int Velocity{0};

    //Physics
    const int Gravity{1000};
    bool IsJumping{};

    //Obstacle Sprites
    Texture2D Obstacle = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData Obstacle1{{0.0,0.0,Obstacle.width/8, Obstacle.height/8}, //Rectangle Rect
    {WindowDimensions[0], WindowDimensions[1] - Obstacle.height/8}, //Vector 2 Position
    0, //Int Frame
    1.0/12.0, //Float Update Time
    0.0, //Float Running Time
    -200}; //Velocity

    AnimData Obstacle2{{0.0,0.0,Obstacle.width/8, Obstacle.height/8}, //Rectangle Rect
    {WindowDimensions[0] + 300, WindowDimensions[1] - Obstacle.height/8}, //Vector 2 Position
    0, //Int Frame
    1.0/16.0, //Float Update Time
    0.0, //Float Running Time
    -200}; //Velocity

    AnimData Obstacles[2]{Obstacle1, Obstacle2};

    //Player Sprites
    Texture2D Player = LoadTexture("textures/scarfy.png");

    AnimData PlayerData{{0.0, 0.0, Player.width/6, Player.height}, //Rectangle Rect
    {WindowDimensions[0]/2 - PlayerData.Rec.width/2, WindowDimensions[1] - PlayerData.Rec.height}, //Vector 2 Position
    0, //Int Frame
    1.0/12.0, //Float Update Time
    0, //Float Running Time
    0}; //Velocity
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
        if(PlayerData.Pos.y >= WindowDimensions[1] - PlayerData.Rec.height)
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

        //Update Obstacle Position
        Obstacles[0].Pos.x += Obstacles[0].Velocity * DeltaTime;
        Obstacles[1].Pos.x += Obstacles[1].Velocity * DeltaTime;

        //Update X position
        PlayerData.Pos.y += PlayerData.Velocity * DeltaTime;

        //Update running time
        PlayerData.RunningTime += DeltaTime;
        Obstacles[0].RunningTime += DeltaTime;
        

        if (PlayerData.RunningTime >= PlayerData.UpdateTime)
        {
            PlayerData.RunningTime = 0.0;
            if (!IsJumping)
            {
                // update animation frame
                PlayerData.Rec.x = PlayerData.Frame * PlayerData.Rec.width;
                PlayerData.Frame++;
                if (PlayerData.Frame > 5)
                {
                    PlayerData.Frame = 0;
                }
            }
        }

        if (Obstacles[0].RunningTime >= Obstacles[0].UpdateTime)
        {
            Obstacles[0].RunningTime = 0.0;
            Obstacles[0].Rec.x = Obstacles[0].Frame * Obstacles[0].Rec.width;
            Obstacles[0].Frame++;
            if (Obstacles[0].Frame > 7)
            {
                Obstacles[0].Frame = 0;
            }
        }

        Obstacles[1].RunningTime += DeltaTime;
        if (Obstacles[1].RunningTime >= Obstacles[1].UpdateTime)
        {
            Obstacles[1].RunningTime = 0.0;
            Obstacles[1].Rec.x = Obstacles[1].Frame * Obstacles[1].Rec.width;
            Obstacles[1].Frame++;
            if (Obstacles[1].Frame > 7)
            {
                Obstacles[1].Frame = 0;
            }
        }

        //Draw Player
        DrawTextureRec(Player, PlayerData.Rec, PlayerData.Pos, WHITE);

        //Draw Obstacle
        DrawTextureRec(Obstacle, Obstacles[0].Rec, Obstacles[0].Pos, WHITE);
        DrawTextureRec(Obstacle, Obstacles[1].Rec, Obstacles[1].Pos, RED);
        
        //End Drawing
        EndDrawing();
    }
    UnloadTexture(Player);
    UnloadTexture(Obstacle);
    CloseWindow();
}