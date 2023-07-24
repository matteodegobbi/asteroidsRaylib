#include <math.h>
#include <stdio.h>

#include "asteroid.h"
#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"
spaceship_t sship;
asteroid_t asteroids[MAX_ASTEROIDS];
//size_t n_asteroids;
// #define QUADRATO_DEBUG  // TODO RIMUOVI QUANDO HAI FINITO

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

    //n_asteroids = INITIAL_ASTEROIDS;
    init_spaceship(&sship);
    for (size_t i = 0; i < MAX_ASTEROIDS; i++) {
        if (i % N_BLOCK_OF_ASTEROID_FAMILY) {
            init_rand_asteroid(&asteroids[i]);
        } else {
            asteroids[i].hit = true;
        }
    }

    // DisableCursor();

    SetTargetFPS(144);  // Set our game to run at 60 frames-per-second
    // TODO LA  NAVICELLA SPARA PIU VELOCEMNTE CON FPS PIU ALTI
    //  Main game loop
    while (!WindowShouldClose()) {  // Detect window close button or ESC key
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

    update_spaceship(&sship, delta_time);
    collision_projectiles_asteroids(asteroids, MAX_ASTEROIDS, sship.projectiles.projectiles_arr,
                                    sship.projectiles.size_projectile_arr,
                                    sship.projectiles.i_first_projectile);

    update_projectiles(proj, delta_time);
    update_asteroids(asteroids, MAX_ASTEROIDS, delta_time);
    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_spaceship(&sship);
    draw_projectiles(sship.projectiles.projectiles_arr, sship.projectiles.size_projectile_arr,
                     sship.projectiles.i_first_projectile);

#ifdef QUADRATO_DEBUG
    Color hitquadrato = GREEN;
#define n_lati 7
    const Vector2 vertices_quadrato[n_lati] = {(Vector2){200, 200}, (Vector2){200, 800}, (Vector2){800, 800},
                                               (Vector2){800, 200}, (Vector2){500, 300}, (Vector2){300, 150},
                                               (Vector2){200, 200}};
    if (CheckCollisionPointPoly(sship.pos, vertices_quadrato, n_lati)) {
        hitquadrato = RED;
    }

    for (size_t i = 0; i < n_lati; a++) {
        DrawLineV(vertices_quadrato[i], vertices_quadrato[(i + 1) % n_lati], hitquadrato);
    }

#endif
    // DrawText(TextFormat("Angolo:%f", sship.angle), 10, 60, 20, DARKGRAY);
    // DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    DrawFPS(10, 10);
    draw_asteroids(asteroids, MAX_ASTEROIDS);
    EndDrawing();
    //----------------------------------------------------------------------------------
}