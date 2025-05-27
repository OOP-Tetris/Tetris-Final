#include "Reverse.h"


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
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (curr_block->get_number(i, j) == 1) {
                int x = curr_block->get_x() + j;
                int y = curr_block->get_y() + i;
                if (x < 0 || x >= 14 || y < 0 || y >= 21 || total_block[y][x])
                    return 1;
            }
        }
    return 0;
}

int Reverse::move_block() {
    printer->erase_cur_block(*curr_block);
    curr_block->move_up();
    if (strike_check()) {
        curr_block->move_down();
        if (curr_block->get_y() > 20) return 1;
        merge_block();
        curr_block = next_block;
        next_block = new Block(stages->get_stick_rate(level));
        block_start(curr_block);
        printer->show_next_block(*next_block, level);
    }
    printer->show_cur_block(*curr_block);
    return 0;
}