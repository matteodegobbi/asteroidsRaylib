#pragma once
#include "raylib.h"
#include "projectile.h"
#include "constants.h"

#include <stddef.h>
typedef struct spaceship_t {
    Vector2 pos; /*Center of spaceship*/
    Vector2 vel;
    Texture icon;
    float angle;
    float width;
    float height;
    queue_proj_t projectiles;    
    bool invincible;
} spaceship_t;
void init_spaceship(spaceship_t* sship);
void update_spaceship(spaceship_t* sship,float delta_time);
void draw_spaceship(spaceship_t* sship);
void shoot_projectile(spaceship_t* sship);
void unshoot_oldest_projectile(spaceship_t* sship);