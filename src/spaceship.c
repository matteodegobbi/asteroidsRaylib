#include "spaceship.h"

#include "raylib.h"
void update_spaceship(spaceship_t* sship) {
    if (IsKeyDown(KEY_W)) {
        sship->pos.y-=1;
    }

    if (IsKeyDown(KEY_S)) {
        sship->pos.y+=1;
    }
}
void draw_spaceship(spaceship_t* sship) { DrawTextureEx(sship->icon, sship->pos, 0, 0.20F, WHITE); }
