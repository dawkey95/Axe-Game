#include "raylib.h"
#include "raymath.h"

    //  Window Dimensions
    int windowWidth = 800;
    int windowHeight = 450;

    //  Player Circle
    int playerCenterX = 200;
    int playerCenterY = 200;
    int playerRadius = 25;

    //  Obstacle Circle
    int obstacleCenterX = 400;
    int obstacleCenterY = 25;
    int obstacleRadius = 25;
    float directionV = 5;
    float directionH = 5;

    //  Collisions
    float tolerance = playerRadius = obstacleRadius;
    float goal = (5 * playerRadius) + obstacleRadius;
    bool collisionWithObstacle{};
    bool collisionWithScoringZone{};
    float distance{};

    //  Color Definitions
    Color CYAN = {0, 255, 255, 255};
    Color ScoreColor = CYAN;
    Color PlayerColor = DARKGRAY;
    Color ObstacleColor = MAROON;
    Color BackgroundColor = BLACK;
    Color Flicker[]{DARKGRAY, GRAY, LIGHTGRAY, WHITE};
    int FlickerSize = 4;

    //  Title
    int BouncingAmount = 20;
    int BouncingDirection = 1;
    int BouncingOffset = 0;
    int LetterOffset = 10;

    // Gameplay
    int PlayerSpeed = 10;
    int Score = 0;
    int Delay = 2*60;
    int Timer = Delay;
    int GameStarted = false;

    void DisplayTitle(float PercentScreenWidth, float PercentScreenHeight)
{   
    if(BouncingOffset < -BouncingAmount || BouncingOffset > BouncingAmount) {
        BouncingDirection = -BouncingDirection;        
    }

    BouncingOffset += BouncingDirection;
    DrawText(TextFormat(" D   D   E   A   L "),
                        (windowWidth*(PercentScreenWidth/100)) - LetterOffset, 
                        (windowHeight*(PercentScreenHeight/100)) + BouncingOffset, 
                        80, 
                        ObstacleColor);

    DrawText(TextFormat("   O   G   B   L   ! "), 
                        (windowWidth*(PercentScreenWidth/100)), 
                        (windowHeight*(PercentScreenHeight/100)) - BouncingOffset, 
                        80, 
                        ScoreColor);
}

bool UseWASDToProceed(float PercentScreenWidth, float PercentScreenHeight)
{
    // Current Game Time (reduced to a whole number) divided by the length of the Flicker array 
    // leaves me a remainder I may use to count through the colors  Modulus FTW!
    int Sequencer = (int)GetTime() % FlickerSize; 
    DrawText("Press W, A, S, or D\n  or   Esc to Quit", (windowWidth * (PercentScreenWidth / 100)), (windowHeight * (PercentScreenHeight / 100)), 15, Flicker[Sequencer]);
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D))
    {
        return true;
    }
    return false;
}

void UpdateDistanceCheck()
{
    distance = sqrt(pow(playerCenterX - obstacleCenterX, 2) + pow(playerCenterY - obstacleCenterY, 2));
    collisionWithObstacle = distance < tolerance;
    collisionWithScoringZone = distance < goal;
}

void ResetGameVariables()
{
    playerCenterX = 200;
    playerCenterY = 200;
    obstacleCenterX = 400;
    obstacleCenterY = 25; 
    Timer = Delay;
    Score = 0;
    collisionWithObstacle = false;
}

void CalculateAndIndicateScoring()
{
    if (collisionWithScoringZone)
    {
        // increase score based on the distance from the obstacle but never less than 1 
        Score += ((goal-distance)/playerRadius)+1;
        // recolor the obstacle
        DrawCircle(obstacleCenterX, obstacleCenterY, obstacleRadius, ScoreColor);   
    }
}

void DrawScorePlayerAndObstacle()
{
    DrawText(TextFormat("Score: %i", Score), windowWidth*.85, windowHeight*.9, 20, ScoreColor);
    DrawCircle(playerCenterX, playerCenterY, playerRadius, PlayerColor);
    DrawCircle(obstacleCenterX, obstacleCenterY, obstacleRadius, ObstacleColor);
}

void BouncyBallMovement()
{
    obstacleCenterY += directionV;
    if (obstacleCenterY > (windowHeight-obstacleRadius) || (obstacleCenterY < obstacleRadius))
    {
        directionV = -directionV;
    }
    obstacleCenterX += directionH;
    if (obstacleCenterX > (windowWidth-obstacleRadius) || (obstacleCenterX < obstacleRadius))
    {
        directionH = -directionH;
    }    
}

void ProcessGameControls()
{
    if (IsKeyDown(KEY_D) && (playerCenterX+playerRadius) < windowWidth)
    {
        playerCenterX += PlayerSpeed;
    }
    if (IsKeyDown(KEY_A) && (playerCenterX-playerRadius) > 0)
    {
        playerCenterX -= PlayerSpeed;
    }
    if (IsKeyDown(KEY_W) && (playerCenterY-playerRadius) > 0)
    {
        playerCenterY = playerCenterY - PlayerSpeed;
    }
    if (IsKeyDown(KEY_S) && (playerCenterY+playerRadius) < windowHeight)
    {
        playerCenterY = playerCenterY + PlayerSpeed;
    }
}

int main()
{
    InitWindow(windowWidth, windowHeight, "W/A/S/D Finger Trainer");
    SetTargetFPS(60);

    while(!WindowShouldClose())          
    {
        BeginDrawing();                  
        ClearBackground(BackgroundColor);      
        UpdateDistanceCheck();
        // Start Screen
        if (!GameStarted)
        {
            DisplayTitle(5, 40);
            if(UseWASDToProceed(40, 70))
            {
                GameStarted = true;
            }
        }
        else
        {
            // End Screen   
            if(collisionWithObstacle)
            {
                DisplayTitle(5, 10);
                DrawText(TextFormat("Score: %i", Score), windowWidth * .33, windowHeight * .4, 55, ScoreColor);
                DrawText("Did You Improve?", windowWidth * .33, windowHeight * .5, 30, ObstacleColor);
                if(Timer <= 0)
                {
                    DrawText("Try Again!", windowWidth * .42, windowHeight * .58, 20, PlayerColor);
                    if(UseWASDToProceed(40, 65))
                    {
                        ResetGameVariables();
                    }
                }
                else
                {
                    Timer--;
                }
            }
            // GamePlay
            else
            {
                DrawScorePlayerAndObstacle();
                CalculateAndIndicateScoring();
                BouncyBallMovement();
                ProcessGameControls();
            } 
        }
    EndDrawing();
    }
}