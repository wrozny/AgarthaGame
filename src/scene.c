#include "scene.h"

#include "ds/stb_ds.h"

Scene* SceneCreate() {
    Scene* newScene = (Scene*)malloc(sizeof(Scene));
    newScene->allObjects = ObjectGroupCreate();
    newScene->chunks = NULL;
    newScene->gravity = 9.81f;
    return newScene;
}

void SceneDestroy(Scene* scene) {
    ObjectGroupFree(scene->allObjects);
    hmfree(scene->chunks);
    free(scene);
}

void SceneDraw(Scene* scene) {
   ObjectGroupDraw(scene->allObjects);
}

/*
    Calculates physics tick for every physics object in the scene
*/
void SceneUpdatePhysics(Scene* scene, double deltaTime) {
    
}

/*
    Adds new StaticObject to scene
*/
void SceneAddStaticObject(Scene* targetScene, StaticObject *staticObject) {
    ObjectGroupSet(targetScene->allObjects, staticObject);
}

/*
    Adds new object with physics applied to scene
*/
void SceneAddPhysicsObject(Scene* targetScene, PhysicsObject *physicsObject) {
    ObjectGroupSet(targetScene->allObjects, physicsObject);
}