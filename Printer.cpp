#include "Printer.h"
#include "iostream"
#define _CRT_SECURE_NO_WARNINGS

Printer::Printer(): ab_x(5), ab_y(1) {}

int Printer::get_x() {
	return ab_x;
}

int Printer::get_y() {
	return ab_y;
}

//좌표지정 함수
int Printer::gotoxy(int x,int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

//색 지정 함수
void Printer::SetColor(int color) 
{ 
	static HANDLE std_output_handle=GetStdHandle(STD_OUTPUT_HANDLE);
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
        printf("┃ K    : Keep Block          ┃");
        Sleep(10);
        gotoxy(10, 14);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
		gotoxy(10, 3);
		printf("Select Start level[1-10]:       \b\b\b\b\b\b\b");
		// 출력 버퍼 비우기
		fflush(stdout);
}


//현재 떨어지고 있는 블럭을 화면에 표시
int Printer::show_cur_block(Block& block)
{
	int i,j;
	
	switch(block.get_shape())
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

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if( (j + block.get_y()) <0)
				continue;

			if(block.get_number(j, i) == 1)
			{
				gotoxy((i + block.get_x())*2 + ab_x, j + block.get_y() + ab_y);
				printf("■");

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77,23);
	return 0;
}

//블록이 이동하거나 회전할때 블럭을 지우는 함수
int Printer::erase_cur_block(Block& block)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(block.get_number(j, i) == 1)
			{
				gotoxy((i+block.get_x())*2+ab_x,j+block.get_y()+ab_y);
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
	int i,j;
	SetColor((level+1)%6+1);
	for(i=1;i<7;i++)
	{
		gotoxy(33,i);
		for(j=0;j<8;j++)
		{
			if(i==1 || i==6 || j==0 || j==4)
			{
				printf("■");				
			}else{
				printf("  ");
			}

		}
	}
    block.rotate(0);
    block.movetoxy(15, 1);

	show_cur_block(block);
	return 0;
}

int Printer::show_keeped_block(Block& block, int level)
{
    int i, j;
    SetColor((level%6)+1);
    for (i = 1; i < 7; i++)
    {
        gotoxy(47, i);
        for (j = 0; j < 8; j++)
        {
            if (i == 1 || i == 6 || j == 0 || j == 4)
            {
                printf("■");
            }
            else printf("  ");
        }
    }

    block.rotate(0);
    block.movetoxy(22, 1);

    show_cur_block(block);

    return 0;
}

//가장 처음 테트리스 로고와 시작창을 보이게 하는 함수
int Printer::show_logo()
{
	hideCursor();
	system("cls");
	int i=0,j;
	SetColor(WHITE);
	gotoxy(42,3);
	/*printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	Sleep(100);
	gotoxy(13,4);
	printf("┃ ◆◆◆   ◆◆◆  ◆◆◆    ◆◆     ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13,5);
	printf("┃  ◆    ◆     ◆     ◆ ◆    ◆   ◆   ┃");
	Sleep(100);
	gotoxy(13,6);
	printf("┃  ◆    ◆◆◆   ◆     ◆◆     ◆    ◆  ┃");
	Sleep(100);
	gotoxy(13,7);
	printf("┃  ◆    ◆     ◆     ◆ ◆    ◆     ◆ ┃");
	Sleep(100);
	gotoxy(13,8);
	printf("┃  ◆    ◆◆◆   ◆     ◆  ◆   ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13,9);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(20,20);
	printf("Please Press Any Key~!");*/
    printf("██╗    ██╗███████╗██╗██████╗ ██████╗");
    Sleep(100);
    gotoxy(42, 4);
    printf("██║    ██║██╔════╝██║██╔══██╗██╔══██╗");
    Sleep(100);
    gotoxy(42, 5);
    printf("██║ █╗ ██║█████╗  ██║██████╔╝██║  ██║");
    Sleep(100);
    gotoxy(42, 6);
    printf("██║███╗██║██╔══╝  ██║██╔══██╗██║  ██║");
    Sleep(100);
    gotoxy(42, 7);
    printf("╚███╔███╔╝███████╗██║██║  ██║██████╔╝");
    Sleep(100);
    gotoxy(42, 8);
    printf(" ╚══╝╚══╝ ╚══════╝╚═╝╚═╝  ╚═╝╚═════╝");
    Sleep(100);

    gotoxy(22, 10);
    printf("██████╗ ██╗      ██████╗  ██████╗██╗  ██╗    ██╗      █████╗ ███╗   ██╗██████╗");
    Sleep(100);
    gotoxy(22, 11);
    printf("██╔══██╗██║     ██╔═══██╗██╔════╝██║ ██╔╝    ██║     ██╔══██╗████╗  ██║██╔══██╗");
    Sleep(100);
    gotoxy(22, 12);
    printf("██████╔╝██║     ██║   ██║██║     █████╔╝     ██║     ███████║██╔██╗ ██║██║  ██║");
    Sleep(100);
    gotoxy(22, 13);
    printf("██╔══██╗██║     ██║   ██║██║     ██╔═██╗     ██║     ██╔══██║██║╚██╗██║██║  ██║");
    Sleep(100);
    gotoxy(22, 14);
    printf("██████╔╝███████╗╚██████╔╝╚██████╗██║  ██╗    ███████╗██║  ██║██║ ╚████║██████╔╝");
    Sleep(100);
    gotoxy(22, 15);
    printf("╚═════╝ ╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝    ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝");
    Sleep(100);
    gotoxy(42, 17);
    printf("░▒▓█ W E I R D   B L O C K   L A N D █▓▒░");

    gotoxy(50, 27);
    printf("Please Press Any Key~!");

	while(true) {
		if(i%40==0)
		{
			
			
			for(j=0;j<5;j++)
			{
				//여기서 18의 값을 조정해서 첫번째 블럭도 다 지워지도록 조정
				gotoxy(19,20+j);
				printf("                                                                 ");
				
				
			}

			Block* block = new Block(rand() % 7, rand() % 4, 19, 20);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 25, 20);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 31, 20);
			show_cur_block(*block);
			delete block;

			block = new Block(rand() % 7, rand() % 4, 37, 20);
			show_cur_block(*block);
			delete block;
		}
		if(_kbhit())
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
	int i,j;
	SetColor(DARK_GRAY);
	for(i=0;i<21;i++)
	{
		for(j=0;j<14;j++)
		{
			if(j==0 || j==13 || i==20)		//레벨에 따라 외벽 색이 변함
			{
				SetColor((level %6) +1);
				
			}else{
				SetColor(DARK_GRAY);
			}
			gotoxy( (j*2)+ab_x, i+ab_y );
			if(total_block[i][j] == 1)
			{	
				printf("■");
			}else{
				printf("  ");
			}
			
		}
	}
	if (level == 0 || level == 3 || level == 6 || level == 9) {
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
	static int printed_text=0;
	SetColor(GRAY);
	if(printed_text == 0)
	{
		gotoxy(33,7);
		printf("STAGE");

		gotoxy(33,9);
		printf("SCORE");

		gotoxy(33,12);
		printf("LINES");
		

	}
	gotoxy(41,7);
	printf("%10d",level+1);
	gotoxy(41,9);
	printf("%10d",score);
	gotoxy(41,12);
	printf("%10d",lines_left);
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
	Sleep(3000); // 3초 대기
	system("cls");
	return 1;
}

//게임이 끝났을때 게임 오버창을 띄우는 함수
int Printer::show_gameover()
{
    system("cls");
    SetColor(RED);
    gotoxy(10, 5);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    gotoxy(10, 6);
    printf("┃  ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗  ███████╗██████╗ ┃");
    gotoxy(10, 7);
    printf("┃ ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║  ██╔════╝██╔══██╗┃");
    gotoxy(10, 8);
    printf("┃ ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║  █████╗  ██████╔╝┃");
    gotoxy(10, 9);
    printf("┃ ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝  ██╔══╝  ██╔══██╗┃");
    gotoxy(10, 10);
    printf("┃ ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝   ███████╗██║  ██║┃");
    gotoxy(10, 11);
    printf("┃  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝    ╚══════╝╚═╝  ╚═╝┃");
    gotoxy(10, 12);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    SetColor(GRAY);
    gotoxy(25, 14);
    printf("▶ 아무 키나 누르면 메인 화면으로 돌아갑니다...");
    (void)_getch();
	system("cls");

	return 0;
}

void Printer::show_ghostBlock(Block& b)
{
    SetColor(GRAY);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b.get_number(i, j)) {
                int x = b.get_x() + j;
                int y = b.get_y() + i;

                // 맵 내부에 있을 때만 출력
                if (y >= 0 && y < 21 && x >= 0 && x < 14) {
                    gotoxy(x * 2 + ab_x, y + ab_y);
                    printf("▦");
                }
            }
        }
    }
}


