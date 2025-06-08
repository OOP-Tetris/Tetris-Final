#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

Game::Game() {
    score = 0;
    lines = 0;
    level = 0;
    is_gameover = 0;
    cleared = false;
}

Game::Game(int score) : score(score), lines(0), level(0), is_gameover(0), cleared(false) {}

Game::~Game() {
    if(curr_block != nullptr)
    delete curr_block;

  delete keeped_block;
  if (prev_ghostBlock != nullptr)
      delete prev_ghostBlock;
}

void Game::run() {
    lines = 0;
    if (is_gameover == 3) {
        printer.show_logo();
    }
    is_gameover = 0;
    cleared = false;

    init();

    curr_block = new Block(stages.get_stick_rate(level));
    next_block = new Block(stages.get_stick_rate(level));
    block_start(curr_block);

    printer.show_next_block(*next_block, level);
    printer.show_total_block(total_block, level);
    printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
    printer.show_cur_block(*curr_block);

    draw_ghostBlock();
    play_loop();

    if (is_gameover == 3) {
        printer.show_logo();
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
        //printer.gotoxy(50, 1);
        if (_kbhit()) {
            keytemp = _getch();
            operate_key(keytemp);
        }

        if (i % stages.get_speed(level) == 0) {
            is_gameover = move_block();
            draw_ghostBlock();
            if (is_gameover != 1 && is_gameover != 3)
                printer.show_cur_block(*curr_block);
        }

        if (is_gameover == 1) {
            printer.show_gameover();
            printer.SetColor(GRAY);
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

        printer.gotoxy(77, 23);
        Sleep(15);
        printer.gotoxy(77, 23);
    }
}

int Game::operate_key(int keytemp) {
    if (keytemp == EXT_KEY) {
        keytemp = _getch();
        switch (keytemp) {
            case KEY_UP:
                rotate();
                draw_ghostBlock();
                break;
            case KEY_LEFT:
                if (curr_block->get_x() > 1) {
                    printer.erase_cur_block(*curr_block);
                    curr_block->move_left();
                    if (strike_check()) curr_block->move_right();
                    printer.show_cur_block(*curr_block);
                    draw_ghostBlock();
                }
                break;
            case KEY_RIGHT:
                if (curr_block->get_x() < 14) {
                    printer.erase_cur_block(*curr_block);
                    curr_block->move_right();
                    if (strike_check()) curr_block->move_left();
                    printer.show_cur_block(*curr_block);
                    draw_ghostBlock();
                }
                break;
            case KEY_DOWN:
                is_gameover = move_block();
                if (is_gameover != 1 && is_gameover != 3)
                    printer.show_cur_block(*curr_block);
                draw_ghostBlock();
                break;
        }
    }
    else {
        while (_kbhit()) (void)_getch();
    }

    if (keytemp == KEEP) {
        keep();
        return 0;
    }
    
    if (keytemp == 32) {
        while (is_gameover == 0) {
            is_gameover = move_block();
        }
        printer.show_cur_block(*curr_block);
        while (_kbhit()) (void)_getch();
    }

    return 0;
}

int Game::rotate() {
    int old_angle = curr_block->get_angle();
    int new_angle = (old_angle + 1) % 4;

    curr_block->rotate(new_angle);
    if (strike_check() == 0)
    {
        curr_block->rotate(old_angle);
        printer.erase_cur_block(*curr_block);
        curr_block->rotate(new_angle);
        printer.show_cur_block(*curr_block);
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
    printer.show_total_block(total_block, level);
    if (is_clear == 4) {
        return 4;
    }
    if (is_clear == 5) {
        return 5;
    }

    return 0;
}

int Game::check_full_line()
{
    int i, j, k;
    int cleared_lines = 0;

    for (i = 0; i < 20; i++)
    {
        for (j = 1; j < 13; j++)
        {
            if (total_block[i][j] == 0)
                break;
        }
        if (j == 13)   //한줄이 다 채워졌음
        {
            lines++;
            cleared_lines++;

            //줄과 레벨 확인
            if (isCleared()) {
                if (level < 9) {
                    lines = 0;
                    level++;
                    init();
                    cleared = true;
                    printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
                    return 4;
                }
                //만약 레벨이 10이 되는 경우 쇼우 클리어를 진행
                else {
                    //show_clear_screen이라는 것에서 1의 값을 받으면 3을 반환
                    // --> merge_block()에서 이 값에 따른 반환값을 만들도록함
                    //메인 함수에서 is_game_over이 3일때 break함
                    //이때 화면에서 show_logo()가 잘 보이지 않는다는 것을 확인하여 show_logo() 앞 cls를 통해 지우고 다시 그리도록 함.

                    printer.show_total_block(total_block, level);
                    lines = 0;
                    printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
                    if (printer.show_clear_screen(score)) return 3;
                }
            }

            printer.show_total_block(total_block, level);
            printer.SetColor(BLUE);
            printer.gotoxy(1 * 2 + printer.get_x(), i + printer.get_y());
            for (j = 1; j < 13; j++)
            {
                printf("□");
                Sleep(10);
            }
            printer.gotoxy(1 * 2 + printer.get_x(), i + printer.get_y());
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
            printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);

            i--; // 같은 줄을 다시 검사
        }
    }

    if (cleared_lines > 0)
        return 5;

    return 0;
}



void Game::reset_stage() {
    init();
}

// 0: 현재 블럭 저장, 1: 킵했던 블럭 사용
int Game::keep() {
    printer.erase_cur_block(*curr_block);

    if (keeped_block != nullptr) {
        Block* temp = curr_block;
        curr_block = keeped_block;
        printer.erase_cur_block(*keeped_block);
        keeped_block = nullptr;

        delete next_block;
        next_block = temp;

        temp = nullptr;
    }
    else {
        keeped_block = curr_block;
        curr_block = next_block;

        next_block = new Block(stages.get_stick_rate(level));

        printer.show_keeped_block(*keeped_block, level);
    }

    printer.show_next_block(*next_block, level);

    if (level == 0 || level == 3 || level == 6) {
        curr_block->start_Reversed();
    }
    else {
        curr_block->start();
    }

    block_start(curr_block);

    return 0;
}

void Game::draw_ghostBlock()
{
    if (prev_ghostBlock != nullptr) {
        printer.erase_ghostBlock(*prev_ghostBlock, total_block);
        delete prev_ghostBlock;
        prev_ghostBlock = nullptr;
    }

    Block* ghostBlock = new Block(*curr_block);
    while (true) {
        ghostBlock->move_down();
        if (check_collision(ghostBlock)) {
            ghostBlock->move_up();
            break;
        }
    }

    printer.show_ghostBlock(*ghostBlock);
    prev_ghostBlock = ghostBlock;
}



bool Game::check_collision(Block* b)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (b->get_number(i, j) == 1) {
                int x = b->get_x() + j;
                int y = b->get_y() + i;
                if (x < 0 || x >= 14 || y >= 21 || total_block[y][x])
                    return true;
            }
        }
    return false;
}
