#include "raylib.h"

typedef struct spaceship_t {
    Vector2 pos;/*Center of spaceship*/
    Vector2 vel;
    Texture icon;
    int angle;
    float width;
    float height;
    
} spaceship_t;
void update_spaceship(spaceship_t* sship);
void draw_spaceship(spaceship_t* sship);