#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Maze::Maze() :Game()
{
    clearedRows = 0;
    srand((unsigned)time(NULL));
}

Maze::Maze(int score) : Game(score)
{
    clearedRows = 0;
    srand((unsigned)time(NULL));
}

void Maze::makeMaze(char total_block[21][14])
{
    rows = stages.get_clear_line(level); // 레벨에 따라 줄 수 설정

    switch (level)
    {
    case 2:
        spaceNum = 2;
        break;
    case 5:
        spaceNum = 3;
        break;
    case 8:
        spaceNum = 4;
        break;
    case 9:
        spaceNum = 5;
        break;
    default:
        rows = 0;
        spaceNum = 0;
        break;
    }


    int rowStart = 20 - rows;
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

bool Maze::isCleared() {
    int checkStart = 20 - (rows - clearedRows); // 아직 안 사라진 줄의 시작점

    // 가장 아래 한 줄만 검사
    for (int j = 1; j < 13; j++) {
        if (total_block[checkStart][j] == 0) {
            return false; // 한 칸이라도 비었으면 아직 클리어 아님
        }
    }

    // 꽉 찼으면 줄 없애고 clearedRows 증가
    /*for (int j = 1; j < 13; j++) {
        total_block[checkStart][j] = 0;
    }

    for (int i = checkStart; i > 0; i--) {
        for (int j = 1; j < 13; j++) {
            total_block[i][j] = total_block[i - 1][j];
        }
    }
    for (int j = 1; j < 13; j++) {
        total_block[0][j] = 0;
    }*/ //중복호출

    clearedRows++;
    if (clearedRows == rows) {
        cleared = true;
        return true;
    }

    return clearedRows == rows;
}

void Maze::comboEvent()
{
      lines++;
  printer.show_combo();
  Sleep(300);

  
  printer.show_total_block(total_block, level);
  printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);
  if (keeped_block != nullptr) {
      printer.show_keeped_block(*keeped_block, level);
  }

  //// 맨 아래 줄 채우기
  for (int j = 1; j < 13; j++)
      total_block[19 ][j] = 1;
  check_full_line();
  clearedRows++; // 목표 줄 수도 1줄 줄임!
   

  //  printer.SetColor(BLUE);
  // printer.gotoxy(1 * 2 + printer.get_x(), 19 + printer.get_y());
  // for (int j = 1; j < 13; j++)
  // {
  //     printf("□");
  //     Sleep(10);
  // }
  // printer.gotoxy(1 * 2 + printer.get_x(), 19 + printer.get_y());
  // for (int j = 1; j < 13; j++)
  // {
  //     printf("  ");
  //    Sleep(10);
  // }

  // // 맨 아래 줄 제거
  // for (int j = 1; j < 13; j++)
  //     total_block[19][j] = 0;

  // // 전체 블록 아래로 내림
  // for (int i = 19; i > 0; i--)
  //     for (int j = 1; j < 13; j++)
  //         total_block[i][j] = total_block[i - 1][j];

  // for (int j = 1; j < 13; j++)
  //    total_block[0][j] = 0;

  // clearedRows++; // 목표 줄 수도 1줄 줄임!

  //

  printer.show_total_block(total_block, level);
  printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);
}

void Maze::init() {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 14; j++)
            total_block[i][j] = (j == 0 || j == 13) ? 1 : 0;
    for (int j = 0; j < 14; j++) total_block[20][j] = 1;

    makeMaze(total_block); 
    printer.show_total_block(total_block, level);

    lines = 0;
    cleared = false;
    //comboUsed = false;
}

void Maze::block_start(Block* b) {
    b->start();
}

int Maze::check_full_line()
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

            for (k = i; k > 0; k--)
            {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[0][j] = 0;

            score += 100 + (level * 10) + (rand() % 10);
            printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);

            i--; // 같은 줄을 다시 검사
        }
    }

    if (cleared_lines > 0)
        return 5;

    return 0;
}


int Maze::strike_check() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (curr_block->get_number(i, j) == 1) {
                int x = curr_block->get_x() + j;
                int y = curr_block->get_y() + i;
                if (x < 0 || x >= 14 || y >= 21 || total_block[y][x])
                    return 1;
            }
        }
    return 0;
}



int Maze::move_block()
{
    printer.erase_cur_block(*curr_block);

    curr_block->move_down();
    if (strike_check() == 1)
    {
        if (curr_block->get_y() < 0) {
            return 0;
        }

        curr_block->move_up();
        if (curr_block->get_y() < 0) 
        {

            //printer.SetColor(3);
            //printf("%d %d \n", curr_block->get_x(), curr_block->get_y());
            //system("pause");

            printer.SetColor(DARK_GRAY);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (curr_block->get_number(i, j) == 1) {
                        int dx = curr_block->get_x() + j;
                        int dy = curr_block->get_y() + i;
                        if (dx >= 0 && dx <= 14 && dy >= 0 && dy < 20) {
                            printer.gotoxy(dx * 2 + printer.get_x(), dy + printer.get_y());
                            printf("■");
                        }
                    }
                }
            }
            Sleep(100);


            return 1;
        }
        //블록 병합을 먼저 진행한 후에 그 다음에 클리어가 되지 않았으면 (isCleared함수값이 거짓이면) 그 때서야 콤보 이벤트를 발생시킨다
        int is_over = merge_block();

        //새로 추가된 내용 지금 스테이지 목표 줄의 절반이 깨지는 경우에는 가장 아래에 있는 줄 한개를 삭제시킨다
        if (clearedRows * 2 == rows) {
            comboEvent();
            //comboUsed = true;

            if (check_FirstComb) {
                //printer.show_combo();
                //printer.show_total_block(total_block, level);
                //printer.show_gamestat(level, score, stages.get_clear_line(level) - clearedRows);
                if (keeped_block != nullptr) {
                    printer.show_keeped_block(*keeped_block, level);
                }
                check_FirstComb = false;
            }
            else {
                check_FirstComb = true;
            }

        }

        if (rows <= clearedRows) {
            if (level < 10) {
                lines = 0;
                level++;
                init();
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


        if (is_over == 3) {
            return 3;
        }
        if (is_over == 4) {
            return 4;
        }

        delete curr_block;
        curr_block = next_block;

        if (is_over == 4) {
            return 4;
        }

        next_block = new Block(stages.get_stick_rate(level));
        printer.show_next_block(*next_block, level);
        curr_block->start();
        printer.show_next_block(*next_block, level);
        return 2;
    }
    printer.erase_cur_block(*curr_block);

    return 0;
}
