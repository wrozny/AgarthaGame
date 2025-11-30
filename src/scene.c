#include "scene.h"

Scene* SceneCreate() {
    Scene* newScene = (Scene*)malloc(sizeof(Scene));
    newScene->staticObjects = create_vector(sizeof(StaticObject));
    newScene->physicsObjects = create_vector(sizeof(PhysicsObject));
    newScene->gravity = 9.81f;
    return newScene;
}

void SceneDestroy(Scene* scene) {
    vec_deep_free(scene->staticObjects, StaticObjectDestroy);
    vec_deep_free(scene->physicsObjects, PhysicsObjectDestroy);
    free(scene);
}

void SceneDraw(Scene* scene) {
    for(int i = 0; i < scene->staticObjects->size; i++) {
        StaticObject *obj = vec_get(scene->staticObjects, i);
        GameObjectDraw(obj->gameObject);
    }

    for(int i = 0; i < scene->physicsObjects->size; i++) {
        PhysicsObject *obj = vec_get(scene->physicsObjects, i);
        GameObjectDraw(obj->gameObject);
    }
}

/*
    Calculates physics tick for every physics object in the scene
*/
void SceneUpdatePhysics(Scene* scene, double deltaTime) {
    deltaTime = (double)Clamp((float)deltaTime, 0.0f, 1.0f / 60.0f);

    Vector2 gravityVector2 = {0.0f, -scene->gravity * (float)deltaTime * 100};

    for(int i = 0; i < scene->physicsObjects->size; i++) {
        PhysicsObject *currentPhysicsObject = vec_get(scene->physicsObjects, i);
        currentPhysicsObject->inAir = true;
        currentPhysicsObject->velocity = Vector2Subtract(currentPhysicsObject->velocity, gravityVector2);
        PhysicsObjectApplyVelocity(currentPhysicsObject, deltaTime);

        if(fabs(currentPhysicsObject->velocity.x) < 7.5f) {
            currentPhysicsObject->velocity.x = 0.0f;
        }
        if(fabs(currentPhysicsObject->velocity.y) < 7.5f) {
            currentPhysicsObject->velocity.y = 0.0f;
        }

        for(int j = 0; j < scene->staticObjects->size; j++) {
            StaticObject *currentStaticObject = vec_get(scene->staticObjects, j);
            CollisionsResolvePhysicsAndStaticObjects(currentPhysicsObject, currentStaticObject);
        }
    }
}

/*
    Adds new StaticObject to scene
*/
void SceneAddStaticObject(Scene* targetScene, StaticObject* staticObject) {
    vec_push(targetScene->staticObjects, staticObject);
}

/*
    Adds new object with physics applied to scene
*/
void SceneAddPhysicsObject(Scene* targetScene, PhysicsObject* physicsObject) {
    vec_push(targetScene->physicsObjects, physicsObject);
}