#include "raylib.h"

int main()
{

    //Variables
    int width;
    int height;


    //Variables Initialized
    width = 350;
    height = 200;


    //Main Code
    InitWindow(width, height, "Axe Game");

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(WHITE);

        EndDrawing();
    }
}