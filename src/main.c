#include <math.h>
#include <stdio.h>

#include "asteroid.h"
#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"
spaceship_t sship;
asteroid_t asteroids[MAX_ASTEROIDS*5];
size_t n_asteroids_alive;
unsigned int current_level;
// size_t n_asteroids;
//  #define QUADRATO_DEBUG  // TODO RIMUOVI QUANDO HAI FINITO

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

    n_asteroids_alive = INITIAL_ASTEROIDS;
    current_level = 1;

    init_spaceship(&sship);
    for (size_t i = 0; i < MAX_ASTEROIDS; i++) {
        if (i % N_BLOCK_OF_ASTEROID_FAMILY == 0) {
            init_rand_asteroid(&asteroids[i]);
        } else {
            asteroids[i].flag = ASTFLAG_UNINITIALIZED;
        }
    }

    // DisableCursor();

    SetTargetFPS(144);  // Set our game to run at 60 frames-per-second
    // TODO LA  NAVICELLA SPARA PIU VELOCEMNTE CON FPS PIU ALTI
    //  Main game loop
    while (!WindowShouldClose()) {  // Detect window close button or ESC key
        double delta_time = GetFrameTime();
        UpdateDrawFrame(delta_time);
        if (n_asteroids_alive == 0) {
            current_level++;
            for (size_t i = 0; i < MAX_ASTEROIDS; i++) {
                if (i % N_BLOCK_OF_ASTEROID_FAMILY == 0) {
                    init_rand_asteroid(&asteroids[i]);
                } else {
                    asteroids[i].flag = ASTFLAG_UNINITIALIZED;
                }
            }
            n_asteroids_alive=INITIAL_ASTEROIDS;
        }
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

    update_spaceship(&sship, delta_time);
    collision_projectiles_asteroids(asteroids, MAX_ASTEROIDS, sship.projectiles.projectiles_arr,
                                    sship.projectiles.size_projectile_arr,
                                    sship.projectiles.i_first_projectile, &n_asteroids_alive);

    update_projectiles(proj, delta_time);
    update_asteroids(asteroids, MAX_ASTEROIDS, delta_time);
    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_spaceship(&sship);
    draw_projectiles(sship.projectiles.projectiles_arr, sship.projectiles.size_projectile_arr,
                     sship.projectiles.i_first_projectile);

    // DrawText(TextFormat("Angolo:%f", sship.angle), 10, 60, 20, DARKGRAY);
    //  DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    // DrawText(TextFormat("Vettore:%f,%f", sship.pos.x, sship.pos.y), 10, 80, 20, DARKGRAY);
     DrawText(TextFormat("Number of asteroids:%d", n_asteroids_alive), 10, 100, 20, DARKGRAY);
    char* level_string = TextFormat("Level %d", current_level);
    const int level_font = 60;
    DrawText(level_string, SCREEN_WIDTH / 2 - MeasureText(level_string, level_font) / 2, 20, level_font,
             GREEN);

    // DrawFPS(10, 10);
    draw_asteroids(asteroids, MAX_ASTEROIDS);
    EndDrawing();
    //----------------------------------------------------------------------------------
}