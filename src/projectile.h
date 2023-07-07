#pragma once
#include <stddef.h>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

#define INITIAL_DIST_TO_LIVE 2000

typedef struct projectile_t {
    Vector2 pos;
    Vector2 vel;
    float dist_left_alive;
    Color color;
} projectile_t;

typedef struct queue_proj_t {
    projectile_t projectiles_arr[MAX_SPACESHIP_PROJECTILES];  // FIFO circular queue
    size_t i_first_projectile;
    size_t size_projectile_arr;
} queue_proj_t;

void update_projectiles(queue_proj_t* queue);
void draw_projectiles(const projectile_t arr[], size_t size, size_t first);

void enqueue_projectile(queue_proj_t* queue, Vector2 initial_pos, Vector2 vel);
void dequeue_projectile(queue_proj_t* queue);