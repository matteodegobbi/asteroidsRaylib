
#include "projectile.h"

#include <assert.h>
#include <stdio.h>

#include "spaceship.h"
void update_projectiles(queue_proj_t* queue) {
    size_t first = queue->i_first_projectile;
    size_t size = queue->size_projectile_arr;
    for (size_t i = first; i < first + size; i++) {
        projectile_t current = queue->projectiles_arr[i % MAX_SPACESHIP_PROJECTILES];
        if (current.dist_left_alive <= 0) {
            dequeue_projectile(queue);
        } else {
            queue->projectiles_arr[i % MAX_SPACESHIP_PROJECTILES].pos = Vector2Add(current.pos, current.vel);
            queue->projectiles_arr[i % MAX_SPACESHIP_PROJECTILES].dist_left_alive -=
                Vector2Length(current.vel);
        }
        Vector2* current_pos = &(queue->projectiles_arr[i % MAX_SPACESHIP_PROJECTILES].pos);
        current_pos->y = fmod(current_pos->y + PROJECTILE_SIZE / 2, SCREEN_HEIGHT + PROJECTILE_SIZE) -
                         PROJECTILE_SIZE / 2;  // reenter from up
        current_pos->x = fmod(current_pos->x + PROJECTILE_SIZE / 2, SCREEN_WIDTH + PROJECTILE_SIZE) -
                         PROJECTILE_SIZE / 2;         // reenter from left
        if (current_pos->y < -PROJECTILE_SIZE / 2) {  // reenter from down
            current_pos->y = SCREEN_HEIGHT + PROJECTILE_SIZE / 2;
        }
        if (current_pos->x < -PROJECTILE_SIZE / 2) {  // reenter from right
            current_pos->x = SCREEN_WIDTH + PROJECTILE_SIZE / 2;
        }
    }
}

void draw_projectiles(const projectile_t arr[], size_t size, size_t first) {
    for (size_t i = first; i < first + size; i++) {
        DrawCircle(arr[i % MAX_SPACESHIP_PROJECTILES].pos.x, arr[i % MAX_SPACESHIP_PROJECTILES].pos.y,
                   PROJECTILE_SIZE, arr[i%MAX_SPACESHIP_PROJECTILES].color);
    }
}

void enqueue_projectile(queue_proj_t* queue, Vector2 initial_pos, Vector2 vel) {
    // check if queue is full
    if (queue->size_projectile_arr == MAX_SPACESHIP_PROJECTILES) {
        return;
    }
    size_t index_new_proj =
        (queue->i_first_projectile + queue->size_projectile_arr) % MAX_SPACESHIP_PROJECTILES;
    queue->projectiles_arr[index_new_proj].pos = initial_pos;
    queue->projectiles_arr[index_new_proj].dist_left_alive = INITIAL_DIST_TO_LIVE;
    queue->projectiles_arr[index_new_proj].vel = vel;
    queue->projectiles_arr[index_new_proj].color=GetColor((unsigned int)GetRandomValue(0,0xFFFFFF));//RANDOM COLOR
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