void Printer::erase_ghostBlock(Block& b, char total_block[21][14])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b.get_number(i, j)) {
                int x = b.get_x() + j;
                int y = b.get_y() + i;

                if (x < 0 || x >= 14 || y < 0 || y >= 21)
                    continue; // 범위 밖이면 skip

                gotoxy(x * 2 + ab_x, y + ab_y);

                if (total_block[y][x]) {
                    SetColor(DARK_GRAY);
                    printf("■");
                }
                else {
                    printf("  ");
                }
            }
        }
    }
}



void Printer::show_combo()
{
    flash_map_border();
    const int colors[] = { RED, YELLOW, GREEN, SKY_BLUE, BLUE, VOILET };
    const int colorCount = sizeof(colors) / sizeof(colors[0]);

    for (int loop = 0; loop < 6; ++loop) { // 총 6번 깜빡이게
        SetColor(colors[loop % colorCount]);

        gotoxy(15, 8);
        printf("┌────────────────────────────────-──────────────┐");
        gotoxy(15, 9);
        printf("│  ██████╗ ██████╗ ███╗   ███╗██████╗  ██████╗  │");
        gotoxy(15, 10);
        printf("│ ██╔════╝██╔═══██╗████╗ ████║██╔══██╗██╔═══██╗ │");
        gotoxy(15, 11);
        printf("│ ██║     ██║   ██║██╔████╔██║██████╔╝██║   ██║ │");
        gotoxy(15, 12);
        printf("│ ██║     ██║   ██║██║╚██╔╝██║██╔══██╗██║   ██║ │");
        gotoxy(15, 13);
        printf("│ ╚██████╗╚██████╔╝██║ ╚═╝ ██║██████╔╝╚██████╔╝ │");
        gotoxy(15, 14);
        printf("│  ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═════╝  ╚═════╝  │");
        gotoxy(15, 15);
        printf("└─────────────────────────────────-─────────────┘");

        Sleep(100);
    }

    SetColor(GRAY); // 원래 색으로 복구

    fflush(stdin);
    Sleep(500);
   
    (void)_getche();
    system("cls");
    return;
}



#define DIALOG_WIDTH 74
#define DIALOG_X 5
#define DIALOG_Y 20
#define DIALOG_LINES 5

void Printer::draw_dialog_frame() {
    SetColor(WHITE);

    // 상단 테두리
    gotoxy(DIALOG_X, DIALOG_Y);
    printf("┌");
    for (int i = 0; i < DIALOG_WIDTH; i++) printf("─");
    printf("┐");

    // 본문 영역 (이름 + 대사 5줄)
    for (int i = 1; i <= DIALOG_LINES + 1; i++) {
        gotoxy(DIALOG_X, DIALOG_Y + i);
        printf("│");
        for (int j = 0; j < DIALOG_WIDTH; j++) printf(" ");
        printf("│");
    }

    // 하단 테두리
    gotoxy(DIALOG_X, DIALOG_Y + DIALOG_LINES + 2);
    printf("└");
    for (int i = 0; i < DIALOG_WIDTH; i++) printf("─");
    printf("┘");
}



void Printer::dialog_line(const char* speaker, const char* lines[], int lineCount) {
    SetColor(WHITE);

    // 이름 출력 (왼쪽 테두리 다음 칸부터)
    gotoxy(DIALOG_X + 1, DIALOG_Y + 1);
    printf(" %-*.*s ", DIALOG_WIDTH-2, DIALOG_WIDTH-2, speaker);  // 양쪽 공백 포함

    // 대사 출력 (최대 5줄)
    for (int i = 0; i < DIALOG_LINES; i++) {
        gotoxy(DIALOG_X + 1, DIALOG_Y + 2 + i);
        if (i < lineCount)
            printf(" %-*.*s ", DIALOG_WIDTH-2, DIALOG_WIDTH-2, lines[i]);
        else
            printf(" %-*.*s ", DIALOG_WIDTH-2, DIALOG_WIDTH-2, "");  // 빈 줄도 양쪽 공백 유지
    }

    // 안내 메시지
    gotoxy(DIALOG_X, DIALOG_Y + DIALOG_LINES + 3);
    printf("▶ 계속하려면 아무 키나 누르세요...");
    (void)_getch();

    // 안내 메시지 지움
    gotoxy(DIALOG_X, DIALOG_Y + DIALOG_LINES + 3);
    printf("                                         ");
}


