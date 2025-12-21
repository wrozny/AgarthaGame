#include "game.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

Scene *currentScene;

float zoom = 1.0f;


static inline float clampf(float value, float min, float max) {
    if(value > max) {
        return max;
    }
    if(value < min) {
        return min;
    }
    return value;
}

void PhysicsUpdate(double deltaTime) {
    Vector2 inputDirection = InputGetDirection();
    //PlayerCamera.target = Vector2Add(PlayerCamera.target, Vector2Multiply(inputDirection, (Vector2){PLAYER_SPEED * (float)deltaTime, -PLAYER_SPEED * (float)deltaTime}));
    PlayerCamera.zoom = zoom;

    if(IsKeyDown(KEY_E)) {
        zoom += 1.0f * (float)deltaTime;
    }
    if(IsKeyDown(KEY_Q)) {
        zoom -= 1.0f * (float)deltaTime;
    }

    zoom = clampf(zoom, (1.0f / 3.0f), 3.0f);

    PhysicsObject *firstPhysicsObject = currentScene->allObjects->physicsObjects[0].value;

    if (firstPhysicsObject->velocity.x < 300.0f) {
        firstPhysicsObject->velocity = Vector2Add(firstPhysicsObject->velocity, Vector2Multiply(inputDirection, (Vector2) {400.0f * (float)deltaTime, 0.0f}));
    }

    if(!firstPhysicsObject->inAir && inputDirection.y) {
        firstPhysicsObject->velocity = Vector2Add((Vector2) {.x = 0.0f, .y = -600.0f}, firstPhysicsObject->velocity);
    }

    if(IsKeyDown(KEY_R)) {
        firstPhysicsObject->velocity = Vector2Zero();
        firstPhysicsObject->gameObject.pos = (Vector2) {.x = 128.0f, 128.0f};
    }

    PlayerCamera.target = Vector2Subtract(firstPhysicsObject->gameObject.pos, (Vector2) {.x = ((960.0f / 2.0f) / PlayerCamera.zoom) - 32.0f, .y = (720.0f / 2.0f) / PlayerCamera.zoom});

    SceneUpdatePhysics(currentScene, deltaTime);
}

void OnFrameRender(double deltaTime) {
    BeginMode2D(PlayerCamera);
    SceneDraw(currentScene);
    EndMode2D();
}


bool InitGame() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Agartha Game");
    AssetsLoad(); 
    currentScene = SceneCreate();
    LoadMapToScene(currentScene, MAPTYPE_AGARTHA_START);
    InitPlayer();
    SetTargetFPS(60);

    SceneObjectGroupBuffer = calloc(32, sizeof(ObjectGroup_t*));


    PhysicsObject *firstPhysicsObject = currentScene->allObjects->physicsObjects[0].value;
    firstPhysicsObject->velocity = (Vector2){.x = 230.0f, .y = -300.0f};

    if (!IsWindowReady()) {
        return false;
    }

    return true;
}


void RunGame() {
    while(!WindowShouldClose()) {
        double deltaTime = GetFrameTime();
        PhysicsUpdate(deltaTime);
        BeginDrawing();
            ClearBackground(BLACK);
            OnFrameRender(deltaTime);
        EndDrawing();
    }
}

void CloseGame() {
    CloseWindow();
    SceneDestroy(currentScene);
    free(SceneObjectGroupBuffer);
    AssetsUnload();
}