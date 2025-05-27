#pragma once
#include "Stages.h"
#include "Block.h"
#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Game {
protected:
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
public:

    //Game();
    //void run();
    //int init();
    ////거꾸로 나라 초기화하는 함수
    //int init_Reversed();
    //int input_data();
    //int move_block();
    ////거꾸로 나라의 블록 움직임을 나타내는 추가된 함수
    //int move_block_Reversed();
    //int strike_check();
    ////거꾸로 나라 전용 충돌 감지 함수 거의 strike_check함수와 비슷하지만 추가된 내용 블록의 y좌표가 0보다 작아도 충돌로 가정한다는 내용이 추가되었습니다
    //int strike_check_Reversed();
    //int merge_block();
    //int check_full_line();
    //int rotate();
    ////거꾸로 나라인지 여부를 판단하는 함수로 신규 추가됨
    //bool isReverseWorld(int level);
    Game();
    virtual ~Game();

    virtual void init() = 0;
    virtual int move_block() = 0;
    virtual int strike_check() = 0;
    virtual void block_start(Block* b) = 0;
    virtual void reset_stage();

    void run(); // 공통 게임 루프
    void play_loop();
    int input_data(); // 공통
    int merge_block();
    int check_full_line();
    int rotate();
    void setLevel(int le) {
        level = le;
    }

};