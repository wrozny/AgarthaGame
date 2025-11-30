#include "player.h"

Camera2D PlayerCamera;
PhysicsObject* PlayerPhysicsObject;


/*
    Initializes every variable needed for player
*/
void InitPlayer() {
    PlayerPhysicsObject = PhysicsObjectCreate(SI_ASHTAR_SHERAN_ICON, (Vector2) {300, 0}, (Vector2) {64, 64}, 0.0f);

    PlayerCamera.offset = Vector2Zero();
    PlayerCamera.rotation = 0.0f;
    PlayerCamera.target = Vector2Zero();
    PlayerCamera.zoom = 1.0f;
}


Vector2 InputGetDirection() {
    Vector2 direction;
    direction.x = -(float)IsKeyDown(KEY_A) + (float)IsKeyDown(KEY_D);
    direction.y = -(float)IsKeyDown(KEY_S) + (float)IsKeyDown(KEY_W);
    return direction;
}

