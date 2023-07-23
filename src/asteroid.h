#pragma once

#include "asteroid.h"
#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "raymath.h"

typedef enum { SMALL = 3, MEDIUM = 5, BIG = 6 } asteroid_scale;

typedef struct asteroid_t {
    Vector2 pos;
    Vector2 vel;
    int shape_type;
    asteroid_scale scale;
    Color color;
    float angle;
    bool hit;
} asteroid_t;

asteroid_scale int2scale(int i);
void init_rand_asteroid(asteroid_t* ast);
void update_asteroid(asteroid_t* ast,float delta_time);
void collision_projectiles_asteroids(asteroid_t asteroids[], size_t n_ast, projectile_t projectiles[],
                                     size_t n_proj, size_t i_first_proj);
void draw_asteroid(asteroid_t* ast);
