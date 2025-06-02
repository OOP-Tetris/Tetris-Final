#pragma once
#include "Reverse.h"
#include "Maze.h"
#include "Mirror.h"

class Weird :
    public Reverse, public Maze, public Mirror
{
public:
    Weird();
    ~Weird() = default;
    void init() override;
    int move_block() override;
    int strike_check() override;
    void block_start(Block* b) override;
    bool isCleared() override;

    int check_full_line() override;
    void draw_ghostBlock() override;
    bool check_collision(Block* b) override;

    void makeMaze(char total_block[21][14]) override;
    int operate_key(int keytemp) override;
};

