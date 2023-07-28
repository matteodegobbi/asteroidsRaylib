#pragma once
//---------------------------------
//------------General--------------
//---------------------------------
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1000
#define X_POW_OF_2(x) (1 << (x))
//---------------------------------
//-----------Spaceship-------------
//---------------------------------
#define MAX_SPACESHIP_PROJECTILES 500
#define SPACESHIP_ANGULAR_SPEED 210.0f
#define SPACESHIP_DIREC_SPEED -500
//---------------------------------
//-----------Projectile------------
//---------------------------------
#define PROJECTILE_Y_SPEED -1100
#define PROJECTILE_X_SPEED 0
#define PROJECTILE_SIZE 5.0f
#define FLAG_SHOOTING 0
#define FLAG_DEQUEUED -70
#define FLAG_HIT 1
#define FLAG_UNINITIALIZED -1
//---------------------------------
//------------Asteroids------------
//---------------------------------
#define N_SCALES_ASTEROID 3  // NEEDS TO BE CHANGED IF THE NEXT DEFINE IS CHANGED
typedef enum {
    SMALL = 2,
    MEDIUM = 5,
    BIG = 8
} asteroid_scale;  // IF YOU CHANGE THIS CHANGE PREVIOUS DEFINE and scale2int/int2scale
#define INVALID_SCALE -1

#define INITIAL_ASTEROIDS 2
#define ASTEROID_N_SIDES 8
#define MAX_ASTEROID_DIREC_SPEED 300
#define ASTEROID_ROTATION_SPEED 10.0f
#define N_CHILDREN_ASTEROID 2  // DONT CHANGE THIS
#define N_TYPES_ASTEROIDS 3

#define ASTFLAG_DESTROYED 1
#define ASTFLAG_ALIVE 0
#define ASTFLAG_UNINITIALIZED -1
// how many consecutive spaces to allocate an asteroid and when it dies
// all its children, children of children etc...
#define N_BLOCK_OF_ASTEROID_FAMILY X_POW_OF_2(N_SCALES_ASTEROID - 1)
#define MAX_ASTEROIDS (N_BLOCK_OF_ASTEROID_FAMILY * INITIAL_ASTEROIDS)
//---------------------------------
//-----------Controller------------
//---------------------------------
#define DEAD_ZONE 0.3f
#define GAMEPAD 0
