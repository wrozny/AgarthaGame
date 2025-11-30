#include "game_object.h"


/*
    Draws game object
*/
void GameObjectDraw(GameObject* gameObject) {
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
    Allocates memory for a game object and returns pointer to it
*/
GameObject* GameObjectCreate(SpriteId spriteId, Vector2 pos, Vector2 size, float rotation) {
    GameObject *newGameObject = malloc(sizeof(GameObject));
    newGameObject->spriteId = spriteId;
    newGameObject->pos = pos;
    newGameObject->size = size;
    newGameObject->rotation = rotation;
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

    return newPhysicsObject;
}

/*
    Frees the allocated physics object
*/
void PhysicsObjectDestroy(PhysicsObject *physicsObject) {
    free(physicsObject->gameObject);
    free(physicsObject);
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
    Frees the allocated static object
*/
void StaticObjectDestroy(StaticObject *staticObject) {
    free(staticObject->gameObject);
    free(staticObject);
}

/*
    Applies the velocity to the physics objects position
*/
void PhysicsObjectApplyVelocity(PhysicsObject *physicsObject, double deltaTime) {
    float tickVelocityX = (physicsObject->velocity.x * (float)deltaTime);
    float tickVelocityY = (physicsObject->velocity.y * (float)deltaTime);

    physicsObject->previousPos = physicsObject->gameObject->pos;

    physicsObject->gameObject->pos = (Vector2) {
        tickVelocityX + physicsObject->gameObject->pos.x,
        tickVelocityY + physicsObject->gameObject->pos.y
    };

    physicsObject->velocity = (Vector2) {
        physicsObject->velocity.x - tickVelocityX,
        physicsObject->velocity.y - tickVelocityY
    };
}

// /*
//     Creates new physics object and returns pointer to it
// */
// PhysicsObject* PhysisObjectCreate(int spriteId, Vector2 pos, Vector2 size, float rotation) {
//     PhysicsObject* newPhysicsObject = (PhysicsObject*)malloc(sizeof(PhysicsObject));
//     newPhysicsObject->objectData = ObjectDataCreate(spriteId, pos, size, rotation);
    
//     return newPhysicsObject;    
// }

// /*
//     Creates new static object and returns pointer to it
// */
// StaticObject* StaticObjectCreate(int spriteId, Vector2 pos, Vector2 size, float rotation) {
//     StaticObject* newStaticObject = (StaticObject*)malloc(sizeof(StaticObject));
//     newStaticObject->objectData = ObjectDataCreate(spriteId, pos, size, rotation);
//     return newStaticObject;  
// }

// /*
//     Draws the physics object
// */
// void PhysicsObjectDraw(PhysicsObject* physicsObject) {
    
// }

// /*
//     Draws the static object
// */
// void StaticObjectDraw(StaticObject* staticObject, Rectangle rect) {
//     DrawTextureRec(staticObject->objectData->spriteData->tex, rect, staticObject->objectData->pos, WHITE);
// }

// /*
//     Frees the physics object memory
// */
// void PhysicsObjectDestroy(PhysicsObject* physicsObject) {

// }

// /*
//     Frees the static object memory
// */
// void StaticObjectDestroy(StaticObject* staticObject) {

// }
