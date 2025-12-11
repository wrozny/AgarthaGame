#pragma once

#include "raylib.h"
#include "raymath.h"
#include "stdbool.h"

#include "gobjects.h"

/*
    Returns true or false whether rects are inside eachother
*/
bool CollisionsRectsCollided(Rectangle rect1, Rectangle rect2);

/*
    Returns true or false whether game objects are inside eachother
*/
bool CollisionsGameObjectsCollided(GameObject a, GameObject b);

/*
    Resolves collisions on physics object when collided with static object
*/
void CollisionsResolvePhysicsAndStaticObjects(PhysicsObject *physicsObject, StaticObject *staticObject);

void CollisionsResolve2PhysicsObjects();