#include <math.h>
#include <stdio.h>
#include "raylib.h"

#include "constants.h"
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
    sship=(spaceship_t){{screenWidth/2,screenHeight/2},{0,0}};
    

    InitWindow(screenWidth, screenHeight, "raylib");
    sship.icon=LoadTexture("resources/spaceship.png");
 

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
    DrawText(TextFormat("Velocita' max:%.2f", 2), 10, 60, 20, DARKGRAY);
    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}