#pragma once

#include "raylib.h"
#include "raymath.h"
#include "stdbool.h"
#include "gobjects.h"

/*
    Resolves the velocity applied to the physics object
*/
void PhysicsResolveObjectTick(PhysicsObject *target, ObjectGroup_t **objectGroups, float deltaTime);