void Printer::showSystemScreen(const char* lines[], int lineCount) {
    const int startX = 18;
    const int startY = 1;

    SetColor(RED);

    // SYSTEM ASCII 아트 출력
    gotoxy(startX, startY);
    printf("  ██╗███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗██╗  ");
    gotoxy(startX, startY + 1);
    printf(" ██╔╝██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║╚██╗ ");
    gotoxy(startX, startY + 2);
    printf("██╔╝ ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║ ╚██╗");
    gotoxy(startX, startY + 3);
    printf("╚██╗ ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║ ██╔╝");
    gotoxy(startX, startY + 4);
    printf(" ╚██╗███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║██╔╝ ");
    gotoxy(startX, startY + 5);
    printf("  ╚═╝╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝  ");

    // 박스 위치 및 크기
    const int boxWidth = 74;
    const int boxHeight = 9;
    const int boxX = 13;
    const int boxY = startY + 8;

    SetColor(WHITE);

    // 박스 상단
    gotoxy(boxX, boxY);
    printf("┌");
    for (int i = 0; i < boxWidth - 2; ++i) printf("─");
    printf("┐");

    // 박스 내부
    for (int i = 1; i < boxHeight - 1; ++i) {
        gotoxy(boxX, boxY + i);
        printf("│");
        for (int j = 0; j < boxWidth - 2; ++j) printf(" ");
        printf("│");
    }

    // 박스 하단
    gotoxy(boxX, boxY + boxHeight - 1);
    printf("└");
    for (int i = 0; i < boxWidth - 2; ++i) printf("─");
    printf("┘");

    // 메시지 출력 (중앙 정렬)
    SetColor(YELLOW);
    int firstLineY = boxY + (boxHeight - lineCount) / 2;
    for (int i = 0; i < lineCount; ++i) {
        int len = strlen(lines[i]);
        int msgX = boxX + (boxWidth - len) / 2;
        gotoxy(msgX, firstLineY + i);
        printf("%s", lines[i]);
    }

    // 안내 문구
    SetColor(GRAY);
    gotoxy(boxX + (boxWidth - 30) / 2, boxY + boxHeight + 1);
    printf("▶ 계속하려면 아무 키나 누르세요...");
    _getch();
}





void Printer::first_story() {
    system("cls");
    hideCursor();

    draw_dialog_frame(); // 테두리는 딱 한 번만 그림

    const char* lines1[] = {
        " ",
        "어라 이게 무엇지...? 테트리스?",
        "엄청 오래된 게임 아니야?",
        "누가 내 컴퓨터로 뭘 해놨나...?",
        "과제도 하기 심심한데 한 번 해볼까..?"
    };
    dialog_line("나", lines1, 5);

    const char* lines2[] = {" ","(게임을 시작했다...)" };
    dialog_line("나", lines2, 2);

    const char* lines3[] = {
        " ",
        "어라.. 여기는 어디지...",
        "분명 테트리스 게임을 하고 있던 것 같은데....",
        "(쿵) 테트리스 블럭..? 이게 왜 여기에..??"
    };
    dialog_line("나", lines3, 4);

    const char* lines4[] = { " ","너 여기가 처음이구나" };
    dialog_line("??", lines4, 2);

    const char* lines5[] = { " ", "여기는 어딘데?" };
    dialog_line("나", lines5, 2);

    const char* lines6[] = { " ","ㅋㅋㅋㅋ 여기서 잘 살아남아봐~" };
    dialog_line("??", lines6, 2);

    const char* lines7[] = { " ","(갑자기 사라진다)" };
    dialog_line("??", lines7, 2);

    const char* lines8[] = {
        " ",
        "흐음... 여기를 어떻게 나간담...",
        "일단 가보자!"
    };
    dialog_line("나", lines8, 3);

    system("cls");
}


void Printer::reverse_stage() {
    system("cls");
    hideCursor();
    reverse();
    draw_dialog_frame();

    const char* lines1[] = { " ", "어디야 여긴...? 뭔가 다들 거꾸로 매달려 있는데...?", "이상한데..." };
    dialog_line("나", lines1, 3);

    const char* lines2[] = { " ", "저기요! 혹시 여기서 나가는 길 아세요?" };
    dialog_line("나", lines2, 2);

    const char* lines3[] = { " ", "뭐야 넌 여기가 처음이야? 이상한 애네" };
    dialog_line("??", lines3, 2);

    const char* lines4[] = { " ", "불쌍해보이니 알려주자면 여긴 모든 게 거꾸로인 곳이야" };
    dialog_line("??", lines4, 2);

    const char* lines5[] = { " ", "거꾸로인게 어쨌단 거지..." };
    dialog_line("나", lines5, 2);

    system("cls");

    const char* systemLines[] = {
        "세상이 거꾸로 뒤집혔다!",
        "당신은 거꾸로나라에 도착했습니다!",
        "테트리스의 맵이 거꾸로 뒤집히니 조심하세요!"
    };
    showSystemScreen(systemLines, 3);

    system("cls");
}

void setConsoleColor(WORD foreground, WORD background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}

void Printer::mirror_stage() {
    system("cls");
    hideCursor();
    mirror();
    draw_dialog_frame();

    const char* lines1[] = { " ", "거꾸로 나라는 간신히 빠져나왔는데...", "여긴 또 뭐야? 사방이 거울이잖아?!" };
    dialog_line("나", lines1, 3);

    const char* lines2[] = { " ", "이래서 길을 찾을 수 있나...", "(웅성웅성)" };
    dialog_line("나", lines2, 3);

    const char* lines3[] = { " ", "반가워~ 여기 처음이지?" };
    dialog_line("??", lines3, 2);

    const char* lines4[] = { " ", "아, 또 누구야... 도대체 여긴 어디예요?" };
    dialog_line("나", lines4, 2);

    const char* lines5[] = { " ", "여긴 거울 나라야~ 방향이 계속 바뀌는 아주 재밌는 곳이지" };
    dialog_line("??", lines5, 2);

    const char* lines6[] = { " ", "뒤죽박죽인 방향을 조심해~ 한 번 잘 살아남아봐!" };
    dialog_line("??", lines6, 2);

    const char* lines7[] = { " ", "방향이... 뒤죽박죽...? 또 뭔데 그건..." };
    dialog_line("나", lines7, 2);
    system("cls");

    const char* systemLines[] = {
        "방향키의 조작이 마음대로 바뀐다??",
        "당신은 거울나라에 도착했습니다!",
        "테트리스의 방향키가 계속해서 바뀌니 조심하세요!"
    };
    showSystemScreen( systemLines, 3);

    system("cls");
}

