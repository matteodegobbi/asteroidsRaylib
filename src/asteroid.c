#include "spaceship.h"
#include "asteroid.h"
#include "particle.h"

#include <assert.h>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"



//IF YOU CHANGE THIS RECOMPUTES BARICENTERS, no comptime in C :(
const Vector2 asteroid_shapes[3][ASTEROID_N_SIDES] = {
    {{-10, -10}, {0, -16}, {+10, -12}, {+6, 0}, {+8, +9}, {+1, +5}, {-9, +9}, {-15, 0}},
    {{-5, -3}, {0, -10}, {+6, -5}, {+6, 0}, {+8, 5}, {+1, +5}, {-3, +2}, {-10, 0}},
    {{-10, -6}, {0, -20}, {+12, -10}, {+12, 0}, {+16, 10}, {+2, +10}, {-6, +4}, {-20, 0}}};

const Vector2 asteroid_baricenters[3] = {
    {-1.125,-1.875},
    {0.375,-0.75},
    {0.75,-1.5}
};


asteroid_scale int2scale(int i) {
    switch (i) {
        case 0:
            return SMALL;
        case 1:
            return MEDIUM;
        case 2:
            return BIG;
        default:
            return INVALID_SCALE;
    }
}
int scale2int(asteroid_scale scale) {
    switch (scale) {
        case SMALL:
            return 0;
        case MEDIUM:
            return 1;
        case BIG:
            return 2;
        default:
            return INVALID_SCALE;
    }
}
void init_rand_asteroid(asteroid_t* ast) {
    ast->color = GRAY;
    ast->pos = (Vector2){GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)};
    ast->scale = int2scale(GetRandomValue(0, N_SCALES_ASTEROID - 1));
    // ast->shape_type=1;
    ast->shape_type = GetRandomValue(0, sizeof(asteroid_shapes) / sizeof(asteroid_shapes[0]) - 1);
    ast->vel =
        (Vector2){GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED),
                  GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED)};  // TODO DA CAMBIARE CON VELOCITA PIU SENSATE
    ast->angle = GetRandomValue(0, 360);
    ast->flag = ASTFLAG_ALIVE;
}
void init_rand_asteroid_scale_pos(asteroid_t* ast, asteroid_scale scale, Vector2 pos) {
    ast->color = GRAY;
    ast->pos = pos;
    ast->scale = scale;
    // ast->shape_type=1;
    ast->shape_type = GetRandomValue(0, sizeof(asteroid_shapes) / sizeof(asteroid_shapes[0]) - 1);
    ast->vel =
        (Vector2){GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED),
                  GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED)};  // TODO DA CAMBIARE CON VELOCITA PIU SENSATE
    ast->angle = GetRandomValue(0, 360);
    ast->flag = ASTFLAG_ALIVE;
}

void update_asteroid(asteroid_t* ast, float delta_time) {
    //return;
    if (ast->flag != ASTFLAG_ALIVE) {
        return;
    }
    float diameter = 5.0f;  // TODO CAMBIA GENERICO CON COSTANTS.H
    ast->pos.x += delta_time * ast->vel.x / ast->scale;
    ast->pos.y += delta_time * ast->vel.y / ast->scale;

    //---------------------------------------------------------------------------------------------
    // makes asteroid reenter from the opposite side of where it exited
    ast->pos.y = fmod(ast->pos.y + diameter / 2, SCREEN_HEIGHT + diameter) - diameter / 2;  // reenter from up
    ast->pos.x =
        fmod(ast->pos.x + diameter / 2, SCREEN_WIDTH + diameter) - diameter / 2;  // reenter from left
    if (ast->pos.y < -diameter / 2) {                                             // reenter from down
        ast->pos.y = SCREEN_HEIGHT + diameter / 2;
    }
    if (ast->pos.x < -diameter / 2) {  // reenter from right
        ast->pos.x = SCREEN_WIDTH + diameter / 2;
    }

    ast->angle = fmod(ast->angle += delta_time * ASTEROID_ROTATION_SPEED / ast->scale,
                      360);  // rotate asteroid slowly and keep angles from 0 to 359
    //---------------------------------------------------------------------------------------------
}

