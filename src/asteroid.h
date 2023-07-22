#pragma once

#include "asteroid.h"
#include "constants.h"
#include "raylib.h"
#include "raymath.h"



typedef enum { SMALL = 2, MEDIUM = 5, BIG = 6 } asteroid_scale;

typedef struct asteroid_t {
    Vector2 pos;
    Vector2 vel;
    int shape_type;
    asteroid_scale scale;
    Color color;
    float angle;
} asteroid_t;

float int2scale(int i);
void init_rand_asteroid(asteroid_t* ast);
void update_asteroid(asteroid_t* ast);
void draw_asteroid(asteroid_t* ast);
