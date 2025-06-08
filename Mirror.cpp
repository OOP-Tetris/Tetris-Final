#include "Mirror.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Mirror::Mirror(): Normal() {
    srand(unsigned(time(0))); // Seed for random number generation
    up = KEY_UP;
    down = KEY_DOWN;
    left = KEY_LEFT;
    right = KEY_RIGHT;
}

Mirror::Mirror(int score) : Game(score) {       // Normal(score) doesn't work
    srand(unsigned(time(0))); // Seed for random number generation
    up = KEY_UP;
    down = KEY_DOWN;
    left = KEY_LEFT;
    right = KEY_RIGHT;
}

Mirror::~Mirror() {
    // Destructor implementation if needed
}

int Mirror::operate_key(int keytemp) {
    if (keytemp == EXT_KEY) {
        keytemp = _getche();

        if (keytemp == up) {
            rotate();
            draw_ghostBlock();
        }

        if (keytemp == left) {
            if (curr_block->get_x() > 1) {
                printer.erase_cur_block(*curr_block);
                curr_block->move_left();
                if (strike_check()) curr_block->move_right();
                printer.show_cur_block(*curr_block);
                draw_ghostBlock();
            }
        }

        if (keytemp == right) {
            if (curr_block->get_x() < 14) {
                printer.erase_cur_block(*curr_block);
                curr_block->move_right();
                if (strike_check()) curr_block->move_left();
                printer.show_cur_block(*curr_block);
                draw_ghostBlock();
            }
        }

        if (keytemp == down) {
            is_gameover = move_block();
            if (is_gameover != 1 && is_gameover != 3)
                printer.show_cur_block(*curr_block);
            draw_ghostBlock();
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

int Mirror::random_key() {
    int keys[4] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

    // Fisher-Yates shuffle
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = keys[i];
        keys[i] = keys[j];
        keys[j] = temp;
    }

    up = keys[0];
    down = keys[1];
    left = keys[2];
    right = keys[3];

    return 0;
}

void Mirror::reset_key() {
    up = KEY_UP;
    down = KEY_DOWN;
    left = KEY_LEFT;
    right = KEY_RIGHT;
}

int Mirror::move_block()
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

			printer.SetColor(DARK_GRAY);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (curr_block->get_number(i, j) == 1) {
						int dx = curr_block->get_x() + j;
						int dy = curr_block->get_y() + i;
						if (dx >= 0 && dx <= 14 && dy >= 0 && dy < 20) {
							printer.gotoxy(dx * 2 + printer.get_x(), dy + printer.get_y());
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
        random_key();
		if (lines != 0 && stages.get_clear_line(level) / lines == 2) {
            next_block = new Block(stages.get_stick_rate(level), true);
            if (check_FirstComb) {
                printer.show_combo();
                printer.show_total_block(total_block, level);
                printer.show_gamestat(level, score, stages.get_clear_line(level) - lines);
                if (keeped_block != nullptr) {
                    printer.show_keeped_block(*keeped_block, level);
                }
                check_FirstComb = false;
            }

        }else {
            check_FirstComb = true;
            next_block = new Block(stages.get_stick_rate(level));
        }
		
		printer.show_next_block(*next_block, level);
		curr_block->start();
		printer.show_next_block(*next_block, level);
		return 2;
	}
	printer.erase_cur_block(*curr_block);

	return 0;
}

bool Mirror::isCleared()
{
    if (stages.get_clear_line(level) <= lines) return true;
    else return false;
}