float ccw(Vector2 a,Vector2 b, Vector2 c){
    return (c.y-a.y) * (b.x-a.x) > (b.y-a.y) * (c.x-a.x);
}
bool Vector2Intersect(Vector2 a,Vector2 b,Vector2 c, Vector2 d){
    return ccw(a,c,d) != ccw(b,c,d) && ccw(a,b,c) != ccw(a,b,d);
}
bool collision_spaceship_asteroids(asteroid_t asts[], size_t len_ast,spaceship_t* sship){
    Vector2 c= Vector2Add(sship->pos, Vector2Rotate((Vector2){.x=0,.y=SPACESHIP_HITBOX_OFFSET},DEG2RAD*sship->angle));
    Vector2 d= Vector2Add(sship->pos, Vector2Rotate((Vector2){.x=0,.y=-SPACESHIP_HITBOX_OFFSET},DEG2RAD*sship->angle));
    //Vector2 d= Vector2Add(sship->pos, (Vector2){.x=0,.y=-SPACESHIP_HITBOX_OFFSET});
    for (size_t i = 0; i < len_ast; i++) { 
        if (asts[i].flag != ASTFLAG_ALIVE) {
            continue;
        }


        float scale = asts[i].scale;
        float center_x = asts[i].pos.x;
        float center_y = asts[i].pos.y;
        int shape = asts[i].shape_type;
        float angle = asts[i].angle;
        Vector2 currentVec = Vector2Scale(Vector2Rotate(asteroid_shapes[shape][0], angle),scale);
        for (size_t i = 0; i < ASTEROID_N_SIDES; i++) {
            Vector2 nextVec = Vector2Scale(Vector2Rotate(asteroid_shapes[shape][(i + 1) % ASTEROID_N_SIDES], angle),scale);
            Vector2 currentVecPrime = (Vector2){.x=currentVec.x + center_x, .y=currentVec.y + center_y}; 
            Vector2 nextVecPrime= (Vector2){.x=nextVec.x + center_x, .y=nextVec.y + center_y};
            if (Vector2Intersect(currentVecPrime, nextVecPrime, c, d)) {
//                printf("TRUE SCONTRTO\n");
                return true; 
            } 
            //DrawLine(currentVecPrime.x,currentVecPrime.y, nextVecPrime.x,nextVecPrime.y, RED);
//            DrawLine(currentVec.x + center_x, currentVec.y + center_y,nextVec.x + center_x, nextVec.y + center_y, RED);
            currentVec = nextVec;
        }
    }
    return false;
}
bool collision_projectiles_asteroids(asteroid_t asts[], size_t len_ast, projectile_t projs[], size_t n_proj,
                                     size_t i_first_proj, size_t* n_asteroids_alive_pt,particle_t particles[],size_t particles_len) {
    bool collision_happened = false;
    for (size_t i = 0; i < len_ast; i++) {  //&& IsKeyPressed(KEY_CAPS_LOCK)
        if (asts[i].flag != ASTFLAG_ALIVE) {
            continue;
        }

        Vector2 ast_vertices[ASTEROID_N_SIDES + 1];
        for (size_t k = 0; k < ASTEROID_N_SIDES; k++) {  // COMPUTE ASTEROID REAL SHAPE AND ROTATION
            ast_vertices[k] =
                Vector2Add(Vector2Scale(Vector2Rotate(asteroid_shapes[asts[i].shape_type][k], asts[i].angle),
                                        asts[i].scale),
                           asts[i].pos);
        }
        ast_vertices[ASTEROID_N_SIDES] = ast_vertices[0];  // To use CheckCollisionPointPoly properly

        for (size_t j = 0; j < n_proj; j++) {  // CURRENT ASTEROID AGAINST EVERY PROJECTILE
            // controllo di non stare usando un proiettili dequeued TODO togli sta roba di assert
            // assert(projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].flag == 0);

            //  &&(projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].flag == FLAG_SHOOTING) &&
            //  asts[i].flag == ASTFLAG_ALIVE &&
            if ((projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].flag == FLAG_SHOOTING) &&
                CheckCollisionPointPoly(projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].pos,
                                        ast_vertices, ASTEROID_N_SIDES + 1)) {
                // asts[i].color = RED;
                collision_happened = true;
                asts[i].flag = ASTFLAG_DESTROYED;
                projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].flag = FLAG_HIT;
                // asts[i].scale = 0;
                //  projs[(j+i_first_proj)%n_proj].vel=(Vector2){0,0};
                projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].color = WHITE;
                *n_asteroids_alive_pt = *n_asteroids_alive_pt - 1;
                generate_particles(particles,particles_len,asts[i].pos,asts[i].scale);
                if (asts[i].scale != SMALL) {
                    int index_current_scale = scale2int(asts[i].scale);
                    asteroid_scale children_scale = int2scale(index_current_scale - 1);
                    Vector2 current_pos = asts[i].pos;
                    *n_asteroids_alive_pt = *n_asteroids_alive_pt + N_CHILDREN_ASTEROID;
                    init_rand_asteroid_scale_pos(
                        &asts[i], children_scale,
                        Vector2Add(current_pos,
                                   (Vector2){GetRandomValue(-100, 100), GetRandomValue(-100, 100)}));
                    /*init_rand_asteroid_scale_pos(
                        &asts[i + index_current_scale], children_scale,
                        Vector2Add(current_pos,
                                   (Vector2){GetRandomValue(-100, 100), GetRandomValue(-100, 100)}));*/
                    init_rand_asteroid_scale_pos(
                        &asts[i + X_POW_OF_2(index_current_scale - 1)], children_scale,
                        Vector2Add(current_pos,
                                   (Vector2){GetRandomValue(-100, 100), GetRandomValue(-100, 100)}));
                }
                

                break;
            }
        }
    }
    return collision_happened;
}

