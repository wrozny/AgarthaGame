#include "assets.h"
#include "ds/stb_ds.h"

Texture2D *Assets_loadedTextures;
SpriteData Assets_spriteData[SI_END_ENUM];


/*
    Loads all the assets into memory
*/
void AssetsLoad() {
    //Assets_loadedTextures = create_vector(sizeof(Texture2D));

    //int blocksSpritesheet = AssetsLoadTexture("resources/blocks.png");

    // #include "res/agartha_jpeg.h"
    // int agarthaBackground = AssetsLoadTextureFromBytes(AGARTHA_JPEG_FORMAT, AGARTHA_JPEG, AGARTHA_JPEG_SIZE);
    // Texture2D* agarthaBackgroundTex = AssetsGetTexture(agarthaBackground);
    
    // AssetsLoadSpriteData(
    //     SI_BACKGROUND_AGARTHA, 
    //     agarthaBackground, 
    //     (IntRect) {.x = 0, .y = 0, .width = agarthaBackgroundTex->width, .height = agarthaBackgroundTex->height}
    // );

    //int blocksSpritesheet = AssetsLoadTexture("resources/blocks.png");

    #include "res/blocks_png.h"
    int blocksSpritesheet = AssetsLoadTextureFromBytes(BLOCKS_PNG_FORMAT, BLOCKS_PNG, BLOCKS_PNG_SIZE);

    AssetsLoadSpriteData(SI_TILE_GRASS, blocksSpritesheet, (IntRect)  {0, 0,  64, 64});
    AssetsLoadSpriteData(SI_TILE_DIRT, blocksSpritesheet,  (IntRect)  {0, 64, 64, 64});


    // #include "res/igor_png.h"
    // int igorTextureId = AssetsLoadTextureFromBytes(IGOR_PNG_FORMAT, IGOR_PNG, IGOR_PNG_SIZE);
    // Texture2D* igorTexture = AssetsGetTexture(igorTextureId);

    // AssetsLoadSpriteData(
    //     SI_ICON_IGOR, 
    //     igorTextureId, 
    //     (IntRect) {.x = 0, .y = 0, .width = igorTexture->width, .height = igorTexture->height}
    // );

    #include "res/ashtar_sheran_png.h"
    int ashtarSheranTextureId = AssetsLoadTextureFromBytes(ASHTAR_SHERAN_PNG_FORMAT, ASHTAR_SHERAN_PNG, ASHTAR_SHERAN_PNG_SIZE);
    Texture2D ashtarTexture = AssetsGetTexture(ashtarSheranTextureId);

    AssetsLoadSpriteData(
        SI_ASHTAR_SHERAN_ICON,
        ashtarSheranTextureId,
        (IntRect) {.x = 0, .y = 0, .width = ashtarTexture.width, .height = ashtarTexture.height}
    );


    printf("INFO: ASSETS: All the sprites are loaded!\n");
}

/*
    Frees all the assets that are inside memory
*/
void AssetsUnload() {
    for (int i = 0; i < arrlen(Assets_loadedTextures); i++) {
        Texture2D tex = Assets_loadedTextures[i];
        UnloadTexture(tex);
    }
    arrfree(Assets_loadedTextures);
}


/*
    Draws sprite at given position
*/
void AssetsDrawSprite(SpriteId spriteId, Rectangle destination, float rotation) {
    SpriteData spriteData = AssetsGetSpriteData(spriteId);
    static const Vector2 ORIGIN_ZERO = { 0.0f, 0.0f };

    DrawTexturePro(
        spriteData.tex, 
            (Rectangle){
                .x =      (float)spriteData.rect.x, 
                .y =      (float)spriteData.rect.y,
                .width =  (float)spriteData.rect.width,
                .height = (float)spriteData.rect.height
            }, 
        destination,
        ORIGIN_ZERO, 
        rotation, 
        WHITE
    );
}




/*
    Loads sprite data 
*/
void AssetsLoadSpriteData(SpriteId spriteId, int texId, IntRect rect) {
    Texture2D tex = AssetsGetTexture(texId);

    if(tex.id == 0) {
        printf("FATAL ERROR: Failed to load sprite with id: %d\n", spriteId);
        exit(-1);
    }

    Assets_spriteData[spriteId] = (SpriteData) {.rect = rect, .tex = tex};
}

/*
    Loads texture into memory from file and returns id to it
*/
// int AssetsLoadTexture(const char* filePath) {
//     Texture2D *tex = malloc(sizeof(Texture2D));
//     *tex = LoadTexture(filePath);
//     vec_push(Assets_loadedTextures, tex);

//     return Assets_loadedTextures->size - 1;
// }

/*
    Loads texture into memory from bytes
*/
int AssetsLoadTextureFromBytes(const char* fileType, const unsigned char* fileData, int dataSize) {
    //Texture2D *tex = malloc(sizeof(Texture2D));
    Texture2D tex;
    Image newImage = LoadImageFromMemory(fileType, fileData, dataSize);
    tex = LoadTextureFromImage(newImage);
    UnloadImage(newImage);

    if(tex.id == 0) {
        printf("FATAL ERROR: Failed to load embeded asset %s, %d bytes", fileType, dataSize);
        exit(-1);
    }

    arrpush(Assets_loadedTextures, tex);

    return arrlen(Assets_loadedTextures) - 1;
}

/*
    Returns loaded texture by id
*/
Texture2D AssetsGetTexture(int texId) {
    Texture2D tex = Assets_loadedTextures[texId];
    return tex;
}

/*
    Returns the loaded sprite data from memory
*/
SpriteData AssetsGetSpriteData(SpriteId spriteId) {
    return Assets_spriteData[spriteId];
}
