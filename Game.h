#pragma once
#include "Stages.h"
#include "Block.h"
#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Game {
    private:
        int level;
        int score;
        int lines;
        int i;
	    int is_gameover=0;
        char keytemp;
        char total_block[21][14];
        Stages* stages;
        Printer* printer;
        Block* curr_block;
        Block* next_block;
        Block* keeped_block;
    public:
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
        int keep();
};