#pragma once
#include <vector>
#include "Game.h"

using namespace std;

class Maze : public Game
{
private:
	//int level;		// ������ row���� �� �ٿ� ��Ÿ���� ��ĭ ���� ����
	int rows;		// �� �� ��
	int spaceNum;	// �� �ٿ� ��Ÿ���� ��ĭ ����
	int clearedRows; // ���� �̷� �� ��
public:
	Maze();
	void makeMaze(char total_block[21][14]);
	bool isCleared() const;
	void init() override;
	int move_block() override;
	int strike_check() override;
	void block_start(Block* b) override;

};


