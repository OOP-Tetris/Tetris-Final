#pragma once
#include "Stages.h"
#include "Block.h"
#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define EXT_KEY 0xffffffe0
#define KEY_LEFT 0x4b
#define KEY_RIGHT 0x4d
#define KEY_UP 0x48
#define KEY_DOWN 0x50
#define KEEP 0x6b

class Game {
protected:
    bool check_FirstComb = true;
    int level;
    int score;
    int lines;
    int i;
    int is_gameover = 0;
    char keytemp;
    char total_block[21][14];
    Stages* stages;
    Printer* printer;
    Block* curr_block;
    Block* next_block;
    Block* keeped_block;
    bool cleared = false;
    Block* prev_ghostBlock = nullptr;
public:
    Game();
    virtual ~Game();

    virtual void init() = 0;
    virtual int move_block() = 0;
    virtual int strike_check() = 0;
    virtual void block_start(Block* b) = 0;
    virtual void reset_stage();
    virtual int operate_key(int keytemp);
    //이 함수가 거꾸로 나라에는 맏지 않아 가상함수로 받고 Reverse.h에 override해서 재정의했습니다
    virtual int check_full_line();
    virtual bool isCleared() = 0;
    

    void run(); // 공통 게임 루프
    void play_loop();
    int merge_block();
    int rotate();
    void setLevel(int le) {
        level = le;
    }
    bool getCleared() {
        return cleared;
    }
    int getLevel() {
        return level;
    }
    int keep();

    int getScore() {
        return score;
    }
    // 어디에 떨어질지 미리 보여주기
    virtual void draw_ghostBlock();
    virtual bool check_collision(Block* b);

};
