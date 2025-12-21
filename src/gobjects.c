#include "gobjects.h"
#include "ds/stb_ds.h"

static uint32_t g_nextGameObjectId = 0;


/*
    Draws game object
*/
void GameObjectDraw(GameObject *gameObject) {
    AssetsDrawSprite(
        gameObject->spriteId, 
        (Rectangle) {
            .x = gameObject->pos.x,
            .y = gameObject->pos.y,
            .width = gameObject->size.x,
            .height = gameObject->size.y
        },
        gameObject->rotation
    );
}

/*
    Draws the outline of a game object
*/
void GameObjectDrawOutline(GameObject* gameObject) {
    DrawRectangleLines((int)gameObject->pos.x, (int)gameObject->pos.y, (int)gameObject->size.x, (int)gameObject->size.y, RED);
}

/*
    Allocates memory for a game object and returns pointer to it
*/
GameObject GameObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation) {
    GameObject newGameObject;

    newGameObject.spriteId = spriteId;
    newGameObject.pos = pos;
    newGameObject.size = size;
    newGameObject.rotation = rotation;
    newGameObject.objectId = g_nextGameObjectId++;

    return newGameObject;
}


/*
    Creates new physics object and returns pointer to it
*/
PhysicsObject* PhysicsObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation) {
    PhysicsObject *newPhysicsObject = malloc(sizeof(PhysicsObject));

    newPhysicsObject->gameObject = GameObjectCreate(spriteId, pos, size, rotation);
    newPhysicsObject->previousPos = (Vector2) {0.0f, 0.0f};
    newPhysicsObject->velocity = (Vector2){0.0f, 0.0f};
    newPhysicsObject->inAir = true;
    newPhysicsObject->physicsStepCompleted = false;
    newPhysicsObject->mass = 100.0f;

    return newPhysicsObject;
}


/*
    Creates new static object and returns pointer to it
*/
StaticObject* StaticObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation, bool canCollide) {
    StaticObject *newStaticObject = malloc(sizeof(StaticObject));

    newStaticObject->gameObject = GameObjectCreate(spriteId, pos, size, rotation);
    newStaticObject->canCollide = canCollide;

    return newStaticObject;
}


/*
    Applies the velocity to the physics objects position
*/
void PhysicsObjectApplyVelocity(PhysicsObject *physicsObject, double deltaTime) {
    float tickVelocityX = (physicsObject->velocity.x * (float)deltaTime);
    float tickVelocityY = (physicsObject->velocity.y * (float)deltaTime);

    physicsObject->previousPos = physicsObject->gameObject.pos;

    physicsObject->gameObject.pos = (Vector2) {
        tickVelocityX + physicsObject->gameObject.pos.x,
        tickVelocityY + physicsObject->gameObject.pos.y
    };

    physicsObject->velocity = (Vector2) {
        physicsObject->velocity.x - tickVelocityX,
        physicsObject->velocity.y - tickVelocityY
    };
}


/*
    Creates new object group
*/
ObjectGroup_t* ObjectGroupCreate() {
    ObjectGroup_t *newGroup = malloc(sizeof(ObjectGroup_t));

    newGroup->physicsObjects = NULL;
    newGroup->staticObjects = NULL;

    return newGroup;
}


/*
    Frees the object group
*/
void ObjectGroupFree(ObjectGroup_t* objectGroup) {
    if(!objectGroup->staticObjects) {
        int staticObjectsCount = (int)hmlen(objectGroup->staticObjects);

        for(int i = 0; i < staticObjectsCount; i++) {
            StaticObject *currStaticObject = objectGroup->staticObjects[i].value;
            free(currStaticObject);
        }
    }

    if(!objectGroup->physicsObjects) {
        int physicsObjectsCount = (int)hmlen(objectGroup->physicsObjects);

        for(int i = 0; i < physicsObjectsCount; i++) {
            PhysicsObject *currPhysicsObject = objectGroup->physicsObjects[i].value;
            free(currPhysicsObject);
        }
    }

    hmfree(objectGroup->staticObjects);
    hmfree(objectGroup->physicsObjects);

    free(objectGroup);
}


/*
    Draws the object group
*/
void ObjectGroupDraw(ObjectGroup_t* objectGroup) {
    if(objectGroup->staticObjects) {
        int staticObjectsCount = (int)hmlen(objectGroup->staticObjects);

        for(int i = 0; i < staticObjectsCount; i++) {
            StaticObject *currStaticObject = objectGroup->staticObjects[i].value;
            GameObjectDraw(&currStaticObject->gameObject);
        }
    }

    if(objectGroup->physicsObjects) {
        int physicsObjectsCount = (int)hmlen(objectGroup->physicsObjects);

        for(int i = 0; i < physicsObjectsCount; i++) {
            PhysicsObject *currPhysicsObject = objectGroup->physicsObjects[i].value;
            GameObjectDraw(&currPhysicsObject->gameObject);
        }
    }
}


/*
    Adds new physics object to the group or overrides
*/
void ObjectGroupSetPhysicsObject(ObjectGroup_t *objectGroup, PhysicsObject* physicsObject) {
    uint32_t objectId = physicsObject->gameObject.objectId;
    hmput(objectGroup->physicsObjects, objectId, physicsObject);
}


/*
    Adds new static object to the group or overrides
*/
void ObjectGroupSetStaticObject(ObjectGroup_t *objectGroup, StaticObject* staticObject) {
    uint32_t objectId = staticObject->gameObject.objectId;
    hmput(objectGroup->staticObjects, objectId, staticObject);
}


/*
    Removes element with given objectId
*/
bool ObjectGroupRemove(ObjectGroup_t* objectGroup, uint32_t objectId) {
    if(objectGroup->physicsObjects) {
        PhysicsObject *currPhysicsObject = hmget(objectGroup->physicsObjects, objectId);

        if(currPhysicsObject) {
            free(currPhysicsObject);
            return hmdel(objectGroup->physicsObjects, objectId);
        }
    }

    if(objectGroup->staticObjects) {
        StaticObject *currStaticObject = hmget(objectGroup->staticObjects, objectId);

        if(currStaticObject) {
            free(currStaticObject);
            return hmdel(objectGroup->staticObjects, objectId);
        }
    }

    return false;
}
