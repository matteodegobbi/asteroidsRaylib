#pragma once

#include "spaceship.h"
#include "constants.h"
#include "projectile.h"
#include "particle.h"
#include "raylib.h"
#include "raymath.h"

typedef struct spaceship_t  spaceship_t;
typedef struct asteroid_t {
    Vector2 pos;
    Vector2 vel;
    int shape_type;
    asteroid_scale scale;
    Color color;
    float angle;
    int flag;
} asteroid_t;

asteroid_scale int2scale(int i);
void init_rand_asteroid(asteroid_t* ast);
void init_rand_asteroid_scale_pos(asteroid_t* ast, asteroid_scale scale, Vector2 pos);
void update_asteroid(asteroid_t* ast, float delta_time);
bool collision_projectiles_asteroids(asteroid_t asteroids[], size_t n_ast, projectile_t projectiles[],
                                     size_t n_proj, size_t i_first_proj, size_t* n_asteroids_alive_pt,
                                     particle_t particles[], size_t particles_len);
void draw_asteroid(asteroid_t* ast);

bool collision_spaceship_asteroids(asteroid_t asts[], size_t len_ast,spaceship_t* sship);
void update_asteroids(asteroid_t asteroids[], size_t len, float delta_time);
void draw_asteroids(asteroid_t asteroids[], size_t len);
