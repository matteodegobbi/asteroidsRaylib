#include "spaceship.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "constants.h"
#include "projectile.h"
#include "raylib.h"
#include "raymath.h"

void init_spaceship(spaceship_t* sship) {
    sship->icon = LoadTexture("resources/spaceship.png");
    *sship =
        (spaceship_t){{SCREEN_WIDTH / 1 - sship->icon.width / 2, SCREEN_HEIGHT / 2 - sship->icon.height / 2},
                      {0, SPACESHIP_DIREC_SPEED},
                      sship->icon,
                      0,
                      sship->icon.width / 4,
                      sship->icon.height / 4};
    sship->projectiles.i_first_projectile = 0;
    sship->projectiles.size_projectile_arr = 0;
    sship->invincible = false;
    for (size_t i = 0; i < MAX_SPACESHIP_PROJECTILES; i++) {
        sship->projectiles.projectiles_arr[i].flag = FLAG_UNINITIALIZED;
    }
}
void update_spaceship(spaceship_t* sship, float delta_time) {
    //---------------------------------------------------------------------------------------------
    // KEYBOARD AND MOUSE
    if (IsKeyDown(KEY_A)) {
        double delta_angle = delta_time * SPACESHIP_ANGULAR_SPEED;
        sship->vel = Vector2Rotate(sship->vel, -delta_angle * DEG2RAD);
        sship->angle -= delta_angle;
    }

    if (IsKeyDown(KEY_D)) {
        double delta_angle = delta_time * SPACESHIP_ANGULAR_SPEED;
        sship->vel = Vector2Rotate(sship->vel, delta_angle * DEG2RAD);
        sship->angle += delta_angle;
    }

    if (IsKeyDown(KEY_W)) {
        sship->pos = Vector2Add(sship->pos, Vector2Scale(sship->vel, delta_time));
    }

    if (IsKeyDown(KEY_S)) {
        sship->pos = Vector2Subtract(sship->pos, Vector2Scale(sship->vel, delta_time));
    }

    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonDown(0)) { /*shoot*/
        /*adds laser to array of entities to draw */
        shoot_projectile(sship);
    }

    if (IsKeyDown(KEY_TAB)) { /*deshoot solo per il debug*/
        unshoot_oldest_projectile(sship);
    }
    if (IsKeyPressed(KEY_HOME)) {
        // NOTHING
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------
    // GAMEPAD
    if (IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
        IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) { /*shoot*/
        /*adds laser to array of entities to draw */
        shoot_projectile(sship);
    }

    float axisX = GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X);
    float axisY = GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_Y);
    axisX = (axisX >= 0 ? 1 : -1) * pow(axisX, 2);
    axisY = (axisY >= 0 ? 1 : -1) * pow(axisY, 2);
    Vector2 axis = (Vector2){axisX, axisY};
    float normAxis = Vector2Length(axis);
    if (normAxis >= DEAD_ZONE) {
        sship->angle = (atan2f(axisY, axisX)) * RAD2DEG + 90;
        sship->vel = Vector2Rotate((Vector2){0, SPACESHIP_DIREC_SPEED}, sship->angle * DEG2RAD);
        sship->pos = Vector2Add(sship->pos, Vector2Scale(sship->vel, normAxis * delta_time));
    }

    // DrawCircleV(Vector2Add((Vector2){SCREEN_WIDTH/2,SCREEN_HEIGHT/2},Vector2Scale(axis,100)),20.0f,RED);

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

    sship->angle = fmod(sship->angle, 360.0f);  // keep angles from 0 to 359
    //---------------------------------------------------------------------------------------------
}
void shoot_projectile(spaceship_t* sship) {
    /*TODO ADD MODIFIER FOR FASTER PROJECTILES*/
    // COMMENTED VERSION HAS INERTIA FROM SHIP
    // enqueue_projectile(&(sship->projectiles),sship->pos,sship->vel);
    Vector2 proj_vel =
        Vector2Rotate((Vector2){PROJECTILE_X_SPEED, PROJECTILE_Y_SPEED}, DEG2RAD * sship->angle);
    Vector2 relative_pos = Vector2Scale(Vector2Normalize(sship->vel), sship->height / 2);
    enqueue_projectile(&(sship->projectiles), Vector2Add(sship->pos, relative_pos), proj_vel);
}
void unshoot_oldest_projectile(spaceship_t* sship) { /*DEBUG GOD MODE*/
    dequeue_projectile(&(sship->projectiles));
}
void draw_spaceship(spaceship_t* sship) {
    if (sship->invincible) {
        DrawCircleV(sship->pos, sship->height * 1.2f, SKYBLUE);
    }

    Vector2 drawCenter = (Vector2){sship->width / 2, sship->height / 2};
    Rectangle source = (Rectangle){0, 0, sship->icon.width, sship->icon.height};
    Rectangle destination = (Rectangle){sship->pos.x, sship->pos.y, sship->width, sship->height};
    DrawTexturePro(sship->icon, source, destination, drawCenter, sship->angle, WHITE);
}
