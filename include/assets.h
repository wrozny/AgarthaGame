#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "ds/vector.h"
#include "raylib.h"


typedef struct IntRect {
    int x;
    int y;
    int width;
    int height;
} IntRect;


typedef enum SpriteId {
    SI_TILE_GRASS,
    SI_TILE_DIRT,
    SI_ASHTAR_SHERAN_ICON,
    SI_END_ENUM
} SpriteId;


typedef struct SpriteData {
    IntRect rect;
    Texture2D* tex;
} SpriteData;


extern Vector* Assets_loadedTextures;
extern SpriteData Assets_spriteData[SI_END_ENUM];


/*
    Loads all the assets into memory
*/
void AssetsLoad();

/*
    Frees all the assets that are inside memory
*/
void AssetsUnload();

/*
    Loads sprite data 
*/
void AssetsLoadSpriteData(SpriteId spriteId, int texId, IntRect rect);

/*
    Loads texture into memory from file and returns id to it
*/
int AssetsLoadTexture(const char* filePath);

/*
    Loads texture into memory from bytes
*/
int AssetsLoadTextureFromBytes(const char* fileType, const unsigned char* fileData, int dataSize);

/*
    Returns the loaded sprite data from memory
*/
SpriteData AssetsGetSpriteData(SpriteId spriteId);

/*
    Returns loaded texture by id
*/
Texture2D* AssetsGetTexture(int texId);

/*
    Draws sprite at given position
*/
void AssetsDrawSprite(SpriteId spriteId, Rectangle destination, float rotation);
