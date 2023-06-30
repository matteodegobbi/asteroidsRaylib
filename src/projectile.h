#include "raylib.h"
#include <stddef.h>
#define INITIAL_DIST_TO_LIVE 1000
#pragma once
typedef struct projectile_t {
    Vector2 pos;
    Vector2 vel;
    float distLeftToLive;

} projectile_t;
void draw_projectiles(projectile_t arr[], size_t arr_length);