void Printer::miro_stage() {
    system("cls");
    hideCursor();
    miro();

    draw_dialog_frame();

    const char* lines1[] = { " ", "아니 힘들게 거울 나라까지 지나왔는데 여긴 또 뭐야", "슬슬 짜증이 나네...심지어 여기 사방에 큰 벽이 있잖아!!!" };
    dialog_line("나", lines1, 3);

    const char* lines2[] = { " ", "어라 거기! 뭐 좀 물어보자!" };
    dialog_line("나", lines2, 2);

    const char* lines3[] = { " ", "내 휴식을 방해하면서 거기라니!! 뭐야 이 이상한 앤" };
    dialog_line("??", lines3, 2);

    const char* lines4[] = { " ", "아니..여기서 길을 잃었는데 어떻게 나가지?" };
    dialog_line("나", lines4, 2);

    const char* lines5[] = { " ", "ㅋㅋㅋㅋㅋ당연하지 여긴 미로니까" };
    dialog_line("??", lines5, 2);

    const char* lines6[] = { " ", "미로..?" };
    dialog_line("나", lines6, 2);

    system("cls");

    const char* systemLines[] = {
        "당신은 미로에 갇혔다!",
        "당신은 미로나라에 도착했습니다!",
        "테트리스에 미로 장애물이 나타나니 미로 끝에 잘 도달해보세요!"
    };
    showSystemScreen( systemLines, 3);

    system("cls");
}

void Printer::repeat_level() {
    system("cls");
    hideCursor();
    draw_dialog_frame();

    const char* lines1[] = { " ", "휴... 드디어 탈출이네!", "이제 정말 나갈 수 있는 건가?" };
    dialog_line("나", lines1, 3);

    const char* lines2[] = { " ", "큭큭... 그럼 재미없지!" };
    dialog_line("??", lines2, 2);

    const char* lines3[] = { " ", "더 빠른 속도로 즐기게 해주지!", "한 번 탈출해 봐!" };
    dialog_line("??", lines3, 3);

    const char* lines4[] = { " ", "...뭐라고?" };
    dialog_line("나", lines4, 2);

    system("cls");

    const char* systemLines[] = {
        "블럭이 더 빠른 속도로 추락한다!",
        "여태 거쳐온 나라를 두 번씩 더 탈출하자!"
    };
    showSystemScreen(systemLines, 2);

    system("cls");
}

void Printer::weird_stage() {
    system("cls");
    hideCursor();
    draw_dialog_frame();

    const char* lines1[] = {
        " ",
        "이제 진짜 끝났겠지...?",
        "거꾸로도, 거울도, 미로도 다 지나왔는데..."
    };
    dialog_line("나", lines1, 3);

    const char* lines2[] = {
        " ",
        "어디선가 이상한 기운이 느껴진다...",
        "뭐야... 방금 지나온 곳이 한꺼번에 섞인 것 같잖아?!"
    };
    dialog_line("나", lines2, 3);

    const char* lines3[] = {
        " ",
        "후후후... 마지막 관문에 온 걸 환영해~",
        "익숙한 듯 낯선, 이 세계에서 넌 헤맬 수밖에 없어."
    };
    dialog_line("??", lines3, 3);

    const char* lines4[] = {
        " ",
        "거꾸로 된 길, 헷갈리는 방향, 끝이 안 보이는 미로...",
        "그 모든 게 한꺼번에 찾아올 거야~"
    };
    dialog_line("??", lines4, 3);

    const char* lines5[] = {
        " ",
        "...이걸 다 버티라고?",
    };
    dialog_line("나", lines5, 2);

    const char* lines6[] = {
        " ",
        "미쳤네 진짜..."
    };
    dialog_line("나", lines6, 2);

    const char* systemLines[] = {
        "당신은 이상한 나라에 도착했습니다!",
        "거꾸로 나라 + 거울 나라 + 미로 나라",
        "모든 효과가 동시에 적용됩니다. 끝까지 버텨보세요!"
    };
    showSystemScreen(systemLines, 3);

    system("cls");
}

void Printer::ending() {
    system("cls");
    hideCursor();

    draw_dialog_frame();

    const char* lines1[] = { " ", "와... 쉽지 않았다 진짜...", "드디어 집에 갈 수 있나...." };
    dialog_line("나", lines1, 3);
    system("cls");

    const char* lines2[] = { " ", "잘가... 간만에 즐거웠다.." };
    dialog_line("??", lines2, 2);
    system("cls");

    const char* lines3[] = {
        " ",
        "(졸린 눈을 뜨며)",
        "내가 잠들었었나...",
        "손에 이 블럭은 뭐지?",
        "에잇 나도 몰라, 밥 먹으러 가야겠다"
    };
    dialog_line("나", lines3, 5);

    system("cls");
    //테트리스 맵을 한번더 보여줌
}




void Printer::flash_map_border() {
    const int colors[] = { RED, YELLOW, GREEN, SKY_BLUE, BLUE, VOILET };
    const int colorCount = sizeof(colors) / sizeof(colors[0]);

    // 맵 테두리 위치
    const int top = 0, left = 5;
    const int width = 12, height = 20;

    for (int t = 0; t < 6; ++t) {
        SetColor(colors[t % colorCount]);

        // 상단 테두리
        for (int x = 0; x <= width + 1; ++x) {
            gotoxy(left + x * 2, top);
            printf("■");
        }

        // 하단 테두리
        for (int x = 0; x <= width + 1; ++x) {
            gotoxy(left + x * 2, top + height + 1);
            printf("■");
        }

        // 좌우 테두리
        for (int y = 1; y <= height; ++y) {
            gotoxy(left, top + y);
            printf("■");
            gotoxy(left + (width + 1) * 2, top + y);
            printf("■");
        }

        Sleep(100);
    }

    SetColor(GRAY); // 복원
}


