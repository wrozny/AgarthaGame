#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "raylib.h"
#include "assets.h"

typedef struct GameObject {
    SpriteId spriteId;
    Vector2 pos;
    Vector2 size;
    float rotation;
    uint32_t objectId;
} GameObject;

typedef struct PhysicsObject {
    GameObject *gameObject;
    Vector2 previousPos;
    Vector2 velocity;
    bool inAir;
} PhysicsObject;

typedef struct StaticObject {
    GameObject *gameObject;
    bool canCollide;
} StaticObject;


/*
    Draws game object
*/
void GameObjectDraw(GameObject* gameObject);

/*
    Allocates memory for a game object and returns pointer to it
*/
GameObject* GameObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation);

/*
    Creates new physics object and returns pointer to it
*/
PhysicsObject* PhysicsObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation);

/*
    Frees the allocated physics object
*/
void PhysicsObjectDestroy(PhysicsObject *physicsObject);

/*
    Creates new static object and returns pointer to it
*/
StaticObject* StaticObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation, bool canCollide);

/*
    Frees the allocated static object
*/
void StaticObjectDestroy(StaticObject *staticObject);

/*
    Applies the velocity to the physics objects position
*/
void PhysicsObjectApplyVelocity(PhysicsObject *physicsObject, double deltaTime);
