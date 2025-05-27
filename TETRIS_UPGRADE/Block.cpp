#include"Block.h"

Block::Block(int shape, int angle, int x, int y, bool combo) : block_shape(shape), block_angle(angle), block_x(x), block_y(y), combo(combo) {}

Block::Block(int stick_rate, bool combo) {
	int shape;
	int i;
	this->combo = combo;

	i = rand() % 100;
	if (i <= stick_rate)		//����� ����Ȯ�� ���
		shape = 0;				//����� ������� ����
	else
		shape = (rand() % 6) + 1;		//shape���� 1~6�� ���� ��
	//�޺��� ��Ȳ���� �ϴ� �̷� ���� ������ ������ ����� ���� ����� ������ �����߰� �̷γ���� �ϼ��Ǹ� ���⿡ ������ ������ �̺�Ʈ�� �߻����Ѿ� �մϴ�
	if (combo) {
		shape = 0;
	}

	block_x = 5;
	block_y = -3;
	block_angle = 0;
	block_shape = shape;
}

int Block::get_x() {
	return block_x;
}

int Block::get_y() {
	return block_y;
}

int Block::get_shape() {
	return block_shape;
}

int Block::get_angle() {
	return block_angle;
}

char (*Block::get_block())[4] {
	return block[block_shape][block_angle];
}

int Block::get_number(int i, int j) {
	return block[block_shape][block_angle][i][j];
}

void Block::rotate(int angle) {
	block_angle = angle;
}

void Block::movetoxy(int x, int y) {
	block_x = x;
	block_y = y;
}

void Block::move_left() {
	block_x--;
}

void Block::move_right() {
	block_x++;
}
void Block::move_down() {
	block_y++;
}

void Block::move_up() {
	block_y--;
}

int Block::start() {
	block_x = 5;
	block_y = -3;
	block_angle = 0;

	return 0;
}

int Block::start_Reversed()
{
	block_x = 5;
	block_y = 23;
	block_angle = 0;

	return 0;
}




char Block::block[7][4][4][4] = {
	//������
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//�׸���
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'��' ���
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'��'���
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'��' ���
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

	//'Z' ���
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' ���
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

};
