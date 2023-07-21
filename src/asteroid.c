#include "asteroid.h"

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

const Vector2 asteroid_shapes[2][8] = {
    {{-10, -10}, {0, -13}, {+10, -12}, {+10, 0}, {+8, +9}, {+1, +5}, {-9, +9}, {-15, 0}}, {}};

void init_rand_asteroid(asteroid_t* ast) {
    ast->color=GRAY;
    ast->pos=(Vector2){GetRandomValue(0,SCREEN_WIDTH),GetRandomValue(0,SCREEN_HEIGHT)};
    ast->scale= BIG;
    ast->shape_type=0;//TODO DA CAMBIARE IN UNO CASUALE
    ast->vel=(Vector2){0,0};
}
asteroid_t asteroids[MAX_ASTEROIDS];

void draw_asteroid(asteroid_t* ast) {
    float scale = ast->scale;
    float center_x = ast->pos.x;
    float center_y = ast->pos.y;
    int shape = ast->shape_type;
    for (size_t i = 0; i < 8; i++) {
        DrawCircle(scale * asteroid_shapes[shape][i].x + center_x,
                   scale * asteroid_shapes[shape][i].y + center_y, 5, BLACK);
        DrawLine(scale * asteroid_shapes[shape][i].x + center_x,
                 scale * asteroid_shapes[shape][i].y + center_y,
                 scale * asteroid_shapes[shape][(i + 1) % 8].x + center_x,
                 scale * asteroid_shapes[shape][(i + 1) % 8].y + center_y, GRAY);
    }
    DrawCircle(center_x, center_y, 5, RED);
}