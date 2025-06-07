#include "Weird.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Stages.h"

Weird::Weird() : Reverse(), Maze(), Mirror() {
}

void Weird::init() {
    Reverse::init();

    makeMaze(total_block);
    printer.show_total_block(total_block, level);
}

int Weird::move_block() {
    int move = Reverse::move_block();
    if ( (lines < (stages.get_clear_line(level) / 2)) && (move == 2) ) {
        Mirror::random_key();
    }
    if (lines >= (stages.get_clear_line(level) / 2)) {
        Mirror::reset_key();
    }
    return move;
}
int Weird::strike_check() {
    return Reverse::strike_check();
}

void Weird::block_start(Block* b) {
    Reverse::block_start(b);
}

bool Weird::isCleared() {
    int checkStart = (rows - clearedRows); // 아직 안 사라진 줄의 시작점

    for (int j = 1; j < 13; j++) {
        if (total_block[checkStart][j] == 0) {
            return false; // 한 칸이라도 비었으면 아직 클리어 아님
        }
    }

    clearedRows++;
    lines++;
    if (clearedRows == rows) {
        cleared = true;
        return true;
    }

    return clearedRows == rows;
}

int Weird::check_full_line()
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
        if (j == 13)	//한줄이 다 채워졌음
        {
            cleared_lines++;

            //줄과 레벨 확인
            if (isCleared()) {
                if (level < 10) {
                    lines = 0;
                    level++;
                    cleared = true;
                    printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);
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
                    printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);
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

            //바뀐 부분 기존의 코드와 완전히 반대로 바꿨습니다 위의 블록을 지우고 아래 블록을 위의 블록으로 한 칸식 올리는
             //방식으로 수정했습니다
            for (k = i; k < 20; k++)
            {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k + 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[19][j] = 0;
            score += 100 + (level * 10) + (rand() % 10);
            printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
            i--;

            //return 5;
        }
    }
    if (cleared_lines > 0)
        return 5;

    return 0;
}

void Weird::draw_ghostBlock() {
    Reverse::draw_ghostBlock();
}

bool Weird::check_collision(Block* b) {
    return Reverse::check_collision(b);
}

void Weird::makeMaze(char total_block[21][14])
{
    rows = stages.get_clear_line(level);
    spaceNum = rows;

    int rowStart = 1;
    for (int i = 0; i < rows; i++) {
        vector<int> spaceIdx;
        for (int j = 1; j < 13; j++) {
            spaceIdx.push_back(j);
            total_block[rowStart + i][j] = 1;
        }
        random_shuffle(spaceIdx.begin(), spaceIdx.end());
        for (int j = 0; j < spaceNum; j++) {
            total_block[rowStart + i][spaceIdx[j]] = 0;
        }
    }
}

int Weird::operate_key(int keytemp) {
    return Mirror::operate_key(keytemp);
}
