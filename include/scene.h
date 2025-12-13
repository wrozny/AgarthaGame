#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "gobjects.h"
#include "physics/physics.h"
#include "hashing.h"



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