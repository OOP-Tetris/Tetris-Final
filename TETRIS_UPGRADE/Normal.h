#pragma once
#include "Game.h"

class Normal : public Game {
public:
    void init() override;
    int move_block() override;
    int strike_check() override;
    void block_start(Block* b) override;
};

