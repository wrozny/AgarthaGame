#pragma once

#include "raylib.h"
#include "raymath.h"

#include "gobjects.h"

#define PLAYER_SPEED 200.0f

extern Camera2D PlayerCamera;
extern PhysicsObject* PlayerPhysicsObject;

/*
    Initializes every variable needed for player
*/
void InitPlayer();

/*
   Returns the direction of input based on readen input
*/
Vector2 InputGetDirection();