void Printer::mirror() {
    gotoxy(13, 0); printf("⠀⣠⣈⡀⠋⠳⢦⡤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣤⢲⠎⠋⢠⢡⠄⠀\n");
    gotoxy(13, 1); printf("⠀⢠⡁⡁⠀⠀⠀⠈⠙⠻⢦⣤⣤⣤⣤⢤⢤⢤⣤⢤⢤⢤⢤⣤⡤⣤⡤⣤⣤⡤⣤⡤⣤⡤⡤⣤⠤⡤⣤⢤⣤⢤⣤⣤⣤⣤⢤⢤⣤⣤⢤⢤⢤⢠⢤⡴⠗⠙⠀⠀⠀⠀⢈⣈⡀⠀\n");
    gotoxy(13, 2); printf("⠀⣁⣉⡁⠀⠀⠀⠀⠀⠀⠀⡆⠠⢠⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⢤⢢⠆⠀⠀⡂⠀⠀⠀⠀⠀⠀⠀⢈⣈⡁⠀\n");
    gotoxy(13, 3); printf("⠀⣀⣁⡁⠀⠀⠀⠀⠀⠀⠀⡃⠀⠀⠈⠘⠛⢶⣤⡀⠀⡀⢀⠀⢀⠀⡀⡀⢀⠀⡀⢀⠀⡀⢀⠀⢀⢀⠀⡀⢀⢀⠀⡀⣠⣤⠶⠋⠉⠁⠀⠀⠀⠀⡁⠀⠀⠀⠀⠀⠀⠀⢈⣈⡁⠀\n");
    gotoxy(13, 4); printf("⠀⣈⣁⡁⢠⡠⣄⣀⠀⠀⠀⡃⠀⠀⠀⠀⠀⠀⠀⠉⡉⠉⢊⣉⢋⡉⠙⠉⠋⠛⠉⠋⠙⠉⠃⠋⠁⠉⠓⠉⢉⣉⡉⡙⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⡁⠀⠀⠀⣤⢤⠆⠋⢉⣈⡁⠀\n");
    gotoxy(13, 5); printf("⠀⣈⣁⠁⢘⢐⠉⠂⠛⠓⠂⡃⠀⣀⣀⠀⠀⠀⠀⠀⡁⠀⠀⠈⠙⠙⠓⡦⣄⣀⣀⣀⣀⣀⣀⣀⣀⣤⡶⠛⠉⠁⠀⡁⠀⠀⠀⠀⢀⣀⢤⢲⠄⠀⡁⢂⠝⠋⠂⠁⠀⠀⢈⣊⡁⠀\n");
    gotoxy(13, 6); printf("⠀⢐⣉⠁⢘⢀⠀⠀⠀⡑⠀⡃⠐⡉⠉⠘⠛⠝⠂⠀⡁⠀⣀⠀⠀⠀⠀⠀⠁⡉⠁⠉⠁⢁⡭⠗⢑⠁⠀⠀⠀⢀⠀⡁⠀⡤⠖⠚⠛⠈⠉⠀⡃⠀⡁⢘⠀⠀⠀⠀⠀⠀⢈⣈⡂⠀\n");
    gotoxy(13, 7); printf("⠀⢁⣉⠁⢘⢈⠀⢘⠃⡐⠀⡃⠀⡑⠒⠒⠖⠒⡁⠀⡁⠀⡂⠉⡛⠓⠒⢶⠀⡛⠖⠢⠏⠁⠀⠀⢸⠀⢀⡴⠚⠉⠀⡁⠀⡓⠒⠖⡂⠀⡶⠒⡁⠀⡁⢘⠈⠋⢈⠉⠁⠀⢈⣊⡁⠀\n");
    gotoxy(13, 8); printf("⠀⢉⢃⠁⢸⢀⠀⢈⠀⡐⠀⡃⠀⡁⠀⠀⡃⠀⠄⠀⡁⠀⡃⠀⡃⠖⡒⢊⠀⡇⠀⠀⡃⠀⡖⠊⢸⠀⢀⡲⠚⠒⠂⡁⠀⡇⠀⠀⡁⠀⡁⠀⡁⠀⡁⢸⠀⠀⢘⠀⠀⠀⠘⣈⠁⠀\n");
    gotoxy(13, 9); printf("⠀⢁⠃⠃⢸⠠⠀⢈⠀⡐⠀⡇⠀⠅⠀⠀⠅⠀⠂⠀⠅⠀⡃⠀⡃⠐⡀⢸⠀⡇⠀⠀⡃⠀⡃⠀⢸⠀⠀⡇⠀⠀⠀⡁⠀⡇⠀⠀⡅⠀⠇⠀⡁⠀⠅⢸⠀⠀⠸⠀⠀⠀⠘⡉⠃⠀\n");
    gotoxy(13, 10); printf("⠀⠊⠋⠃⠸⢐⠀⠨⠀⠰⠀⡇⠀⠃⠀⠈⠆⠀⡁⠀⠃⠀⠃⠀⠇⠐⡀⢸⠀⡇⠀⠀⠇⠀⠇⠀⢸⠀⠀⠇⠀⠀⠀⡁⠀⡇⠀⠀⠆⠀⠇⠀⠃⠀⠃⢸⠀⠀⠸⠀⠀⠀⠘⠙⠁⠀\n");
    gotoxy(13, 11); printf("⠀⠃⠋⠃⢸⠐⠀⠘⠀⠡⠀⠇⠀⠃⠀⠀⠃⠀⠄⠀⠃⠀⠇⠀⠃⠐⡀⠸⠀⡇⠀⠀⠇⠀⠇⠀⢸⠀⠈⠇⠀⠀⠀⠁⠀⡇⠀⠀⠃⠀⠇⠀⠇⠀⠃⠸⠀⠀⠸⠀⠀⠀⠘⠙⠁⠀\n");
    gotoxy(13, 12); printf("⠀⠉⠋⠃⠸⢈⠀⠘⠀⠡⠀⠇⠀⠃⠀⠀⠃⠀⠂⠀⠃⠀⠃⠀⠃⠖⠶⠚⠀⡇⠀⠀⠇⠀⠓⠖⠼⠀⠈⠳⠲⠲⠆⠁⠀⢇⣀⡀⠃⠀⠗⠉⠆⠀⠃⠸⠀⠀⠸⠀⠀⠀⠘⠛⠁⠀\n");
    gotoxy(13, 13); printf("⠀⠩⠛⠂⠸⠠⠀⠘⠀⠡⠀⠇⠀⠳⠦⠲⠱⠆⠁⠀⠃⠀⠇⠖⠶⠲⠆⠸⠀⠇⠶⠦⢣⠀⠀⠀⠸⠀⠈⠶⠒⠶⠂⠅⠀⠏⡈⠉⠆⠀⢧⡀⠇⠀⠃⠸⠐⠶⠲⠖⠆⠀⠘⠛⠅⠀\n");
    gotoxy(13, 14); printf("⠀⠪⠫⠂⠸⠐⠀⠘⣀⠡⠀⠇⠀⠣⠴⠔⠃⠉⠄⠀⠃⠀⠃⠀⢀⣠⢤⠜⠀⡇⣤⢤⠤⠽⢦⣄⠸⠀⠨⣤⣀⠀⠀⠅⠀⢏⣉⣉⢦⣀⡀⠁⠆⠀⠃⠸⠀⠀⠀⠀⠀⠀⠘⠟⠇⠀\n");
    gotoxy(13, 15); printf("⠀⠪⠣⠂⠸⢈⠐⠋⠀⠒⠀⠇⠀⠆⠀⠀⠀⠀⠂⠀⠃⠀⠧⠰⠚⠁⠀⠀⠀⡇⠀⠀⠀⠀⠀⠈⢸⠀⠀⠀⠉⠳⠄⠂⠀⡇⠈⠈⠁⠀⠉⠓⠆⠀⠃⠸⠀⠀⠀⠀⠀⠀⠸⠝⠆⠀\n");
    gotoxy(13, 16); printf("⠀⠘⠓⠂⢸⠠⡄⠖⠒⠣⠀⡇⠀⠆⠀⠀⠀⣠⠅⠀⠃⠀⠀⠀⠀⠀⠀⣠⠟⠊⠓⠋⠋⠓⠋⠚⠂⢣⡄⠀⠀⠀⠀⠃⠀⣇⢀⣀⣀⣀⣀⡀⠇⠀⠃⢸⠑⠚⠢⣤⣀⡀⠰⠻⠐⠀\n");
    gotoxy(13, 17); printf("⠀⠚⠎⠆⠀⠁⠀⠀⠀⠡⠀⡇⠀⢆⣠⠖⠛⠈⠀⠀⡃⠀⠀⠀⢀⡰⡋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢳⣄⠀⠀⠃⠀⡇⠉⠈⠈⠀⠈⠀⠇⠀⡃⢸⠀⠀⠀⠀⠁⠁⠰⠳⠁⠀\n");
    gotoxy(13, 18); printf("⠀⠒⠎⠆⠀⠀⠀⠀⠀⢡⠀⡆⠰⠎⠁⠀⠀⠀⠀⠀⠆⠀⢀⡰⠎⠷⠶⠶⠶⠶⠶⠶⠶⠶⠖⠮⠖⠶⠲⠖⠾⠙⢆⡁⠀⡖⠶⠴⠳⠖⠖⠖⡂⠀⠆⡸⠀⠀⠀⠀⠀⠀⠰⠲⠆⠀\n");
    gotoxy(13, 19); printf("⠀⠒⠖⠆⠀⠀⠀⣠⠴⠆⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠆⡜⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⡆⠀⠀⠀⠀⠀⠀⠆⠀⠆⠉⠚⠦⣤⣀⠀⠀⠰⠶⠂⠀\n");
    gotoxy(13, 20); printf("⠀⢒⠖⠆⣠⠦⠋⠁⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⣴⠲⠴⠰⠶⠲⠖⠶⠖⠶⠖⠖⠖⠖⠖⠖⠖⠒⠖⠲⠲⠖⠶⠲⠶⢲⣄⠀⠀⠀⠀⠀⠆⠀⠆⠀⠀⠀⠀⠉⠳⡦⣴⠲⠆⠀\n");
    gotoxy(13, 21); printf("⠀⢒⠔⠏⠁⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⠀⣰⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠱⣄⠀⠀⠀⠂⠀⠆⠀⠀⠀⠀⠀⠀⠀⠰⡲⠆⠀\n");

}

