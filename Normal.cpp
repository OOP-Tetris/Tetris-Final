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

bool Normal::isCleared()
{
    if (stages->get_clear_line(level) <= lines) return true;
    else return false;
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
							printf("¡á");
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

        if (is_over == 4) {
            return 4;
        }

		delete curr_block;
		curr_block = next_block;
		//¸¸¾à Å¬¸®¾îÇÑ ¶óÀÎÀÇ ¼ö°¡ ±ú¾ßµÇ´Â ÁÙÀÇ ¹ÝÀÌ¶ó¸é ÄÞº¸°¡ ¹ßµ¿ÇØ ´ÙÀ½ºí·ÏÀº ¹«Á¶°Ç ÀÏÀÚ ºí·ÏÀÌ ³ª¿Â´Ù
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
