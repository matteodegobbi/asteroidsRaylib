#include "raylib.h"
#include "projectile.h"
#include <stddef.h>
typedef struct spaceship_t {
    Vector2 pos; /*Center of spaceship*/
    Vector2 vel;
    Texture icon;
    int angle;
    float width;
    float height;
    projectile_t projectiles[1000];
    size_t iLastProjectile;
} spaceship_t;
void update_spaceship(spaceship_t* sship);
void draw_spaceship(spaceship_t* sship);
void shoot_projectile(spaceship_t* sship);