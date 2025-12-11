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
    inputDirection.x = inputDirection.x * PLAYER_SPEED * (float)deltaTime;
    inputDirection.y = -inputDirection.y * PLAYER_SPEED * (float)deltaTime;

    PlayerCamera.target = Vector2Add(inputDirection, PlayerCamera.target);

    //printf("%.3f\n", 1 / GetFrameTime());
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