#include <math.h>
#include <stdio.h>

#include "asteroid.h"
#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"
spaceship_t sship;
asteroid_t asteroids[MAX_ASTEROIDS];
size_t n_asteroids = 12;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(float);  // Update and draw one frame

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

    SetTargetFPS(144);  // Set our game to run at 60 frames-per-second
    //TODO LA  NAVICELLA SPARA PIU VELOCEMNTE CON FPS PIU ALTI
    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        double delta_time = GetFrameTime();
        UpdateDrawFrame(delta_time);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
// Update and draw game frame
static void UpdateDrawFrame(float delta_time) {
    // Update
    queue_proj_t* proj = &sship.projectiles;

    update_spaceship(&sship,delta_time);
    collision_projectiles_asteroids(asteroids, n_asteroids, sship.projectiles.projectiles_arr,
                                    sship.projectiles.size_projectile_arr,
                                    sship.projectiles.i_first_projectile);

    update_projectiles(proj,delta_time);
    for (size_t i = 0; i < n_asteroids; i++) {
        update_asteroid(&asteroids[i],delta_time);
    }

    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_spaceship(&sship);
    draw_projectiles(sship.projectiles.projectiles_arr, sship.projectiles.size_projectile_arr,
                     sship.projectiles.i_first_projectile);

    //DrawText(TextFormat("Angolo:%f", sship.angle), 10, 60, 20, DARKGRAY);
    //DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    DrawFPS(10, 10);

    for (size_t i = 0; i < n_asteroids; i++) {
        draw_asteroid(&asteroids[i]);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
}