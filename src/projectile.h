#pragma once

#include "raylib.h"
#include <stddef.h>

#define INITIAL_DIST_TO_LIVE 1000

typedef struct projectile_t {
    Vector2 pos;
    Vector2 vel;
    float dist_left_alive;

} projectile_t;
void draw_projectiles(projectile_t arr[], size_t arr_length);

