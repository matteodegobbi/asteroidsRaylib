


#include "spaceship.h"
void update_projectiles(projectile_t arr[], size_t arr_length) {}

void draw_projectiles(projectile_t arr[], size_t arr_length) {
    for (size_t i = 0; i < arr_length; i++) {
        DrawCircle(arr[i].pos.x,arr[i].pos.y,10.0f,GREEN);
    }
}