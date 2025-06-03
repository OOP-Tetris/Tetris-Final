#pragma once
#include "Game.h"
#include "Normal.h"

class Mirror : public virtual Normal
{
protected:
    int up;
    int down;
    int left;
    int right;
public:
    Mirror();
    Mirror(int score);
    ~Mirror() override;
    int operate_key(int tempkey) override;
    int random_key();
    void reset_key();
    int move_block() override;
    bool isCleared() override;
};

