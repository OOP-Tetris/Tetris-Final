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
    ////�Ųٷ� ���� �ʱ�ȭ�ϴ� �Լ�
    //int init_Reversed();
    //int input_data();
    //int move_block();
    ////�Ųٷ� ������ ��� �������� ��Ÿ���� �߰��� �Լ�
    //int move_block_Reversed();
    //int strike_check();
    ////�Ųٷ� ���� ���� �浹 ���� �Լ� ���� strike_check�Լ��� ��������� �߰��� ���� ����� y��ǥ�� 0���� �۾Ƶ� �浹�� �����Ѵٴ� ������ �߰��Ǿ����ϴ�
    //int strike_check_Reversed();
    //int merge_block();
    //int check_full_line();
    //int rotate();
    ////�Ųٷ� �������� ���θ� �Ǵ��ϴ� �Լ��� �ű� �߰���
    //bool isReverseWorld(int level);
    Game();
    virtual ~Game();

    virtual void init() = 0;
    virtual int move_block() = 0;
    virtual int strike_check() = 0;
    virtual void block_start(Block* b) = 0;
    virtual void reset_stage();

    void run(); // ���� ���� ����
    void play_loop();
    int input_data(); // ����
    int merge_block();
    int check_full_line();
    int rotate();
    void setLevel(int le) {
        level = le;
    }

};