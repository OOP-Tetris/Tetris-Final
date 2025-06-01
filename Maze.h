#pragma once
#include <vector>
#include "Game.h"

using namespace std;

class Maze : public Game
{
private:
	//int level;		// 레벨별 row수와 각 줄에 나타나는 빈칸 개수 조정
	int rows;		// 총 줄 수
	int spaceNum;	// 한 줄에 나타나는 빈칸 개수
	int clearedRows; // 깨진 미로 줄 수
public:
	Maze();
	void makeMaze(char total_block[21][14]);
	bool isCleared() override;
	void init() override;
	int move_block() override;
	int strike_check() override;
	void block_start(Block* b) override;
    int check_full_line() override;

    //미로 관련 이벤트 처리하는 함수
     void comboEvent();
};


