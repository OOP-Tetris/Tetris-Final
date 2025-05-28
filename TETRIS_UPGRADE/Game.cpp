#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define EXT_KEY 0xffffffe0
#define KEY_LEFT 0x4b
#define KEY_RIGHT 0x4d
#define KEY_UP 0x48
#define KEY_DOWN 0x50

using namespace std;

Game::Game() {
    printer = new Printer();
    score = 0;
    lines = 0;
    level = 0;
    is_gameover = 0;
    cleared = false;
    stages = new Stages();
}

Game::~Game() {
    delete curr_block;
    delete next_block;
    delete printer;
    delete stages;
}

void Game::run() {
        score = 0;
        lines = 0;
        if (is_gameover == 3) {
            printer->show_logo();
        }
        is_gameover = 0;
        cleared = false;


        init();

        curr_block = new Block(stages->get_stick_rate(level));
        next_block = new Block(stages->get_stick_rate(level));
        block_start(curr_block);

        printer->show_next_block(*next_block, level);
        printer->show_total_block(total_block, level);
        printer->show_gamestat(level, score, stages->get_clear_line(level) - lines);
        printer->show_cur_block(*curr_block);
        cout << "start loop";
        play_loop();

        if (is_gameover == 3) {
            printer->show_logo();
        }
        if (is_gameover == 1) {
            score = 0;
            lines = 0;
            is_gameover = 0;


            init();
            return;
        }
        if (is_gameover == 4) {
            return;
        }
}

void Game::play_loop() {
    for (int i = 1;; i++) {
        printer->gotoxy(50, 1);
        cout << level;
        if (_kbhit()) {
            keytemp = _getche();
            if (keytemp == EXT_KEY) {
                keytemp = _getche();
                switch (keytemp) {
                case KEY_UP:
                    rotate();
                    break;
                case KEY_LEFT:
                    if (curr_block->get_x() > 1) {
                        printer->erase_cur_block(*curr_block);
                        curr_block->move_left();
                        if (strike_check()) curr_block->move_right();
                        printer->show_cur_block(*curr_block);
                    }
                    break;
                case KEY_RIGHT:
                    if (curr_block->get_x() < 14) {
                        printer->erase_cur_block(*curr_block);
                        curr_block->move_right();
                        if (strike_check()) curr_block->move_left();
                        printer->show_cur_block(*curr_block);
                    }
                    break;
                case KEY_DOWN:
                    is_gameover = move_block();
                    if (is_gameover != 1 && is_gameover != 3)
                        printer->show_cur_block(*curr_block);
                    break;
                }
            }
            else {
                while (_kbhit()) (void)_getch();
            }

            if (keytemp == 32) {
                while (is_gameover == 0) {
                    is_gameover = move_block();
                }
                printer->show_cur_block(*curr_block);
                while (_kbhit()) (void)_getch();
            }
        }

        if (i % stages->get_speed(level) == 0) {
            is_gameover = move_block();
            if (is_gameover != 1 && is_gameover != 3)
                printer->show_cur_block(*curr_block);
        }

        if (is_gameover == 1) {
            printer->show_gameover();
            printer->SetColor(GRAY);
            is_gameover = 0;
            while (_kbhit()) (void)_getch();
            system("cls");
            return;
        }

        if (is_gameover == 3) {
            while (_kbhit()) (void)_getch();
            system("cls");
            return;
        }
        if (is_gameover == 4) {
            return;
        }

        printer->gotoxy(77, 23);
        Sleep(15);
        printer->gotoxy(77, 23);
    }
}


int Game::rotate() {
    int old_angle = curr_block->get_angle();
    int new_angle = (old_angle + 1) % 4;

    curr_block->rotate(new_angle);
    if (strike_check() == 0)
    {
        curr_block->rotate(old_angle);
        printer->erase_cur_block(*curr_block);
        curr_block->rotate(new_angle);
        printer->show_cur_block(*curr_block);
        return 0;
    }

    curr_block->rotate(old_angle);
    return 0;
}


int Game::merge_block()
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            total_block[curr_block->get_y() + i][curr_block->get_x() + j] |= curr_block->get_number(i, j);
        }
    }
    int is_clear = check_full_line();
    if (is_clear == 3) {
        return 3;
    }
    printer->show_total_block(total_block, level);
    if (is_clear == 4) {
        return 4;
    }

    return 0;
}

int Game::check_full_line()
{
    int i, j, k;
    for (i = 0; i < 20; i++)
    {
        for (j = 1; j < 13; j++)
        {
            if (total_block[i][j] == 0)
                break;
        }
        if (j == 13)	//한줄이 다 채워졌음
        {

            lines++;
            //줄과 레벨 확인



            if (stages->get_clear_line(level) <= lines) {
                if (level < 10) {
                    lines = 0;
                    level++;
                    init();
                    cleared = true;
                    printer->show_gamestat(level, score, stages->get_clear_line(level) - lines);
                    return 4;
                }
                //만약 레벨이 10이 되는 경우 쇼우 클리어를 진행
                else {
                    //show_clear_screen이라는 것에서 1의 값을 받으면 3을 반환
                    // --> merge_block()에서 이 값에 따른 반환값을 만들도록함
                    //메인 함수에서 is_game_over이 3일때 break함
                    //이때 화면에서 show_logo()가 잘 보이지 않는다는 것을 확인하여 show_logo() 앞 cls를 통해 지우고 다시 그리도록 함.

                    printer->show_total_block(total_block, level);
                    lines = 0;
                    printer->show_gamestat(level, score, stages->get_clear_line(level) - lines);
                    if (printer->show_clear_screen(score)) return 3;
                }
            }

            printer->show_total_block(total_block, level);
            printer->SetColor(BLUE);
            printer->gotoxy(1 * 2 + printer->get_x(), i + printer->get_y());
            for (j = 1; j < 13; j++)
            {
                printf("□");
                Sleep(10);
            }
            printer->gotoxy(1 * 2 + printer->get_x(), i + printer->get_y());
            for (j = 1; j < 13; j++)
            {
                printf("  ");
                Sleep(10);
            }

            for (k = i; k > 0; k--)
            {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[0][j] = 0;
            score += 100 + (level * 10) + (rand() % 10);
            printer->show_gamestat(level, score, stages->get_clear_line(level) - lines);
            i--;
        }

    }


    return 0;
}

void Game::reset_stage() {
    init();
}


// 0: 현재 블럭 저장, 1: 킵했던 블럭 사용
int Game::keep() {
    if (keeped_block != nullptr) {
        Block* temp = curr_block;
        curr_block = keeped_block;
        keeped_block = nullptr;

        delete next_block;
        next_block = temp;

        temp = nullptr;
    }
    else {
        keeped_block = curr_block;
        curr_block = next_block;

        next_block = new Block(stages->get_stick_rate(level));
    }
    printer->show_next_block(*next_block, level);

    if (level == 0 || level == 3 || level == 6) {
        curr_block->start_Reversed();
    }
    else {
        curr_block->start();
    }
    return 0;
}