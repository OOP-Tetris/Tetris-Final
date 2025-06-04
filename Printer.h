#pragma once
#include "Color.h"
#include "Block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Printer {
    private:
        int ab_x;
        int ab_y;
    public:
        Printer();
        int get_x();
        int get_y();
        int gotoxy(int x, int y);
        void SetColor(int color);
        void hideCursor() {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO cursorInfo;

            GetConsoleCursorInfo(hConsole, &cursorInfo);
            cursorInfo.bVisible = FALSE; // Ŀ�� �����
            SetConsoleCursorInfo(hConsole, &cursorInfo);
        }
        void show_keys();
        int show_cur_block(Block& block);
        int erase_cur_block(Block& block);
        int show_next_block(Block& block, int level);
        int show_keeped_block(Block& block, int level);
        int show_logo();
        int show_total_block(char total_block[21][14], int level);
        int show_gamestat(int level, int score, int lines_left);
        int show_clear_screen(int score);
        void show_combo();

        int show_gameover();
        void show_ghostBlock(Block& b);
        void erase_ghostBlock(Block& b, char total_block[21][14]);

        void draw_dialog_frame();
        void dialog_line(const char* speaker, const char* lines[], int lineCount);
        void first_story();
        void mirror_stage();
        void reverse_stage();
        void miro_stage();
        void repeat_level();
        void weird_stage();
        void ending();

        void flash_map_border();
};
