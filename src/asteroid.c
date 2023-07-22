#include "asteroid.h"

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

asteroid_t asteroids[MAX_ASTEROIDS];
size_t n_asteroids = 12;

const Vector2 asteroid_shapes[3][ASTEROID_N_SIDES] = {
    {{-10, -10}, {0, -16}, {+10, -12}, {+6, 0}, {+8, +9}, {+1, +5}, {-9, +9}, {-15, 0}},
    {{-5, -3}, {0, -10}, {+6, -5}, {+6, 0}, {+8, 5}, {+1, +5}, {-3, +2}, {-10, 0}},
    {{-10, -6}, {0, -20}, {+12, -10}, {+12, 0}, {+16, 10}, {+2, +10}, {-6, +4}, {-20, 0}}};

float int2scale(int i) {
    switch (i) {
        case 0:
            return SMALL;
        case 1:
            return MEDIUM;
        default:
            return BIG;
    }
}
void init_rand_asteroid(asteroid_t* ast) {
    ast->color = GRAY;
    ast->pos = (Vector2){GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)};
    ast->scale = int2scale(GetRandomValue(0,2));//TODO NUMERO ELEMENTI NEL ENUM
    ast->shape_type = GetRandomValue(
        0, sizeof(asteroid_shapes) / sizeof(asteroid_shapes[0]) - 1);  // TODO DA CAMBIARE IN UNO CASUALE
    ast->vel =
        (Vector2){GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED),
                  GetRandomValue(0, MAX_ASTEROID_DIREC_SPEED)};  // TODO DA CAMBIARE CON VELOCITA PIU SENSATE
    ast->angle = GetRandomValue(0, 360);
}

void update_asteroid(asteroid_t* ast) {
    float diameter = 5.0f;  // TODO CAMBIA GENERICO CON COSTANTS.H
    ast->pos.x += ast->vel.x / ast->scale;
    ast->pos.y += ast->vel.y / ast->scale;

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

    ast->angle = fmod(ast->angle += ASTEROID_ROTATION_SPEED / ast->scale,
                      360);  // rotate asteroid slowly and keep angles from 0 to 359
    //---------------------------------------------------------------------------------------------
}
void draw_asteroid(asteroid_t* ast) {
    float scale = ast->scale;
    float center_x = ast->pos.x;
    float center_y = ast->pos.y;
    int shape = ast->shape_type;
    float angle = ast->angle;
    Vector2 currentVec = Vector2Rotate(asteroid_shapes[shape][0], angle);
    for (size_t i = 0; i < ASTEROID_N_SIDES; i++) {
        Vector2 nextVec = Vector2Rotate(asteroid_shapes[shape][(i + 1) % ASTEROID_N_SIDES], angle);
        // DrawCircle(scale *currentVec.x + center_x, scale * currentVec.y + center_y, 5, BLACK);
        DrawLine(scale * currentVec.x + center_x, scale * currentVec.y + center_y,
                 scale * nextVec.x + center_x, scale * nextVec.y + center_y, GRAY);
        currentVec = nextVec;
    }
    // DrawCircle(center_x, center_y, 5, RED);
}