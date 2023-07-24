#include "asteroid.h"

#include <assert.h>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

const Vector2 asteroid_shapes[3][ASTEROID_N_SIDES] = {
    {{-10, -10}, {0, -16}, {+10, -12}, {+6, 0}, {+8, +9}, {+1, +5}, {-9, +9}, {-15, 0}},
    {{-5, -3}, {0, -10}, {+6, -5}, {+6, 0}, {+8, 5}, {+1, +5}, {-3, +2}, {-10, 0}},
    {{-10, -6}, {0, -20}, {+12, -10}, {+12, 0}, {+16, 10}, {+2, +10}, {-6, +4}, {-20, 0}}};

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
    ast->scale = int2scale(GetRandomValue(0, N_SCALES_ASTEROID));
    ast->shape_type = GetRandomValue(0, sizeof(asteroid_shapes) / sizeof(asteroid_shapes[0]) - 1);
    ast->vel =
        (Vector2){GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED),
                  GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED)};  // TODO DA CAMBIARE CON VELOCITA PIU SENSATE
    ast->angle = GetRandomValue(0, 360);
    ast->hit = false;
}
void init_rand_asteroid_scale_pos(asteroid_t* ast, asteroid_scale scale, Vector2 pos) {
    ast->color = GRAY;
    ast->pos = pos;
    ast->scale = scale;
    ast->shape_type = GetRandomValue(0, sizeof(asteroid_shapes) / sizeof(asteroid_shapes[0]) - 1);
    ast->vel =
        (Vector2){GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED),
                  GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED)};  // TODO DA CAMBIARE CON VELOCITA PIU SENSATE
    ast->angle = GetRandomValue(0, 360);
    ast->hit = false;
}

void update_asteroid(asteroid_t* ast, float delta_time) {
    if (ast->hit) {
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

void collision_projectiles_asteroids(asteroid_t asts[], size_t len_ast, projectile_t projs[], size_t n_proj,
                                     size_t i_first_proj) {
    for (size_t i = 0; i < len_ast; i++) {
        if (asts[i].hit) {
            continue;
        }

        Vector2 ast_vertices[ASTEROID_N_SIDES + 1];
        for (size_t k = 0; k < ASTEROID_N_SIDES; k++) {  // COMPUTE ASTEROID REAL SHAPE AND ROTATION
            ast_vertices[k] =
                Vector2Add(Vector2Scale(Vector2Rotate(asteroid_shapes[asts[i].shape_type][k], asts[i].angle),
                                        asts[i].scale),
                           asts[i].pos);
        }
        ast_vertices[ASTEROID_N_SIDES] = ast_vertices[0];
        for (size_t j = 0; j < n_proj; j++) {  // CURRENT ASTEROID AGAINST EVERY PROJECTILE
            // controllo di non stare usando un proiettili dequeued TODO togli sta roba di assert
            // assert(projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].flag == 0);
            if (CheckCollisionPointPoly(projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].pos,
                                        ast_vertices, ASTEROID_N_SIDES + 1)) {
                // asts[i].color = RED;
                asts[i].hit = true;
                // asts[i].scale = 0;
                //  projs[(j+i_first_proj)%n_proj].vel=(Vector2){0,0};
                //  projs[(j + i_first_proj) % MAX_SPACESHIP_PROJECTILES].color = BLACK;
                int index_current_scale = scale2int(asts[i].scale);
                asteroid_scale children_scale = int2scale(index_current_scale-1);
                if (asts[i].scale!=SMALL) {
                    init_rand_asteroid_scale_pos(&asts[i], children_scale, (Vector2){100.0f,100.0f});
                    /*init_rand_asteroid_scale_pos(&asts[i + X_POW_OF_2(index_current_scale - 1)],
                                                 children_scale,
                                                 asts[i + X_POW_OF_2(index_current_scale - 1)].pos);
                }

                break;
            }
        }
    }
}

void draw_asteroid(asteroid_t* ast) {
    if (ast->hit) {
        return;
    }
    float scale = ast->scale;
    float center_x = ast->pos.x;
    float center_y = ast->pos.y;
    int shape = ast->shape_type;
    float angle = ast->angle;
    // DrawCircle(center_x, center_y, 5, RED);
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