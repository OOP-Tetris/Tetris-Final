#pragma once
#include "Game.h"
#include "Normal.h"

class Mirror : public Normal
{
private:
    int up;
    int down;
    int left;
    int right;
public:
    Mirror();
    ~Mirror() override;
    void init() override;
    int operate_key(int tempkey) override;
    int random_key();
    int move_block() override;
};

