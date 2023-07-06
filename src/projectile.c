

#include <assert.h>

#include "spaceship.h"
void update_projectiles(const projectile_t arr[], size_t size, size_t first) {
    for (size_t i = first; i < first + size; i++) {
    }
}

void draw_projectiles(const projectile_t arr[], size_t size, size_t first) {
    for (size_t i = first; i < first + size; i++) {
        DrawCircle(arr[i % MAX_SPACESHIP_PROJECTILES].pos.x, arr[i % MAX_SPACESHIP_PROJECTILES].pos.y, 10.0f,
                   GREEN);
    }
}

void enqueue_projectile(queue_proj_t* queue, Vector2 initial_pos) {
    // check if queue is full
    if (queue->size_projectile_arr == MAX_SPACESHIP_PROJECTILES) {
        return;
    }
    size_t index_new_proj =
        (queue->i_first_projectile + queue->size_projectile_arr) % MAX_SPACESHIP_PROJECTILES;
    queue->projectiles_arr[index_new_proj].pos = initial_pos;
    queue->projectiles_arr[index_new_proj].dist_left_alive = INITIAL_DIST_TO_LIVE;
    queue->size_projectile_arr++;
}

void dequeue_projectile(queue_proj_t* queue) {
    // check if queue is empty
    if (queue->size_projectile_arr == 0) {
        return;
    }
    queue->i_first_projectile = (queue->i_first_projectile + 1) % MAX_SPACESHIP_PROJECTILES;
    queue->size_projectile_arr--;
}