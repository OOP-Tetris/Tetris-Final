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

int Reverse::strike_check() {

	//�߰��� ���ǵ� 21�̻��̸� ��� �������� �浹 ������ ���մϴ�
	if (curr_block->get_y() >= 21) {
		return 0;
	}

	if (curr_block->get_y() <= 0) {
		return 1;
	}


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (curr_block->get_number(i, j) == 1) {
				int x = curr_block->get_x() + j;
				int y = curr_block->get_y() + i;
				if (x < 0 || x >= 14 || y < 0 || total_block[y][x] == 1) {
					return 1;
				}

			}
		}
	return 0;


}

int Reverse::move_block() {
	//���� �ڵ� ��ſ� ���ο� �ڵ带 �ۼ��߽��ϴ�
  /*  printer->erase_cur_block(*curr_block);
	curr_block->move_up();
	if (strike_check() == 1) {


		curr_block->move_down();
		if (curr_block->get_y() > 20) return 1;
		merge_block();
		curr_block = next_block;
		next_block = new Block(stages->get_stick_rate(level));
		block_start(curr_block);
		printer->show_next_block(*next_block, level);
	}
	printer->show_cur_block(*curr_block);
	return 0;*/

	printer->erase_cur_block(*curr_block);

	curr_block->move_up();

	if (strike_check() == 1)
	{
		curr_block->move_down();

		if (curr_block->get_y() >= 20)	//���ӿ��� ���� 21�� �ƴ϶� 20�̾�� �մϴ�
		{

			printer->SetColor(3);
			/*printf("%d %d \n", curr_block->get_x(), curr_block->get_y());
			system("pause");*/

			printer->SetColor(DARK_GRAY);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (curr_block->get_number(i, j) == 1) {
						int dx = curr_block->get_x() - j;
						int dy = curr_block->get_y() - i;
						if (dx >= 0 && dx <= 14 && dy >= 0 && dy < 20) {
							printer->gotoxy(dx * 2 + printer->get_x(), dy + printer->get_y());
							printf("��");
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
		if (is_over == 4) {
			return 4;
		}
		//���� Ŭ������ ������ ���� ���ߵǴ� ���� ���̶�� �޺��� �ߵ��� ��������� ������ ���� ����� ���´�
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