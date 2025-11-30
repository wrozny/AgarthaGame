#include "game_maps.h"

const char map1[MAP1_SIZE_VERTICAL][MAP1_SIZE_HORIZONTAL] = {
    // {1, 1 ,1, 1, 1, 1, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    // {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
    // {1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
    // {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    {1,1,1,0,0,0,0,0,0,1},
    {0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {0,0,0,0,0,1,0,0,0,1},
    {0,0,0,0,0,0,0,1,0,1},
    {0,0,0,0,1,1,1,1,1,1}
};

/*
    Loads map into scene
*/
void LoadMapToScene(Scene* scene, MapType mapType) {
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Loading map...", 0, 0, 50, WHITE);
    EndDrawing();

    int rows;
    int cols;
    const char* mapData;

    switch (mapType) {
        case MAPTYPE_AGARTHA_START:
            rows = MAP1_SIZE_VERTICAL;
            cols = MAP1_SIZE_HORIZONTAL;
            mapData = &map1[0][0];
            break;
        default:
            return;
    }

    Vector2 blockSize;
    blockSize.x = (float)MAP1_BLOCK_SIZE;
    blockSize.y = (float)MAP1_BLOCK_SIZE;

    for(int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            char objectType = mapData[y * cols + x]; 
            char objectTypeAbove = mapData[(y - 1) * cols + x]; 

            if (objectType == 2) {
                Vector2 pos;
                pos.x = (float)(x * MAP1_BLOCK_SIZE + MAP1_BLOCK_SIZE);
                pos.y = (float)(y * MAP1_BLOCK_SIZE);

                PhysicsObject *newPhysicsObject = PhysicsObjectCreate(SI_ASHTAR_SHERAN_ICON, pos, (Vector2){64, 64}, 0.0f);
                SceneAddPhysicsObject(scene, newPhysicsObject);

                continue;
            }

            if(objectType == 1) {
                SpriteId spriteIdToRender = SI_TILE_DIRT;

                if(y == 0) {
                    spriteIdToRender = SI_TILE_GRASS;
                }

                if(objectTypeAbove == 0) {
                    spriteIdToRender = SI_TILE_GRASS;
                }

                Vector2 pos;
                pos.x = (float)(x * MAP1_BLOCK_SIZE + MAP1_BLOCK_SIZE);
                pos.y = (float)(y * MAP1_BLOCK_SIZE);
                StaticObject* obj = StaticObjectCreate(spriteIdToRender, pos, blockSize, 0.0f, true);
                SceneAddStaticObject(scene, obj);
            }
        }
    }

    printf("Amount of objects loaded = %d\n", scene->staticObjects->size + scene->physicsObjects->size);
}