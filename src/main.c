#include <math.h>
#include <stdio.h>

#include "asteroid.h"
#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"
spaceship_t sship;
extern asteroid_t asteroids[];
extern size_t n_asteroids;

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
    init_spaceship(&sship);
    for (size_t i = 0; i < n_asteroids; i++) {
        init_rand_asteroid(&asteroids[i]);
    }

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
    queue_proj_t* proj = &sship.projectiles;
    update_projectiles(proj);
    update_spaceship(&sship);
    for (size_t i = 0; i < n_asteroids; i++) {
        update_asteroid(&asteroids[i]);
    }

    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_spaceship(&sship);
    draw_projectiles(sship.projectiles.projectiles_arr, sship.projectiles.size_projectile_arr,
                     sship.projectiles.i_first_projectile);

    // DrawText(TextFormat("Angolo:%d", sship.angle), 10, 60, 20, DARKGRAY);
    // DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    DrawFPS(10, 10);

    for (size_t i = 0; i < n_asteroids; i++) {
        draw_asteroid(&asteroids[i]);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
}