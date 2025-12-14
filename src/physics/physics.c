#include "physics/physics.h"
#include "ds/stb_ds.h"

/*
    Resolves collision between physics object and a collidable game object
*/
static inline void PhysicsResolveCollision_PO(PhysicsObject *a, GameObject *b) {
    //!TODO
}

/*
    Resolves collision between 2 physics objects
*/
static inline void PhysicsResolveCollision_PP(PhysicsObject *a, PhysicsObject *b) {
    //!TODO
}

/*
    Resolves collision between physics object and a static object
*/
static inline void PhysicsResolveCollision_PS(PhysicsObject *a, StaticObject *b) {
    if(b->canCollide) {
        PhysicsResolveCollision_PO(a, &b->gameObject);
    }
}


/*
    Resolves the velocity applied to the physics object
*/
void PhysicsResolveObjectTick(PhysicsObject *target, ObjectGroup_t **objectGroups, float deltaTime) {
    Vector2 oldPosition = target->gameObject.pos;
    Vector2 newPosition = 
        (Vector2) {
            .x = target->gameObject.pos.x + target->velocity.x * deltaTime, 
            .y = target->gameObject.pos.y + target->velocity.y * deltaTime
        };
    
    for (; *objectGroups; ++objectGroups) {
        ObjectGroup_t *currentGroup = *objectGroups;

        if(currentGroup->staticObjects) {
            size_t staticObjectCount = hmlen(currentGroup->staticObjects);

            for(int i = 0; i < staticObjectCount; i++) {
                //!TODO
            }
        }

        if(currentGroup->physicsObjects) {
            size_t physicsObjectCount = hmlen(currentGroup->physicsObjects);

            for(int i = 0; i < physicsObjectCount; i++) {
                //!TODO
            }
        }
    }
}