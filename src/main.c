#include <math.h>
#include <stdio.h>

#include "constants.h"
#include "raylib.h"
#include "spaceship.h"
spaceship_t sship;
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);  // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib");
    sship.icon = LoadTexture("resources/spaceship.png");
    sship = (spaceship_t){{screenWidth / 2 - sship.icon.width / 2, screenHeight / 2 - sship.icon.height / 2},
                          {0, -10},
                          sship.icon,
                          0,sship.icon.width/4,sship.icon.height/4};
    /*sship = (spaceship_t){{screenWidth / 2, screenHeight / 2},
                          {0, -1},
                          sship.icon,
                          0};*/
    sship.angle = 0;
    // DisableCursor();

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
// Update and draw game frame
static void UpdateDrawFrame(void) {
    // Update
    update_spaceship(&sship);
    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(RAYWHITE);

    
    draw_spaceship(&sship);
    DrawText(TextFormat("Angolo:%d", sship.angle), 10, 60, 20, DARKGRAY);
    DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}