void Printer::reverse() {
    gotoxy(13, 0); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 1); printf("⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⣒⡒⠒⠒⠒⠒⠒⠒\n");
    gotoxy(13, 2); printf("⡀⠀⠀⠀⠉⠀⠀⠀⢀⡀⣀⢀⣀⡀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠂⠀⠀⠀⠀⠀⠀⢀⣀⠠⠤⠀\n");
    gotoxy(13, 3); printf("⠈⠑⢤⠀⠀⠀⠀⠀⠀⠈⠀⠁⠀⠀⠀⢀⠀⠀⠀⠀⠀⠈⠒⠉⠉⠀⢤⠶⠶⣠⣀⠀⠀⢠⡺⠉⠃⡩⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠊⠁⠀⠀⠀⠀\n");
    gotoxy(13, 4); printf("⠀⠀⠀⠉⠑⠒⢤⠤⠄⠤⠤⠤⢄⡀⠀⠀⠁⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢢⠤⣑⣳⠀⢇⡠⠤⠎⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠔⡒⠊⢩⠉⠉⠉⡍⡉⠉⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 5); printf("⠀⠀⠀⠀⠀⠀⢸⠐⠒⢺⠒⠂⢸⠈⠢⣀⣀⠄⣀⡠⠠⠤⡤⣀⠤⣀⡀⠀⢸⠀⠀⢸⠀⢎⠀⠀⢸⠠⠤⠂⢰⠤⡴⠢⠋⠑⡄⠊⠀⡅⠘⢸⠂⠑⠂⡅⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 6); printf("⠀⠀⠀⠀⠀⠀⢸⠀⠀⢸⠀⠀⢸⠀⠀⢸⠀⠀⠆⠀⠀⠄⡇⠁⢸⠀⠀⠉⠁⠀⠀⢸⠀⢸⠀⠀⢸⠀⠀⠀⢸⠀⠀⠀⠀⠀⡇⠀⠀⠆⠒⢺⠒⠒⠂⡅⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 7); printf("⠀⠀⠀⠀⠀⠀⢸⠈⡉⢹⠉⡁⢸⠀⠀⢸⢨⠉⡅⠀⠀⠄⠃⠃⢸⠀⠀⠀⡁⠀⠀⠈⠆⢸⠀⠀⢸⠀⠀⠀⢸⠠⡄⡤⢠⠄⡇⠀⠀⡃⠠⢼⠠⠤⠄⡃⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 8); printf("⠀⠀⠀⠀⠀⠀⢸⢀⣁⣹⣈⣀⢸⠀⠀⢸⠐⠒⠂⠀⠀⠄⡇⡆⢸⠀⠀⠀⡆⠀⠀⠀⡇⠸⠀⠀⠘⠀⠀⠀⢸⠐⡄⡃⢸⠀⡇⠀⠀⡅⠠⢼⠠⠤⠀⡇⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 9); printf("⠀⠀⠀⠀⠀⠀⢸⠀⠄⢸⠀⠄⢸⠀⠀⢸⠀⠀⠀⠀⠀⠄⡁⡁⢸⠀⠀⠀⡇⠀⠀⠀⡇⡘⠀⠀⠀⡄⠀⠀⢸⠨⠅⡭⢨⠅⡇⠀⠀⠆⣀⣸⣀⣀⡀⠇⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 10); printf("⠀⠀⠀⠀⠀⠀⢸⠠⠤⢼⠤⠤⢸⠀⠀⢸⠠⠤⡄⠀⠀⠄⠇⠇⢸⠀⠀⠀⡇⠀⠀⠀⡇⡇⠀⠀⠀⡇⠀⠀⢸⠠⠃⠆⠸⠀⡇⠀⠀⡃⠀⠸⠀⠀⠀⡇⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 11); printf("⠀⠀⠀⠀⠀⠀⢸⡠⠄⠸⠄⠤⢸⠀⠀⢸⠀⠀⠳⣒⠒⠒⠒⡒⠎⠀⠀⠀⡇⠀⠀⠀⢰⠧⠀⠀⠀⡇⠀⠀⢸⠈⡅⠏⢸⠡⡇⠀⠀⡅⠀⠀⠀⠀⠀⡇⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 12); printf("⠀⠀⠀⠀⠀⠀⠀⠸⠤⠤⠤⠤⢸⠤⠤⠜⠀⠀⠀⠀⠙⠒⠉⠀⠀⠀⠀⠀⠇⠀⠀⠰⠃⠀⠀⠀⠀⡇⠀⠀⢸⣈⣁⣉⣈⣁⡇⠀⠀⠆⠀⠀⠀⠀⠀⡇⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 13); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠤⠢⠜⠴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡢⠤⠴⠐⠂⠒⠒⠐⠤⢇⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⡃⠀⠀⠀⠀⠀⡇⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 14); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠈⠉⠉⠉⠉⠉⠉⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⡅⠀⠀⠠⡄⠂⠑⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 15); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠀⠀⠀⠀⠀⠀⠀⠀⠆⠀⠀⠀⠀⠀⠀⠀⠀⡗⠒⠒⡒⠒⠒⠒⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 16); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⡃⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 17); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡈⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 18); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⡅⠀⠀⠀⠀⠀⠀⠀⠀⢁⠈⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 19); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 20); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢥⠀⠃⠀⠀⢠⠤⠤⣀⠀⠀⠈⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 21); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠤⣀⠀⢰⢁⠤⢀⡈⡆⢀⣀⠤⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 22); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢉⠼⢄⡀⠱⠎⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 23); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢃⠤⠀⠀⠘⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 24); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⡎⠁⠀⠀⡦⣸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 25); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡈⢈⠀⠓⢡⠁⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 26); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢦⠈⠈⠉⠒⠁⣀⡜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    gotoxy(13, 27); printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠐⠒⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");

}



