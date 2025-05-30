#pragma once
#include "Game.h"

class Reverse : public Game {
public:
    void init() override;
    int move_block() override;
    int strike_check() override;
    void block_start(Block* b) override;
    bool isCleared() override;
    //추가된 함수로 이 함수와 move_block함수 그리고 strike_check함수 내용이 변경 및 추가되었습니다
    bool check_overflow();
    int check_full_line() override;
    void draw_ghostBlock() override;
    bool check_collision(Block* b) override;
};
