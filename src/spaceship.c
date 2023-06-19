#include "spaceship.h"

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

void update_spaceship(spaceship_t* sship) {
    if (IsKeyDown(KEY_A)) {
        sship->vel = Vector2Rotate(sship->vel, -DEG2RAD * SPACESHIP_ANGULAR_SPEED);
        sship->angle -= SPACESHIP_ANGULAR_SPEED;
    }

    if (IsKeyDown(KEY_D)) {
        sship->vel = Vector2Rotate(sship->vel, DEG2RAD * SPACESHIP_ANGULAR_SPEED);
        sship->angle += SPACESHIP_ANGULAR_SPEED;
    }

    if (IsKeyDown(KEY_W)) {
        sship->pos = Vector2Add(sship->pos, sship->vel);
    }

    if (IsKeyDown(KEY_S)) {
        sship->pos = Vector2Subtract(sship->pos, sship->vel);
    }

    if (IsKeyPressed(KEY_SPACE)) {/*shoot*/
        /*add laser to array of entities to draw */
    }

    //---------------------------------------------------------------------------------------------
    // makes spaceship reenter from the opposite side of where it exited
    sship->pos.y = fmod(sship->pos.y + sship->height / 2, SCREEN_HEIGHT + sship->height) -
                   sship->height / 2;  // reenter from up
    sship->pos.x = fmod(sship->pos.x + sship->height / 2, SCREEN_WIDTH + sship->height) -
                   sship->height / 2;         // reenter from left
    if (sship->pos.y < -sship->height / 2) {  // reenter from down
        sship->pos.y = SCREEN_HEIGHT + sship->height / 2;
    }
    if (sship->pos.x < -sship->height / 2) {  // reenter from right
        sship->pos.x = SCREEN_WIDTH + sship->height / 2;
    }

    sship->angle = sship->angle % 360;  // keep angles from 0 to 359
    //---------------------------------------------------------------------------------------------
}
void draw_spaceship(spaceship_t* sship) {
    Vector2 drawCenter = (Vector2){sship->width / 2, sship->height / 2};
    Rectangle source = (Rectangle){0, 0, sship->icon.width, sship->icon.height};
    Rectangle destination = (Rectangle){sship->pos.x, sship->pos.y, sship->width, sship->height};
    DrawTexturePro(sship->icon, source, destination, drawCenter, sship->angle, WHITE);
}
