#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "gobjects.h"
#include "physics/physics.h"
#include "hashing.h"

extern ObjectGroup_t **SceneObjectGroupBuffer;

#define CHUNK_PIXEL_SIZE 256


typedef struct Scene {
    ObjectGroup_t *allObjects;
    struct {uint32_t key; ObjectGroup_t *value;} *chunks;
    float gravity;
} Scene;

/*
    Initializes the scene
*/
Scene* SceneCreate();

/*
    Frees all the memory allocated for a scene
*/
void SceneDestroy(Scene* scene);

/*
    Draws all the objects inside the scene
*/
void SceneDraw(Scene* scene);

/*
    Draws the scene with debug data
*/
void SceneDrawDebug(Scene* scene);

/*
    Calculates physics tick for every physics object in the scene
*/
void SceneUpdatePhysics(Scene* scene, double deltaTime);

/*
    Adds new StaticObject to scene
*/
void SceneAddStaticObject(Scene* targetScene, StaticObject* staticObject);

/*
    Adds new object with physics applied to scene
*/
void SceneAddPhysicsObject(Scene* targetScene, PhysicsObject* physicsObject);

/*
    Adds the pointer of physics object to chunk that contains it and removes it from chunks that physics object left
    should be executed everytime physics object changes a chunk
*/
void SceneUpdatePhysicsObjectChunk(Scene* targetScene, PhysicsObject* physicsObject);


/*
    Packs two int16's into one uint32
*/
static inline uint32_t ScenePackInt16(int16_t a, int16_t b) {
    return ((uint32_t)a << 16) | b;
}

/*
    Returns the uint32 id of a chunk based on CHUNK_PIXEL_SIZE
*/
static inline uint32_t SceneGetChunkId(float x, float y) {
    return ScenePackInt16((int16_t)(x / CHUNK_PIXEL_SIZE), (int16_t)(y / CHUNK_PIXEL_SIZE));
}

/*
    Given the target rectangle writes to SceneObjectGroupBuffer every ObjectGroup pointer that target is in 
    useful both in physics simulation and chunk rendering
*/
void SceneUpdateObjectGroupBuffer(Scene *scene, Rectangle target);