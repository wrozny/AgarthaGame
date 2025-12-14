#include "scene.h"
#include "ds/stb_ds.h"

#include "player.h"

ObjectGroup_t **SceneObjectGroupBuffer;

/*
    Returns chunk if exists, otherwise creates one
*/
static inline ObjectGroup_t* SceneEnsureChunk_f(Scene* targetScene, uint32_t chunkId) {
    ObjectGroup_t *chunk = hmget(targetScene->chunks, chunkId);

    if(!chunk) {
        ObjectGroup_t *newChunk = ObjectGroupCreate();
        hmput(targetScene->chunks, chunkId, newChunk);
        chunk = hmget(targetScene->chunks, chunkId);
    }

    return chunk;
}

/*
    Returns pointer to chunk if exists, otherwise NULL
*/
static inline ObjectGroup_t* SceneGetChunk_f(Scene* targetScene, uint32_t chunkId) {
    return hmget(targetScene->chunks, chunkId);
}

Scene* SceneCreate() {
    Scene* newScene = (Scene*)malloc(sizeof(Scene));
    newScene->allObjects = ObjectGroupCreate();
    newScene->chunks = NULL;
    newScene->gravity = 9.81f;
    
    return newScene;
}

void SceneDestroy(Scene* scene) {
    ObjectGroupFree(scene->allObjects);
    hmfree(scene->chunks);
    free(scene);
}

void SceneDraw(Scene* scene) {
    SceneUpdateObjectGroupBuffer(scene, 
        (Rectangle) {
            .x = PlayerCamera.target.x, 
            .y = PlayerCamera.target.y, 
            .width = 960.0f / PlayerCamera.zoom, 
            .height = 720.0f / PlayerCamera.zoom
        }
    );

    ObjectGroup_t **chunkLookupPtr = SceneObjectGroupBuffer;
    
    for(; *chunkLookupPtr; ++chunkLookupPtr) {
        ObjectGroup_t *currentChunk = *chunkLookupPtr;
        ObjectGroupDraw(currentChunk);
    }
}

/*
    Draws the scene with debug data
*/
void SceneDrawDebug(Scene* scene) {
    SceneUpdateObjectGroupBuffer(scene, 
        (Rectangle) {
            .x = PlayerCamera.target.x, 
            .y = PlayerCamera.target.y, 
            .width = 960.0f / PlayerCamera.zoom, 
            .height = 720.0f / PlayerCamera.zoom
        }
    );

    ObjectGroup_t **chunkLookupPtr = SceneObjectGroupBuffer;
    int chunks = 0;

    for(; *chunkLookupPtr; ++chunkLookupPtr) {
        ObjectGroup_t *currentChunk = *chunkLookupPtr;
        StaticObject *anyStaticObject = currentChunk->staticObjects[0].value;

        int chunkX;
        int chunkY;

        if(anyStaticObject) {
            chunkX = ((int)(anyStaticObject->gameObject.pos.x) / CHUNK_PIXEL_SIZE) * CHUNK_PIXEL_SIZE;
            chunkY = ((int)(anyStaticObject->gameObject.pos.y) / CHUNK_PIXEL_SIZE) * CHUNK_PIXEL_SIZE;
        }

        DrawRectangleLines(chunkX, chunkY, CHUNK_PIXEL_SIZE, CHUNK_PIXEL_SIZE, WHITE);
        ObjectGroupDraw(currentChunk);
        chunks++;
    }

    char buffer[64];

    #ifdef WIN32
        sprintf_s(buffer, 64, "chunks = %d", chunks);
    #else
        sprintf(buffer, "chunks = %d", chunks);
    #endif

    
    DrawText(buffer, (int)PlayerCamera.target.x, (int)PlayerCamera.target.y, 20, WHITE);
}


/*
    Calculates physics tick for every physics object in the scene
*/
void SceneUpdatePhysics(Scene* scene, double deltaTime) {
    
}

/*
    Adds new StaticObject to scene
*/
void SceneAddStaticObject(Scene* targetScene, StaticObject *staticObject) {
    ObjectGroupSet(targetScene->allObjects, staticObject);
    uint32_t chunkId = SceneGetChunkId(staticObject->gameObject.pos.x, staticObject->gameObject.pos.y);
    ObjectGroup_t* chunk = SceneEnsureChunk_f(targetScene, chunkId);
    ObjectGroupSet(chunk, staticObject);
}

/*
    Adds new object with physics applied to scene
*/
void SceneAddPhysicsObject(Scene* targetScene, PhysicsObject *physicsObject) {
    ObjectGroupSet(targetScene->allObjects, physicsObject);
    uint32_t chunkId = SceneGetChunkId(physicsObject->gameObject.pos.x, physicsObject->gameObject.pos.y);
    ObjectGroup_t* chunk = SceneEnsureChunk_f(targetScene, chunkId);
    ObjectGroupSet(chunk, physicsObject);
}

/*
    Given the target rectangle writes to SceneObjectGroupBuffer every ObjectGroup pointer that target is in 
    useful both in physics simulation and chunk rendering
*/
void SceneUpdateObjectGroupBuffer(Scene *scene, Rectangle target) {
    int16_t minChunkX = (int16_t)target.x / CHUNK_PIXEL_SIZE;
    int16_t maxChunkX = (int16_t)(target.x + target.width) / CHUNK_PIXEL_SIZE;

    int16_t minChunkY = (int16_t)target.y / CHUNK_PIXEL_SIZE;
    int16_t maxChunkY = (int16_t)(target.y + target.height) / CHUNK_PIXEL_SIZE;

    int freeIdx = 0;
    
    for (int16_t currChunkX = minChunkX; currChunkX <= maxChunkX; currChunkX++) {
        for (int16_t currChunkY = minChunkY; currChunkY <= maxChunkY; currChunkY++) {
            //DrawRectangleLines();

            uint32_t chunkId = ScenePackInt16(currChunkX, currChunkY);
            ObjectGroup_t *objectGroup = SceneGetChunk_f(scene, chunkId);

            if (objectGroup) {
                SceneObjectGroupBuffer[freeIdx] = objectGroup;
                freeIdx++;
            }
        }
    }

    SceneObjectGroupBuffer[freeIdx] = NULL;
}
