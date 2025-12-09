#include <stdio.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "ds/stb_ds.h"

#include "game.h"


int main() {
    if(!InitGame()) {
        printf("Failed to initialize the game!");
        return -1;
    }
    RunGame();
    CloseGame();

    return 0;
}