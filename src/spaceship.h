#pragma once

#include "raylib.h"
#include "projectile.h"
#include "constants.h"

#include <stddef.h>
typedef struct spaceship_t {
    Vector2 pos; /*Center of spaceship*/
    Vector2 vel;
    Texture icon;
    int angle;
    float width;
    float height;
    projectile_t projectiles_arr[MAX_SPACESHIP_PROJECTILES];//FIFO circular queue
    size_t i_last_projectile;
    size_t size_projectile_arr;
} spaceship_t;
void init_spaceship(spaceship_t* sship);
void update_spaceship(spaceship_t* sship);
void draw_spaceship(spaceship_t* sship);
void shoot_projectile(spaceship_t* sship);