#include "raylib.h"
#include "raymath.h"

int main()
{

    // Variables
    int width;
    int height;
    int direction;
    bool collision_with_axe;
    bool gameStarted;

    // Circle Coordinates
    int circle_x;
    int circle_y;
    int circle_radius;

    // Circle Edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    // Axe Coordinates
    int axe_x;
    int axe_y;
    int axe_length;

    // Axe Edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_length};

    // Variables Initialized
    width = 800;
    height = 450;
    circle_x = 200;
    circle_y = 200;
    circle_radius = 25;
    axe_x = 400;
    axe_y = 0;
    axe_length = 50;
    direction = 10;
    gameStarted = false;
    collision_with_axe = 
                    (b_axe_y >= u_circle_y) && 
                    (u_axe_y <= b_circle_y) && 
                    (l_axe_x <= r_circle_x) && 
                    (r_axe_x >= l_circle_x);

    // Main Code
    InitWindow(width, height, "Axe Game");

    SetTargetFPS(60);
    while(WindowShouldClose() == false) {
        // Update Cicrcle Edges
        l_circle_x = circle_x - circle_radius;
        r_circle_x = circle_x + circle_radius;
        u_circle_y = circle_y - circle_radius;
        b_circle_y = circle_y + circle_radius;

        // Update Axe Edges
        l_axe_x = axe_x;
        r_axe_x = axe_x + axe_length;
        u_axe_y = axe_y;
        b_axe_y = axe_y + axe_length;

        // Update Collision With Axe
        collision_with_axe = 
                    (b_axe_y >= u_circle_y) && 
                    (u_axe_y <= b_circle_y) && 
                    (l_axe_x <= r_circle_x) && 
                    (r_axe_x >= l_circle_x);

        BeginDrawing();
        ClearBackground(WHITE);
        
        if (!gameStarted) {
            DrawText("Press SPACE to play!", (width / 6), (height / 2), 50, BLACK);
            if (IsKeyDown(KEY_SPACE)) {
                gameStarted = true;
            }
        }

        else {
            if (collision_with_axe){
                DrawText("Game Over", (width / 2), (height / 2), 20, RED);
            }

            else {
                // Game logic begins here
                DrawCircle(circle_x, circle_y, circle_radius, BLUE);
                DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

                // Move The Axe
                axe_y += direction;
                if (axe_y > height || axe_y < 0) {
                    direction = -direction;
                }
                    
                // Move Circle
                if (IsKeyDown(KEY_D) && circle_x < width) {
                    circle_x += 10;
                }

                if (IsKeyDown(KEY_A) && circle_x > 0) {
                    circle_x -= 10;
                }

                if (IsKeyDown(KEY_W) && circle_y > 0) {
                    circle_y -= 10;
                }

                if (IsKeyDown(KEY_S) && circle_y < height) {
                    circle_y += 10;
                }
                // Game logic ends here
            }
        }

        EndDrawing();
    }
}