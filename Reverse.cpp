#include "Reverse.h"
#include<iostream>

void Reverse::init() {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 14; j++)
            total_block[i][j] = (j == 0 || j == 13) ? 1 : 0;
    lines = 0;
}

void Reverse::block_start(Block* b) {
    b->start_Reversed();
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
					if (x < 0 || x >= 13 ) {
						return 1;
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
				if (x < 0 || x >= 13 || y < 0 || total_block[y][x] == 1) {
					return 1;
				}
                    
            }
        }
    return 0;

	
}

int Reverse::move_block() {
	printer->erase_cur_block(*curr_block);

	curr_block->move_up();	


	if (strike_check() == 1)
	{	
		curr_block->move_down();
		//블록이 충돌한 경우에 대해서 게임 화면을 벗어나는 지를 확인하는 함수로 게임화면을 벗어나면 true를 반환하며 이 경우 게임 클리어 실패로 판별되어 false가 반환됩니다
		if (check_overflow()) {
			return 1;
		}
		if (curr_block->get_y() >= 20 )	//게임오버 조건 21이 아니라 20이어야 합니다
		{
			Sleep(100);
			return 1;
		}
	

		int is_over = merge_block();

		if (is_over == 3) {
			return 3;
		}

		delete curr_block;
		curr_block = next_block;
		//만약 클리어한 라인의 수가 깨야되는 줄의 반이라면 콤보가 발동해 다음블록은 무조건 일자 블록이 나온다
		if (lines != 0 && stages->get_clear_line(level) / lines == 2) {
			next_block = new Block(stages->get_stick_rate(level), true);
		}
		else {
			next_block = new Block(stages->get_stick_rate(level));
		}
		
		printer->show_next_block(*next_block, level);
		curr_block->start_Reversed();
		printer->show_next_block(*next_block, level);
		return 2;
	
	}
	printer->erase_cur_block(*curr_block);

	return 0;
}
