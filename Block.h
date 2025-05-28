#pragma once
#include "cstdlib"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Block {
    private:
        static char block[7][4][4][4];
        int block_shape;
        int block_angle;
        int block_x;
        int block_y;
        bool combo;
    public:
        Block() = delete;
        Block(int stick_rate, bool combo = false);
        Block(int shape, int rotate, int x, int y, bool combo = false);
        int get_x();
        int get_y();
        int get_shape();
        int get_angle();
        char (*get_block())[4];
        int get_number(int i, int j);
        void rotate(int angle);
        void movetoxy(int x, int y);
        void move_left();
        void move_right();
        void move_down();
        void move_up();
        int start();
        int start_Reversed();
};