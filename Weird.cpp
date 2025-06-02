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
    printer->show_total_block(total_block, level);
}

int Weird::move_block() {
    int move = Reverse::move_block();
    if ( (lines < (stages->get_clear_line(level) / 2)) && (move == 2) ) {
        Mirror::random_key();
    }
    if (lines >= (stages->get_clear_line(level) / 2)) {
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
    return Maze::isCleared();
}

int Weird::check_full_line() {
    return Reverse::check_full_line();
}

void Weird::draw_ghostBlock() {
    Reverse::draw_ghostBlock();
}

bool Weird::check_collision(Block* b) {
    return Reverse::check_collision(b);
}

void Weird::makeMaze(char total_block[21][14])
{
    rows = 5;
    spaceNum = 5;

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
