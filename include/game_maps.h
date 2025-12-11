#pragma once
#include "scene.h"
#include "assets.h"

typedef enum MapType {
    MAPTYPE_AGARTHA_START = 1
} MapType;

#define MAP1_SIZE_HORIZONTAL 10
#define MAP1_SIZE_VERTICAL 6
#define MAP1_BLOCK_SIZE 64

extern const char map1[MAP1_SIZE_VERTICAL][MAP1_SIZE_HORIZONTAL];

/*
    Loads map into scene
*/
void LoadMapToScene(Scene* scene, MapType mapType);