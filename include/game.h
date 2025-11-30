#include "raylib.h"
#include "raymath.h"
#include "ds/vector.h"
#include "assets.h"
#include "game_object.h"
#include "scene.h"
#include "game_maps.h"
#include "player.h"
#include "collisions.h"
#include "hashing.h"
#include "ds/hashmap.h"

/*
    Initializes the game and returns if succeeded
*/
bool InitGame();

/*
    Starts the game loop
*/
void RunGame();

/*
    Closes the game
*/
void CloseGame();