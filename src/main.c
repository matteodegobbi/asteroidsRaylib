#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "asteroid.h"
#include "constants.h"
#include "particle.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"
#include <assert.h>
spaceship_t sship;
// asteroid_t asteroids[MAX_ASTEROIDS];//TODO forse fai con realloc
asteroid_t* asteroids;
size_t n_asteroids_alive;
unsigned int current_level;
particle_t asteroid_particles[N_PARTICLES_ASTEROID];
bool developer_mode = false;

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
    
    asteroids = calloc(MAX_ASTEROIDS, sizeof(asteroid_t));
    if (asteroids == NULL) {
        return -1;
    }

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
    double time_waited_invincible = 0;
    SetTargetFPS(144);  // Set our game to run at 60 frames-per-second
    // TODO LA  NAVICELLA SPARA PIU VELOCEMNTE CON FPS PIU ALTI
    //  Main game loop
    while (!WindowShouldClose()) {  // Detect window close button or ESC key
        double delta_time = GetFrameTime();
        if (sship.invincible && (time_waited_invincible += delta_time) >= SECONDS_INVINCIBILITY) {
            sship.invincible = false;
            time_waited_invincible = 0;
        }

        UpdateDrawFrame(delta_time);
        if (n_asteroids_alive == 0) {
            current_level++;
            asteroid_t* temp = realloc(asteroids, MAX_ASTEROIDS * current_level * sizeof(asteroid_t));
            if (temp == NULL) {
                return -1;
            }
            asteroids = temp;
            for (size_t i = 0; i < MAX_ASTEROIDS * current_level; i++) {
                if (i % N_BLOCK_OF_ASTEROID_FAMILY == 0) {
                    init_rand_asteroid(&asteroids[i]);
                } else {
                    asteroids[i].flag = ASTFLAG_UNINITIALIZED;
                }
            }
            n_asteroids_alive = INITIAL_ASTEROIDS * current_level;
            sship.invincible = true;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free(asteroids);
    return 0;
}
// Update and draw game frame
static void UpdateDrawFrame(float delta_time) {
    // Update
    
    if(IsKeyPressed(KEY_TAB)){
        developer_mode = !developer_mode;
    }
    queue_proj_t* proj = &sship.projectiles;

    update_spaceship(&sship, delta_time,asteroids);
    bool collision_happened = collision_projectiles_asteroids(
        asteroids, MAX_ASTEROIDS * current_level, sship.projectiles.projectiles_arr,
        sship.projectiles.size_projectile_arr, sship.projectiles.i_first_projectile, &n_asteroids_alive,
        asteroid_particles, N_PARTICLES_ASTEROID);

    bool spaceship_hit = collision_spaceship_asteroids(asteroids, MAX_ASTEROIDS*current_level, &sship);
    //assert(!spaceship_hit);
    update_projectiles(proj, delta_time);
    update_asteroids(asteroids, MAX_ASTEROIDS * current_level, delta_time);
    

    

    update_particles(asteroid_particles, N_PARTICLES_ASTEROID, delta_time);
    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(spaceship_hit?RED:RAYWHITE);

    //DrawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, spaceship_hit? RED:RAYWHITE);
    draw_spaceship(&sship);
    draw_projectiles(sship.projectiles.projectiles_arr, sship.projectiles.size_projectile_arr,
                     sship.projectiles.i_first_projectile);

    // DrawText(TextFormat("Angolo:%f", sship.angle), 10, 60, 20, DARKGRAY);
    //  DrawText(TextFormat("Vettore:%f,%f", sship.vel.x, sship.vel.y), 10, 80, 20, DARKGRAY);
    // DrawText(TextFormat("Vettore:%f,%f", sship.pos.x, sship.pos.y), 10, 80, 20, DARKGRAY);
    DrawText(TextFormat("Number of asteroids:%d", n_asteroids_alive), 10, 100, 20, RED);
    char* level_string = TextFormat("Level %d", current_level);
    const int level_font = 60;
    DrawText(level_string, SCREEN_WIDTH / 2 - MeasureText(level_string, level_font) / 2, 20, level_font,
             GREEN);

    if(developer_mode){
        DrawText("Developer-Mode", SCREEN_WIDTH / 2 - MeasureText("Developer-Mode", level_font) / 2, 60, level_font,RED);
        DrawFPS(10, 10);
    }
    draw_asteroids(asteroids, MAX_ASTEROIDS * current_level);
    
    draw_particles(asteroid_particles, N_PARTICLES_ASTEROID, GRAY);
    
    EndDrawing();
    //----------------------------------------------------------------------------------
}
