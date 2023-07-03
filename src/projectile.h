#pragma once

#include <stddef.h>

#include "raylib.h"

#define INITIAL_DIST_TO_LIVE 1000

typedef struct projectile_t {
    Vector2 pos;
    Vector2 vel;
    float dist_left_alive;

} projectile_t;

void update_projectiles(const projectile_t arr[], size_t size,size_t first);

void draw_projectiles(const projectile_t arr[], size_t size, size_t first);
