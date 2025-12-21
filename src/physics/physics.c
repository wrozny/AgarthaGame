#include "physics/physics.h"
#include "ds/stb_ds.h"

/*
    Returns either -1, 0 or 1 based on the direction of x
*/
static inline int MathSignf(float x) {
    return (x > 0.0f) - (x < 0.0f);
}

/*
    Returns either -1, 0 or 1 based on the direction x but with margin of error for checking meaningfull input
*/
static inline int MathSignfEpsilon(float x, float epsilon) {
    return (x > epsilon) - (x < -epsilon);
}

/*
    Returns the bigger value
*/
static inline float MathMaxf(float a, float b) {
    if(a > b) {
        return a;
    }
    return b;
}

/*
    Returns the smaller value
*/
static inline float MathMinf(float a, float b) {
    if (a < b) {
        return a;
    }
    return b;
}

/*
    Returns the absolute value of x
*/
static inline float MathAbsf(float x) {
    return x < 0.0f? -x : x;
}

/*
    Floors the float x
*/
static inline float MathFloorf(float x) {
    return (float)((int)(x));
}

/*
    Removes the floating point from vector2 coordinates
*/
static inline Vector2 MathFloorVector2(Vector2 vec) {
    return (Vector2) {.x = MathFloorf(vec.x), .y = MathFloorf(vec.y)};
}

/*
    Applies velocity vector to position vector based on delta time
*/
static inline Vector2 PhysicsApplyVelocityToVector2(Vector2 pos, Vector2 velocity, float deltaTime) {
    return (Vector2) {.x = pos.x + (velocity.x * deltaTime), .y = pos.y + (velocity.y * deltaTime)};
}

/*
    Returns whether 2 objects are colliding
*/
static inline bool CollisionsObjectsColliding(GameObject *a, GameObject *b) {
    return !(a->pos.x + a->size.x <= b->pos.x ||  // a is left of b
             a->pos.x >= b->pos.x + b->size.x ||  // a is right of b
             a->pos.y + a->size.y <= b->pos.y ||  // a is above b
             a->pos.y >= b->pos.y + b->size.y);   // a is below b
}

/*
    Returns whether 2 objects are colliding, with a margin of error (epsilon).
    If the overlap is smaller than epsilon, it returns false.
*/
static inline bool CollisionsObjectsCollidingEpsilon(GameObject *a, GameObject *b, float epsilon) {
    return !(a->pos.x + a->size.x <= b->pos.x + epsilon ||  // a is left of b
             a->pos.x >= b->pos.x + b->size.x - epsilon ||  // a is right of b
             a->pos.y + a->size.y <= b->pos.y + epsilon ||  // a is above b
             a->pos.y >= b->pos.y + b->size.y - epsilon);   // a is below b
}


void PhysicsResolveObjectTick(PhysicsObject *target, ObjectGroup_t **objectGroups, float deltaTime) {
    if(target->physicsStepCompleted) {
        return;
    }

    // too big of a delta time (less than 10 fps) for physics calculation, clipping could happen
    // might implement better system in the future, one that also handles bigger velocities
    if (deltaTime > 0.1f) {
        return;
    }

    target->previousPos = target->gameObject.pos;
    target->inAir = true;

    // x resolution static objects
    float moveX = target->velocity.x * deltaTime;
    target->gameObject.pos.x += moveX;
    
    for (ObjectGroup_t **groupsPtr = objectGroups; *groupsPtr; ++groupsPtr) {
        ObjectGroup_t *currObjectGroup = *groupsPtr;

        // static object resolution
        if(currObjectGroup->staticObjects) {
            size_t staticObjectCount = hmlen(currObjectGroup->staticObjects);

            for (int i = 0; i < staticObjectCount; i++) {
                StaticObject *currStaticObject = currObjectGroup->staticObjects[i].value;
                GameObject *staticGameObject = &currStaticObject->gameObject;

                if (CollisionsObjectsColliding(&target->gameObject, staticGameObject)) {
                    if (target->velocity.x > 0) 
                        target->gameObject.pos.x = staticGameObject->pos.x - target->gameObject.size.x;
                    else if (target->velocity.x < 0) 
                        target->gameObject.pos.x = staticGameObject->pos.x + staticGameObject->size.x;
                    target->velocity.x = 0;
                }
            }
        }


        // physics object resolution
        // TODO
    }


    // y resolution
    float moveY = target->velocity.y * deltaTime;
    target->gameObject.pos.y += moveY;

    for (ObjectGroup_t **groupsPtr = objectGroups; *groupsPtr; ++groupsPtr) {
        ObjectGroup_t *currObjectGroup = *groupsPtr;

        // static object resolution
        if(currObjectGroup->staticObjects) {
            size_t staticObjectCount = hmlen(currObjectGroup->staticObjects);
            for (int i = 0; i < staticObjectCount; i++) {
                StaticObject *currStaticObject = currObjectGroup->staticObjects[i].value;
                GameObject *staticGameObject = &currStaticObject->gameObject;

                if (CollisionsObjectsColliding(&target->gameObject, staticGameObject)) {
                    if (target->velocity.y > 0) {
                        target->gameObject.pos.y = staticGameObject->pos.y - target->gameObject.size.y;
                        target->inAir = false;

                        // friction calculation
                        float friction = GameObjectGetFriction(staticGameObject->spriteId);
                        float frictionLoss = friction * deltaTime;
                        if (MathAbsf(target->velocity.x) <= frictionLoss) target->velocity.x = 0;
                        else target->velocity.x -= MathSignf(target->velocity.x) * frictionLoss;

                    } else if (target->velocity.y < 0) {
                        target->gameObject.pos.y = staticGameObject->pos.y + staticGameObject->size.y;
                    }
                    target->velocity.y = 0;
                }
            }
        }

        // physics object resolution
        // TODO
    }

    target->physicsStepCompleted = true;
}