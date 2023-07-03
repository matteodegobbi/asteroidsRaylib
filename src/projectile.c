

#include "spaceship.h"
void update_projectiles(const projectile_t arr[], size_t size,size_t first) {
    for (size_t i = first; i < first+size; i++) {
        
    }
}

void draw_projectiles(const projectile_t arr[], size_t size, size_t first ) {
    for (size_t i = first; i < first+size; i++) {
        DrawCircle(arr[i%size].pos.x, arr[i%size].pos.y, 10.0f, GREEN);
    }
}