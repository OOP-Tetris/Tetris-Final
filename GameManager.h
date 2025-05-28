#pragma once
#include "Game.h"

class GameManager {
private:
    Game* game;
    Printer printer;
public:
    int input_level();
    void run();
};

