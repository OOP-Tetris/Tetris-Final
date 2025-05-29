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
};

