#include "Normal.h"

void Normal::init() {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 14; j++)
            total_block[i][j] = (j == 0 || j == 13) ? 1 : 0;
    for (int j = 0; j < 14; j++) total_block[20][j] = 1;
    lines = 0;
}

void Normal::block_start(Block* b) {
    b->start();
}

int Normal::strike_check() {
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

int Normal::move_block()
{
	printer->erase_cur_block(*curr_block);

	curr_block->move_down();	//블럭을 한칸 아래로 내림
	if (strike_check() == 1)
	{
		//이 내용은 새로 추가된 부분으로 기존에 이 코드가 없었을 때는 블록의 위치가 -3에서 시작하는 경우에 대해서 그 상황에서 방향 조작키를 입력하고 스페이스를 입력하는 경우 갑자기 게임 종료되는 문제가 있어서 코드를 추가했습니다
		if (curr_block->get_y() < 0) {
			return 0;
		}

		curr_block->move_up();
		if (curr_block->get_y() < 0)	//게임오버
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
		next_block = new Block(stages->get_stick_rate(level));
		printer->show_next_block(*next_block, level);
		curr_block->start();
		printer->show_next_block(*next_block, level);
		return 2;
	}
	printer->erase_cur_block(*curr_block);

	return 0;
}

