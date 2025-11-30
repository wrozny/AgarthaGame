#include "game.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

Scene *currentScene;


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
    // inputDirection.x = inputDirection.x * PLAYER_SPEED * (float)deltaTime;
    // inputDirection.y = -inputDirection.y * PLAYER_SPEED * (float)deltaTime;

    float horizontalVelocity = inputDirection.x * PLAYER_SPEED * PLAYER_SPEED * (float)deltaTime;
    float verticalVelocity = 0.0f;

    if(!PlayerPhysicsObject->inAir) {
        verticalVelocity = -inputDirection.y * PLAYER_SPEED * 2.92f;
    }


    Vector2 newVelocity = 
        (Vector2) {
            clampf(PlayerPhysicsObject->velocity.x + horizontalVelocity, -PLAYER_SPEED * 1.5f, PLAYER_SPEED * 1.5f), 
            clampf(PlayerPhysicsObject->velocity.y + verticalVelocity, -PLAYER_SPEED * 5.0f, PLAYER_SPEED * 5.0f)
        };

    PlayerPhysicsObject->velocity = newVelocity;
   
    PlayerCamera.target = Vector2Subtract(PlayerPhysicsObject->gameObject->pos, (Vector2) {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
    SceneUpdatePhysics(currentScene, deltaTime);

    if(IsKeyDown(KEY_R)) {
        PlayerPhysicsObject->velocity = Vector2Zero();
        PlayerPhysicsObject->gameObject->pos = (Vector2) {100, -200};
    }
}

void OnFrameRender(double deltaTime) {
    BeginMode2D(PlayerCamera);
    SceneDraw(currentScene);
    EndMode2D();
    AssetsDrawSprite(SI_ASHTAR_SHERAN_ICON, (Rectangle) {.x = 0, .y = 360, .height = 360, .width = 240}, 0.0f);
}


bool InitGame() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Agartha Game");
    AssetsLoad(); 
    currentScene = SceneCreate();
    LoadMapToScene(currentScene, MAPTYPE_AGARTHA_START);
    InitPlayer();
    SetTargetFPS(60);

    SceneAddPhysicsObject(currentScene, PlayerPhysicsObject);

    PhysicsObject *sheran1 = (PhysicsObject*)vec_get(currentScene->physicsObjects, 0);
    sheran1->velocity = (Vector2) {500, -500};


    PhysicsObject *sheran2 = PhysicsObjectCreate(SI_ASHTAR_SHERAN_ICON, (Vector2){0, 100}, (Vector2){32, 32}, 0.0f);
    sheran2->velocity = (Vector2){800, -450};

    SceneAddPhysicsObject(currentScene, sheran2);

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
    AssetsUnload();
}