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
    GameObject gameObject;
    Vector2 previousPos;
    Vector2 velocity;
    float mass;
    bool inAir;
    bool physicsStepCompleted;
} PhysicsObject;

typedef struct StaticObject {
    GameObject gameObject;
    bool canCollide;
} StaticObject;

typedef struct ObjectGroup {
    struct {uint32_t key; StaticObject* value;} *staticObjects;
    struct {uint32_t key; PhysicsObject* value;} *physicsObjects;
} ObjectGroup_t;


/*
    Draws game object
*/
void GameObjectDraw(GameObject* gameObject);

/*
    Draws the outline of a game object
*/
void GameObjectDrawOutline(GameObject* gameObject);

/*
    Creates a new GameObject instance with unique id
*/
GameObject GameObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation);

/*
    Creates new physics object and returns pointer to it
*/
PhysicsObject* PhysicsObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation);

/*
    Creates new static object and returns pointer to it
*/
StaticObject* StaticObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation, bool canCollide);

/*
    Creates new object group
*/
ObjectGroup_t* ObjectGroupCreate();

/*
    Frees the object group
*/
void ObjectGroupFree(ObjectGroup_t* objectGroup);

/*
    Draws the object group
*/
void ObjectGroupDraw(ObjectGroup_t* objectGroup);

/*
    Adds new physics object to the group
*/
void ObjectGroupSetPhysicsObject(ObjectGroup_t* objectGroup, PhysicsObject* physicsObject);

/*
    Adds new static object to the group
*/
void ObjectGroupSetStaticObject(ObjectGroup_t* objectGroup, StaticObject* staticObject);

/*
    Removes element with given objectId
*/
bool ObjectGroupRemove(ObjectGroup_t* objectGroup, uint32_t objectId);


#ifndef ObjectGroupSet
    #define ObjectGroupSet(obj_g, obj) _Generic((obj),\
        PhysicsObject* : ObjectGroupSetPhysicsObject,\
        StaticObject*  : ObjectGroupSetStaticObject\
    )(obj_g, obj)
#endif

/*
    Returns the friction of a game object
*/
static inline float GameObjectGetFriction(SpriteId spriteId) {
    
    switch(spriteId) {
        case SI_TILE_GRASS: return 200.0f;
        case SI_TILE_DIRT: return 250.0f;
    }
    return 0.0f;
}