void draw_asteroid(asteroid_t* ast) {
    if (ast->flag != ASTFLAG_ALIVE) {
        return;
    }
    float scale = ast->scale;
    float center_x = ast->pos.x;
    float center_y = ast->pos.y;
    int shape = ast->shape_type;
    float angle = ast->angle;
    DrawCircle(center_x, center_y, 5, RED);
    Vector2 current_baricenter = Vector2Add(ast->pos, asteroid_baricenters[shape]);
    //DrawCircle(current_baricenter.x,current_baricenter.y, ASTEROID_HITBOX_BASE_RADIUS*scale, GREEN);
    Vector2 currentVec = Vector2Rotate(asteroid_shapes[shape][0], angle);
    for (size_t i = 0; i < ASTEROID_N_SIDES; i++) {
        Vector2 nextVec = Vector2Rotate(asteroid_shapes[shape][(i + 1) % ASTEROID_N_SIDES], angle);
        // DrawCircle(scale *currentVec.x + center_x, scale * currentVec.y + center_y, 5, BLACK);
        DrawLine(scale * currentVec.x + center_x, scale * currentVec.y + center_y,
                 scale * nextVec.x + center_x, scale * nextVec.y + center_y, ast->color);
        currentVec = nextVec;
        /*Vector2 vertice = Vector2Add(
            Vector2Scale(Vector2Rotate(asteroid_shapes[ast->shape_type][i], ast->angle), ast->scale),
            ast->pos);
        DrawCircle(vertice.x, vertice.y, 5, GREEN);*/
    }
}
void update_asteroids(asteroid_t asteroids[], size_t len, float delta_time) {
    for (size_t i = 0; i < len; i++) {
        update_asteroid(&asteroids[i], delta_time);
    }
}
void draw_asteroids(asteroid_t asteroids[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        draw_asteroid(&asteroids[i]);
    }
}


/* ADD TO draw_asteroid to draw scuffed hitboxes
    int step_rectangle = ASTEROID_N_SIDES/4;
    Vector2 vertices[4] = {0};
    for (size_t index = 0,i = 0; index < ASTEROID_N_SIDES; index+=step_rectangle,i++) {
        Vector2 temp = Vector2Add(Vector2Rotate(Vector2Scale(asteroid_shapes[shape][index],scale),angle),ast->pos); 
        vertices[i]= temp;
    }
    for (size_t i = 0; i < 4; i++) {
        printf("%lu\n",i);
        printf("%f\n",vertices[i].x);
        printf("%f\n",vertices[i].y);
        DrawLineV(vertices[i], vertices[(i+1)%4], RED);
    }











*/
