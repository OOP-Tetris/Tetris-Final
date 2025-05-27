#include "Printer.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

Printer::Printer() : ab_x(5), ab_y(1) {}

int Printer::get_x() {
	return ab_x;
}

int Printer::get_y() {
	return ab_y;
}

//좌표지정 함수
int Printer::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

//색 지정 함수
void Printer::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

void Printer::show_keys() {
	SetColor(GRAY);
	gotoxy(10, 7);
	printf("┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
	Sleep(10);
	gotoxy(10, 8);
	printf("┃ UP   : Rotate Block        ┃");
	Sleep(10);
	gotoxy(10, 9);
	printf("┃ DOWN : Move One-Step Down  ┃");
	Sleep(10);
	gotoxy(10, 10);
	printf("┃ SPACE: Move Bottom Down    ┃");
	Sleep(10);
	gotoxy(10, 11);
	printf("┃ LEFT : Move Left           ┃");
	Sleep(10);
	gotoxy(10, 12);
	printf("┃ RIGHT: Move Right          ┃");
	Sleep(10);
	gotoxy(10, 13);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(10, 3);
	printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
	// 출력 버퍼 비우기
	fflush(stdout);
}


//현재 떨어지고 있는 블럭을 화면에 표시
int Printer::show_cur_block(Block& block)
{
	int i, j;

	switch (block.get_shape())
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + block.get_y()) < 0)
				continue;

			if (block.get_number(j, i) == 1)
			{
				gotoxy((i + block.get_x()) * 2 + ab_x, j + block.get_y() + ab_y);
				printf("■");

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

//블록이 이동하거나 회전할때 블럭을 지우는 함수
int Printer::erase_cur_block(Block& block)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block.get_number(j, i) == 1)
			{
				gotoxy((i + block.get_x()) * 2 + ab_x, j + block.get_y() + ab_y);
				printf("  ");
				//break;

			}
		}
	}
	return 0;
}

//다음에 나올 블럭이 무엇인지 알려주는 창 띄우는 함수
int Printer::show_next_block(Block& block, int level)
{
	int i, j;
	SetColor((level + 1) % 6 + 1);
	for (i = 1; i < 7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j < 8; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 4)
			{
				printf("■");
			}
			else {
				printf("  ");
			}

		}
	}
	block.rotate(0);
	block.movetoxy(15, 1);

	show_cur_block(block);
	return 0;
}

//가장 처음 테트리스 로고와 시작창을 보이게 하는 함수
int Printer::show_logo()
{
	hideCursor();
	system("cls");
	int i = 0, j;
	SetColor(WHITE);
	gotoxy(13, 3);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	Sleep(100);
	gotoxy(13, 4);
	printf("┃ ◆◆◆   ◆◆◆  ◆◆◆    ◆◆     ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 5);
	printf("┃  ◆    ◆     ◆     ◆ ◆    ◆   ◆   ┃");
	Sleep(100);
	gotoxy(13, 6);
	printf("┃  ◆    ◆◆◆   ◆     ◆◆     ◆    ◆  ┃");
	Sleep(100);
	gotoxy(13, 7);
	printf("┃  ◆    ◆     ◆     ◆ ◆    ◆     ◆ ┃");
	Sleep(100);
	gotoxy(13, 8);
	printf("┃  ◆    ◆◆◆   ◆     ◆  ◆   ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 9);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(20, 20);
	printf("Please Press Any Key~!");

	while (true) {
		if (i % 40 == 0)
		{


			for (j = 0; j < 5; j++)
			{
				//여기서 18의 값을 조정해서 첫번째 블럭도 다 지워지도록 조정
				gotoxy(6, 14 + j);
				printf("                                                             ");


			}

			Block* block = new Block(rand() % 7, rand() % 4, 6, 14);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 12, 14);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 19, 14);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 24, 14);
			show_cur_block(*block);
			delete block;
		}
		if (_kbhit())
			break;
		Sleep(30);
		i++;
	}

	while (_kbhit()) (void)_getche();
	system("cls");

	return 0;
}

//이미 바닥에 떨어져서 자리잡은 블럭들을 표시
int Printer::show_total_block(char total_block[21][14], int level) {
	int i, j;
	SetColor(DARK_GRAY);

	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
			{
				SetColor((level % 6) + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);
			if (total_block[i][j] == 1)
			{
				printf("■");
			}
			else {
				printf("  ");
			}

		}
	}

	if (level == 0 || level == 3 || level == 6) {
		SetColor((level % 6) + 1);
		for (j = 0; j < 14; j++) {
			gotoxy((j * 2) + ab_x, ab_y);
			printf("■");
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}




//현재 게임의 진행상태를 보여주는 함수, 앞으로 깨야하는 줄의 수, 점수, 레벨을 보여줌
int Printer::show_gamestat(int level, int score, int lines_left)
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(33, 7);
		printf("STAGE");

		gotoxy(33, 9);
		printf("SCORE");

		gotoxy(33, 12);
		printf("LINES");


	}
	gotoxy(41, 7);
	printf("%10d", level + 1);
	gotoxy(41, 9);
	printf("%10d", score);
	gotoxy(41, 12);
	printf("%10d", lines_left);
	return 0;
}

int Printer::show_clear_screen(int score) {
	SetColor(YELLOW);
	system("cls");
	gotoxy(10, 9);
	printf("             * GAME CLEARED *         ");
	gotoxy(10, 10);
	printf("      축하합니다! 모든 스테이지 완료!   ");
	gotoxy(10, 11);
	printf("          점수: %10d점         ", score);
	gotoxy(10, 14);
	SetColor(GRAY);
	Sleep(1000); // 3초 대기
	system("cls");
	return 1;
}

//게임이 끝났을때 게임 오버창을 띄우는 함수
int Printer::show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(15, 9);
	printf("┃**************************┃");
	gotoxy(15, 10);
	printf("┃*        GAME OVER       *┃");
	gotoxy(15, 11);
	printf("┃**************************┃");
	gotoxy(15, 12);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	fflush(stdin);
	Sleep(1000);

	(void)_getche();
	system("cls");

	return 0;
}
