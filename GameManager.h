#pragma once
#include "Game.h"

class GameManager {
private:
    int manager_level;
    int score = 0;
    Game* game;
    Printer printer;
public:
    int input_level();
    void run();
};

