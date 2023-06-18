#include "raylib.h"
typedef struct spaceship_t {
    Vector2 pos;
    Vector2 vel;
    Texture icon;
} spaceship_t;
void update_spaceship(spaceship_t* sship);
void draw_spaceship(spaceship_t* sship);