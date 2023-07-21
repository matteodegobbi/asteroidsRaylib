#pragma once

#include "constants.h"
#include "asteroid.h"
#include "raylib.h"
#include "raymath.h"

typedef enum {SMALL=2,MEDIUM=5,BIG=10} asteroid_scale;

typedef struct asteroid_t{
    Vector2 pos;
    Vector2 vel;
    int shape_type;
    asteroid_scale scale;
    Color color;
} asteroid_t;

void init_rand_asteroid(asteroid_t* ast);
void draw_asteroid(asteroid_t* ast);
   