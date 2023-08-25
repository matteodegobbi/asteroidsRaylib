#pragma once

#include <stdio.h>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"
typedef struct particle_t {
    Vector2 pos;
    Vector2 vel;
    float distance_to_live;
} particle_t;

void generate_particles(particle_t particles[], size_t particles_len, Vector2 starting_pos,float radius_multiplier);
void update_particles(particle_t particles[], size_t particles_len, float delta_time);
void draw_particles(particle_t particles[], size_t particles_len, Color c);