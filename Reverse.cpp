#include "Reverse.h"
#include<iostream>

Reverse::Reverse()
{
    //난수를 발생 시킴
    srand(unsigned(time(0)));
}

Reverse::Reverse(int score) : Game(score) {
    //난수를 발생 시킴
    srand(unsigned(time(0)));
}

void Reverse::init() {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 14; j++)
            total_block[i][j] = (j == 0 || j == 13) ? 1 : 0;
    lines = 0;
}

void Reverse::block_start(Block* b) {
    b->start_Reversed();
}

bool Reverse::isCleared()
{
    return cleared;
}

//충돌이 일어났을 때 병합되는 과정에서 블록 중 일부가 게임판 바깥을 벗어났는 지 확인 이 프로그램에서는 이 함수 호출 시에는 늘 충돌이 발생했을 때 호출된다는 점 아시고 보면 이해가 더 빠릅니다
bool Reverse::check_overflow()
{
	
	bool detOverFlow = false;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (curr_block->get_number(i, j) == 1) {
				int x = curr_block->get_x() + j;
				int y = curr_block->get_y() + i;
				//충돌 발생한 블록의 일부가 게임 화면의 영역을 벗어나면 게임 종료조건을 충족하기 때문에 true를 반환합니다
				if (y >= 20) {
					return true;
				}
			}
		}
	//아니면 false반환
	return false;
}

int Reverse::check_full_line()
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



            if (stages.get_clear_line(level) <= lines) {
                if (level < 10) {
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
            
           //바뀐 부분 기존의 코드와 완전히 반대로 바꿨습니다 위의 블록을 지우고 아래 블록을 위의 블록으로 한 칸식 올리는
            //방식으로 수정했습니다
            for (k = i; k < 20; k++)
            {
                for (j = 1; j < 13; j++)
                    total_block[k ][j] = total_block[k + 1 ][j];
            }
            for (j = 1; j < 13; j++)
                total_block[19][j] = 0;
            score += 100 + (level * 10) + (rand() % 10);
            printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
            i--;

            //return 5;
        }

    }
    return 0;
}

void Reverse::draw_ghostBlock()
{
    if (prev_ghostBlock != nullptr) {
        printer.erase_ghostBlock(*prev_ghostBlock, total_block);
        delete prev_ghostBlock;
        prev_ghostBlock = nullptr;
    }

    Block* ghostBlock = new Block(*curr_block);

    // 맵 안쪽까지만 고스트 위치를 이동시켜서 유효한 위치 찾기
    while (true) {
        ghostBlock->move_up();

        int gy = ghostBlock->get_y();

        if (check_collision(ghostBlock)) {
            ghostBlock->move_down(); // 마지막 유효 위치
            break;
        }

        if (gy <= 0) {
            ghostBlock->move_down();
            break;
        }
    }

    // 맵에 올라오기 전이라면 고스트 출력하지 않음 (즉, 아래에서 대기 중일 때는 안 보임)
    if (ghostBlock->get_y() >= 20) {
        delete ghostBlock;
        prev_ghostBlock = nullptr;
        return;
    }

    printer.show_ghostBlock(*ghostBlock);
    prev_ghostBlock = ghostBlock;
}


bool Reverse::check_collision(Block* b)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b->get_number(i, j)) {
                int x = b->get_x() + j;
                int y = b->get_y() + i;

                if (x < 0 || x >= 14 || y < 0 || y >= 21)
                    return true;

                if (total_block[y][x] == 1)
                    return true;
            }
        }
    }
    return false;
}

int Reverse::strike_check() {

	//바닥 도달 시 1반환
    if (curr_block->get_y() <= 0) {

        return 1;
    }

	//추가된 조건들 21이상이면 계속 내려오게 충돌 설정을 피합니다
	if (curr_block->get_y() >= 21) {

		//조건 추가 좌우 장벽에 충돌하는 경우에 대한 예외처리를 위해 이중 for문을 이용해 현재 블록이 위치한 좌표가 좌우 경계를 넘어가면
		//1을 반환하게 바꿨습니다
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (curr_block->get_number(i, j) == 1) {
					int x = curr_block->get_x() + j;
					int y = curr_block->get_y() + i;
                    //변경된 내용 충돌의 종류를 구분함 다른 블록이랑 닫는 게 아니라 좌우 경계 충돌 시에는 2를 반환하고 그 경우에는 게임종료를 시키지 않는 방식으로 코드를 개선함
                    if (x < 0 || x >= 13 ) {
						return 2;
					}
				}
			}
		//좌우 충돌하지 않는 경우에 대해서는 0반환
		return 0;
	}

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (curr_block->get_number(i, j) == 1) {
                int x = curr_block->get_x() + j;
                int y = curr_block->get_y() + i;
                //추가된 내용 이 내용이 없으면 y가 21 이상인 경우 아래 if조건문이 참이 되는 희한한 상황이 생겨서 추가함
                if(y >= 21){continue;}
				if (x < 0 || x >= 13 || y < 0 || total_block[y][x] == 1) {
					return 1;
				}
                    
            }
        }
    return 0;

	
}

int Reverse::move_block() {
	printer.erase_cur_block(*curr_block);

	curr_block->move_up();

    //새로 선언된 변수 y좌표가 21이상일 때 다른 블록과 충돌이 아니라 좌우 경계와의 충돌인 경우에 대해서는 false를 가진다 나머지 경우 true값을 가진다
    bool detOverflow = true;

	if (strike_check() == 1 || strike_check() == 2)
	{
        //다른 블록과 충돌이 아닌 좌우 경계와의 충돌인 경우 false로 값 변환
        if (strike_check() == 2) {
            detOverflow = false;
        }


		curr_block->move_down();
		//블록이 충돌한 경우에 대해서 게임 화면을 벗어나는 지를 확인하는 함수로 게임화면을 벗어나면 true를 반환하며 이 경우 게임 클리어 실패로 판별되어 false가 반환됩니다
        //추가된 내용으로 블록이 모든 블록을 나타내는 경계에 들어가기 전 좌우 충돌하는 경우에는 게임 종료를 시키지 않기 위해 strike함수의 반환값을 조정했고 이를 통해서 detOverflow값을 변경해서 게임 종료 여부를 변경하게 했습니다
		if (check_overflow() && detOverflow) {
            Sleep(100);
            return 1;
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
		//만약 클리어한 라인의 수가 깨야되는 줄의 반이라면 콤보가 발동해 다음블록은 무조건 일자 블록이 나온다
		if (lines != 0 && stages.get_clear_line(level) / lines == 2) {
        next_block = new Block(stages.get_stick_rate(level), true);
            if (check_FirstComb) {
                printer.show_combo();
                printer.show_keeped_block(*keeped_block, level);
                printer.show_total_block(total_block, level);
                printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
                check_FirstComb = false;
            }
        }
        else {
            check_FirstComb = true;
            next_block = new Block(stages.get_stick_rate(level));
        }
		
		printer.show_next_block(*next_block, level);
		curr_block->start_Reversed();
        draw_ghostBlock();
		printer.show_next_block(*next_block, level);
		return 2;
	
	}
	printer.erase_cur_block(*curr_block);

	return 0;
}
