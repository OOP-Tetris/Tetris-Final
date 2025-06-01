#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Maze::Maze() :Game()
{
	clearedRows = 0;
	srand((unsigned)time(NULL));
}

void Maze::makeMaze(char total_block[21][14])
{

	switch (level)
	{
	case 2:
		rows = 2;
		spaceNum = 2;
		break;
	case 5:
		rows = 3;
		spaceNum = 3;
		break;
	case 8:
		rows = 4;
		spaceNum = 4;
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
    for (int j = 1; j < 13; j++) {
        total_block[checkStart][j] = 0;
    }

    for (int i = checkStart; i > 0; i--) {
        for (int j = 1; j < 13; j++) {
            total_block[i][j] = total_block[i - 1][j];
        }
    }
    for (int j = 1; j < 13; j++) {
        total_block[0][j] = 0;
    }

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
    for (int i = 0; i < 13; i++) {
       total_block[19][i] = 1;
    }

    printer->show_total_block(total_block, level);
    Sleep(100);
}
void Maze::init() {
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 14; j++)
			total_block[i][j] = (j == 0 || j == 13) ? 1 : 0;
	for (int j = 0; j < 14; j++) total_block[20][j] = 1;

	makeMaze(total_block);  // º¯°æµÈ ÇÔ¼ö È£Ãâ
	printer->show_total_block(total_block, level);

	lines = 0;
	cleared = false;
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
                if (level < 10) {
                    lines = 0;
                    level++;
                    init();
                    cleared = true;
                    printer->show_gamestat(level, score, stages->get_clear_line(level) - clearedRows);
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
                    printer->show_gamestat(level, score, stages->get_clear_line(level) - clearedRows);
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
            printer->show_gamestat(level, score, stages->get_clear_line(level) - clearedRows);

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
	printer->erase_cur_block(*curr_block);

	curr_block->move_down();	//ºí·°À» ÇÑÄ­ ¾Æ·¡·Î ³»¸²
	if (strike_check() == 1)
	{
		//ÀÌ ³»¿ëÀº »õ·Î Ãß°¡µÈ ºÎºÐÀ¸·Î ±âÁ¸¿¡ ÀÌ ÄÚµå°¡ ¾ø¾úÀ» ¶§´Â ºí·ÏÀÇ À§Ä¡°¡ -3¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì¿¡ ´ëÇØ¼­ ±× »óÈ²¿¡¼­ ¹æÇâ Á¶ÀÛÅ°¸¦ ÀÔ·ÂÇÏ°í ½ºÆäÀÌ½º¸¦ ÀÔ·ÂÇÏ´Â °æ¿ì °©ÀÚ±â °ÔÀÓ Á¾·áµÇ´Â ¹®Á¦°¡ ÀÖ¾î¼­ ÄÚµå¸¦ Ãß°¡Çß½À´Ï´Ù
		if (curr_block->get_y() < 0) {
			return 0;
		}

		curr_block->move_up();
		if (curr_block->get_y() < 0)	//°ÔÀÓ¿À¹ö
		{

			//printer->SetColor(3);
			//printf("%d %d \n", curr_block->get_x(), curr_block->get_y());
			//system("pause");

			printer->SetColor(DARK_GRAY);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (curr_block->get_number(i, j) == 1) {
						int dx = curr_block->get_x() + j;
						int dy = curr_block->get_y() + i;
						if (dx >= 0 && dx <= 14 && dy >= 0 && dy < 20) {
							printer->gotoxy(dx * 2 + printer->get_x(), dy + printer->get_y());
							printf("■");
						}
					}
				}
			}
			Sleep(100);


			return 1;
		}
        //새로 추가된 내용 지금 스테이지 목표 줄의 절반이 깨지는 경우에는 가장 아래에 있는 줄 한개를 삭제시킨다
        if (lines != 0 && stages->get_clear_line(level) / lines == 2) {
        comboEvent();
        printer->show_combo();
        printer->show_total_block(total_block, level);
        printer->show_gamestat(level, score, stages->get_clear_line(level) - lines);
    }
		int is_over = merge_block();

		if (is_over == 3) {
			return 3;
		}
        if (is_over == 4) {
            return 4;
        }

		delete curr_block;
		curr_block = next_block;
		//¸¸¾à Å¬¸®¾îÇÑ ¶óÀÎÀÇ ¼ö°¡ ±ú¾ßµÇ´Â ÁÙÀÇ ¹ÝÀÌ¶ó¸é ÄÞº¸°¡ ¹ßµ¿ÇØ ´ÙÀ½ºí·ÏÀº ¹«Á¶°Ç ÀÏÀÚ ºí·ÏÀÌ ³ª¿Â´Ù

		if (is_over == 4) {
			return 4;
		}
	
		next_block = new Block(stages->get_stick_rate(level));    
		printer->show_next_block(*next_block, level);
		curr_block->start();
		printer->show_next_block(*next_block, level);
		return 2;
	}
	printer->erase_cur_block(*curr_block);

	return 0;
}