void Printer::miro() {
    gotoxy(13, 1); printf("⣀⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠤⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    gotoxy(13, 2); printf("⠀⠀⠘⠒⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⢘⠀⠀⠀⠀⠈⢢⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀");
    gotoxy(13, 3); printf("⠀⠀⠀⠀⠀⠉⢁⡆⠀⠀⠀⠀⢀⠤⠐⠠⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠦⠠⢄⠀⠀⠀⠀⠀⠀⢀⣀⠎⠁⠀⠉");
    gotoxy(13, 4); printf("⠉⠉⠉⠉⠁⠉⠀⠀⠀⠀⡠⠄⠎⠀⠀⠀⠀⠈⣆⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⠠⠜⠀⠀⠀⠀⠀⠘⠥⠤⠤⠤⠤⠤");
    gotoxy(13, 5); printf("⠀⠀⡠⠤⠤⢄⡀⠀⡰⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠤⣀⠀⠀");
    gotoxy(13, 6); printf("⢀⠎⠁⠀⠀⠀⠘⡄⠈⠓⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⠚⠊⠑⠢⡰⠉⠀⠀⠀⠈⠱⡀");
    gotoxy(13, 7); printf("⠌⠀⠀⠀⠀⠀⠀⠘⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢔⡢⠭⠬⢔⡢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠒⠒⢰⠀⠀⠀⠀⠰⡁⠀⠀⠀⠀⠀⠀⠳");
    gotoxy(13, 8); printf("⣣⠀⠀⠀⠀⠀⠀⢨⡂⡔⡒⢉⡒⢤⣀⢀⣀⡀⣀⢀⣀⢀⣀⣀⢀⡀⢀⡀⣰⠱⠁⢀⠤⢄⡀⠈⡞⣀⣀⢀⣀⢀⣀⡀⢀⣀⡀⣀⡏⣀⢀⣀⠀⢣⡀⣀⣀⢘⡆⠀⠀⠀⠀⠀⢀⡧");
    gotoxy(13, 9); printf("⠀⠢⣄⡀⢀⣀⠤⠃⠀⠀⠈⡥⠴⢤⠤⡥⢤⠀⠀⠀⠀⠀⣀⠀⠀⠈⠁⠈⠀⢸⠀⡎⠀⠀⡃⠀⡇⠁⠀⠀⠀⠀⠀⠈⠀⠀⠀⢀⣀⣀⣀⣀⣉⣀⣀⠀⠀⠀⠘⠤⣀⣀⣀⠤⠊⠀");
    gotoxy(13, 10); printf("⠀⠀⠀⢸⠀⡀⢀⣀⣀⠄⠤⢴⠀⠀⠀⢰⠥⠄⠠⠀⢄⡐⡥⢇⣀⣀⣀⠀⠀⢰⠀⡇⢀⡀⡅⣀⡇⠀⠠⠤⠤⠤⠤⠤⠤⠤⠤⠼⠦⠐⠲⠤⡀⢸⠂⠭⣑⠂⠤⢀⡀⡇⠀⠀⠀⠀");
    gotoxy(13, 11); printf("⠒⠈⠉⠹⠨⠤⠤⠤⠖⠒⡈⠙⣤⣤⡔⠊⢐⡈⠳⠯⠿⠻⠿⠟⠉⠤⠼⠤⠤⠴⠤⠤⠤⠤⠤⠤⠧⠤⠌⠲⠄⠉⠛⢍⠉⢉⡬⠡⡌⠭⠴⠦⢌⡙⠠⠤⣀⠈⠁⠒⠠⡇⡑⠒⠤⠄");
    gotoxy(13, 12); printf("⠤⠔⠒⢂⣉⠉⠬⠭⢩⠉⣅⠡⢖⣈⠢⢭⣁⠒⡒⠓⠊⠡⠉⠍⠩⠍⠭⠩⠭⡍⠉⠉⠉⢱⠀⠸⠩⠍⠭⠩⠍⢍⡉⠈⡇⡼⡤⢤⡼⠀⡚⠐⠤⣈⠑⠒⠤⣉⠑⠒⠤⢄⡀⠉⠒⠂");
    gotoxy(13, 13); printf("⠒⠒⠉⠁⣀⠤⠧⠤⠤⠤⠤⠭⠬⠬⠭⠼⠤⠥⠬⠍⢭⠁⠉⠈⣡⠋⠀⢠⠊⡔⠀⠀⠀⢸⠒⠒⠒⠒⠂⢱⢢⠀⠑⠦⠧⠬⢩⠥⠮⠤⠥⠤⠤⠬⠱⠒⠰⠄⠛⠲⠀⠀⠈⠙⠒⠤");
    gotoxy(13, 14); printf("⡠⠔⠊⠉⢀⡠⠔⢢⠁⠘⠐⠂⠃⠒⠈⠒⠒⠒⠒⡎⠁⡇⠀⢰⠁⡀⢀⠉⡉⢈⠉⡉⢉⠈⠉⠉⢡⠀⠀⢸⠀⠳⡀⠀⠐⡖⣉⢊⠓⡌⠁⠉⠈⠁⠉⠉⠁⠉⠉⠁⠉⠉⠉⠉⠉⠈");
    gotoxy(13, 15); printf("⣀⠤⠔⠊⠁⠀⠀⢀⠃⠀⠀⡠⠔⠊⠈⠁⣉⣉⣉⣉⣉⣉⣉⣉⣁⣈⣀⣀⣀⣀⡀⣀⡀⡇⠀⠀⠘⡒⠒⠚⡄⠀⠙⣄⠀⠈⠉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⠉⠒⠤");
    gotoxy(13, 16); printf("⠀⠀⠀⠀⠀⠀⠀⢈⠆⢰⠍⠤⠤⠤⢐⠉⡒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⡧⠠⠄⠸⠄⠤⠈⠆⠀⠀⠈⠢⡀⠀⠀⠀⣀⣀⠀⡄⢠⠀⡄⠤⠠⠬⠑⠦⠤");
    gotoxy(13, 17); printf("⠀⠀⠀⠀⡤⣒⠲⠊⠖⠎⠖⠲⠒⠖⣚⢄⠣⠀⠀⠀⢠⠊⠉⠈⢉⣉⣉⣉⣉⣉⣉⣉⣁⣀⣀⣀⣀⢰⠀⠀⠀⡖⠒⠒⠒⠒⠒⠒⠒⠙⡆⠀⠀⡇⠑⢄⡀⠀⠀⢤⠤⠤⠤⠤⠤⠤");
    gotoxy(13, 18); printf("⠀⠀⣀⠴⠪⢥⠑⠚⣒⣚⣒⠡⠉⠬⠥⠚⢇⠀⠀⡔⠁⠀⠀⢠⢫⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠄⠀⠀⠱⠤⠤⠤⠤⢄⠀⠀⠀⡇⠀⠀⡇⠀⠀⠑⠢⡀⠀⠑⠢⡄⠀⠀⠀");
    gotoxy(13, 19); printf("⠔⠊⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠈⢉⠍⠀⠀⠀⢠⠃⢸⠀⠀⠀⠀⠏⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀⡗⠒⠂⢇⠀⠀⠀⠀⠈⠒⣄⠀⠀⠑⠤⡀");
    gotoxy(13, 20); printf("⠀⠀⢀⡠⠒⠉⡆⠀⠀⠀⠀⠀⠀⡌⠀⠁⠈⠀⠀⠀⠀⢠⠃⠀⢰⠂⠒⠐⢸⠀⠀⠀⠀⡏⠉⠉⠉⠉⠉⠉⠉⠉⠉⢹⠄⠀⠀⠀⠱⡀⡇⠀⠀⠈⠢⡀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠈");
    gotoxy(13, 21); printf("⠀⡴⠥⠤⠤⠤⠱⡄⠀⠀⠀⢀⡰⠃⠒⠒⠐⠒⠐⠒⠒⡁⠀⢀⠇⢠⠒⠑⠂⠀⠀⠀⠀⡇⠀⠀⡔⠒⠒⠒⠒⠒⢲⢸⠘⡄⠀⠀⠀⠙⣄⣀⣀⣀⣀⡘⢦⡀⠤⠠⠄⠤⠠⠑⠦⠀");
    gotoxy(13, 22); printf("⠀⡇⠀⠀⠀⠀⠀⠈⠯⠼⢭⠕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⡜⠀⡎⠀⠀⢀⡏⠈⠉⠁⡇⣀⣀⡇⠀⢸⠉⠉⢱⢠⢸⠀⠘⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    gotoxy(13, 23); printf("⠀⡅⠀⠀⠀⠀⢀⡠⠜⠀⠈⠢⡄⢀⡀⠀⠀⠀⠀⠀⠰⠀⡰⠀⢰⠁⠀⠀⠸⡇⠀⠀⠀⡇⠀⠀⠀⣀⡠⠆⠀⠀⠉⢸⠀⠀⢘⠒⠈⠒⠈⠒⠈⠒⠈⠂⠑⠈⠀⠁⠈⠀⠁⠈⠀⠁");
}
