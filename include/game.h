#include "raylib.h"
#include "raymath.h"
#include "assets.h"
#include "gobjects.h"
#include "scene.h"
#include "game_maps.h"
#include "player.h"
#include "collisions.h"
#include "hashing.h"

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