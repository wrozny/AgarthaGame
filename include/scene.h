#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "ds/vector.h"
#include "game_object.h"
#include "collisions.h"

typedef struct Scene {
    Vector *staticObjects;
    Vector *physicsObjects;
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
    Saves all immovable objects as a single texture
*/
void SceneOptimize(Scene* scene);

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