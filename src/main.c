#include <stdio.h>
#include <stdbool.h>
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