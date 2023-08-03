#include "particle.h"

#include <stdlib.h>
void generate_particles(particle_t particles[], size_t particles_len, Vector2 starting_pos,
                        float radius_multiplier) {
    for (size_t i = 0; i < particles_len; i++) {
        particles[i].pos = starting_pos;
        Vector2 particle_vel;
        particle_vel.x = (float)rand() / (float)(RAND_MAX / (2 * PARTICLE_MAX_DIRECTIONAL_SPEED)) +
                         -PARTICLE_MAX_DIRECTIONAL_SPEED;
        float second_max_speed = sqrtf(PARTICLE_MAX_SPEED * PARTICLE_MAX_SPEED - pow(particle_vel.x, 2));
        particle_vel.y = (float)rand() / (float)(RAND_MAX / (2 * second_max_speed)) + -second_max_speed;

        if (GetRandomValue(0, 1)) {
            particles[i].vel = particle_vel;
        } else {
            particles[i].vel.x = particle_vel.y;
            particles[i].vel.y = particle_vel.x;
        }

        /*particles[i].vel.x=((float)rand() / (float)(RAND_MAX / (2 * PARTICLE_MAX_SPEED)) +
                         -PARTICLE_MAX_SPEED)/SQRT_OF_2;

        particles[i].vel.y=((float)rand() / (float)(RAND_MAX / (2 * PARTICLE_MAX_SPEED)) +
                         -PARTICLE_MAX_SPEED)/SQRT_OF_2;*/
        float r = (float)rand() /
                      (float)(RAND_MAX / (EXPLOSION_MAX_RADIUS_PERCENT - EXPLOSION_MIN_RADIUS_PERCENT)) +
                  EXPLOSION_MIN_RADIUS_PERCENT;
        particles[i].distance_to_live = PARTICLE_DIST_TO_LIVE * r * radius_multiplier;
    }
}
void update_particles(particle_t particles[], size_t particles_len, float delta_time) {
    for (size_t i = 0; i < particles_len; i++) {
        float norm = Vector2Length(particles[i].vel);
        particles[i].distance_to_live -= norm;
        particles[i].pos.x += particles[i].vel.x * delta_time;
        particles[i].pos.y += particles[i].vel.y * delta_time;
    }
}
void draw_particles(particle_t particles[], size_t particles_len, Color c) {
    for (size_t i = 0; i < particles_len; i++) {
        if (particles[i].distance_to_live > 0) {
            float r = (float)rand() / (float)(RAND_MAX / (PARTICLE_RADIUS_MAX - PARTICLE_RADIUS_MIN)) +
                      PARTICLE_RADIUS_MIN;
            DrawCircleV(particles[i].pos, r, c);
        }
    }
}