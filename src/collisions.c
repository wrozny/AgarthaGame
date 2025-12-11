#include "collisions.h"

/*
    Returns true or false whether rects are inside eachother
*/
bool CollisionsRectsCollided(Rectangle rect1, Rectangle rect2) {
    // float aLeft = rect1.x;
    // float aRight = rect1.x + rect1.width;
    // float aTop = a->pos.y;
    // float aBottom = a->pos.y + a->size.y;

    // float bLeft = b->pos.x;
    // float bRight = b->pos.x + b->size.x;
    // float bTop = b->pos.y;
    // float bBottom = b->pos.y + b->size.y;

    // return (aRight > bLeft && aLeft < bRight && aBottom > bTop && aTop < bBottom);
    // !TODO
    return false;
}

/*
    Returns true or false whether game objects are inside eachother
*/
bool CollisionsGameObjectsCollided(GameObject a, GameObject b) {
    float aLeft = a.pos.x;
    float aRight = a.pos.x + a.size.x;
    float aTop = a.pos.y;
    float aBottom = a.pos.y + a.size.y;

    float bLeft = b.pos.x;
    float bRight = b.pos.x + b.size.x;
    float bTop = b.pos.y;
    float bBottom = b.pos.y + b.size.y;

    return (aRight > bLeft && aLeft < bRight && aBottom > bTop && aTop < bBottom);
}


/*
    Resolves collisions on physics object when collided with static object
*/
void CollisionsResolvePhysicsAndStaticObjects(PhysicsObject *physicsObject, StaticObject *staticObject) {
    // if(!staticObject->canCollide) {
    //     return;
    // }

    // GameObject a = physicsObject->gameObject;
    // GameObject b = staticObject->gameObject;

    // float aLeft = a.pos.x;
    // float aRight = a.pos.x + a.size.x;
    // float aTop = a.pos.y;
    // float aBottom = a.pos.y + a.size.y;

    // float bLeft = b.pos.x;
    // float bRight = b.pos.x + b.size.x;
    // float bTop = b.pos.y;
    // float bBottom = b.pos.y + b.size.y;

    // if(aRight >= bLeft && aLeft <= bRight && aBottom >= bTop && aTop <= bBottom) {
    //     float overlapLeft   = aRight - bLeft;
    //     float overlapRight  = bRight - aLeft;
    //     float overlapTop    = aBottom - bTop;
    //     float overlapBottom = bBottom - aTop;
    //     float minXOverlap = fminf(overlapLeft, overlapRight);
    //     float minYOverlap = fminf(overlapTop, overlapBottom);

    //     // Resolve using the axis with *less* penetration
    //     if (minXOverlap <= minYOverlap) {
    //         //Resolve horizontally
    //         if (overlapLeft < overlapRight) {
    //             a.pos.x -= overlapLeft;
    //         } else {
    //             a.pos.x += overlapRight;
    //         }
           
    //         physicsObject->velocity.x = 0.0f;
    //     } else {
    //         //Resolve vertically
    //         physicsObject->inAir = false;

    //         if (overlapTop < overlapBottom) {
    //             a.pos.y -= overlapTop;
    //         } else {
    //             a.pos.y += overlapBottom;
    //         }

    //         physicsObject->velocity.y = 0.0f;
    //     }
    // }
}

