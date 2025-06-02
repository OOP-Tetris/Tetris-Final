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
		printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
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
	Sleep(1000); // 3초 대기
	system("cls");
	return 1;
}

//게임이 끝났을때 게임 오버창을 띄우는 함수
int Printer::show_gameover()
{
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
    SetColor(BLUE);
    gotoxy(15, 8);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    gotoxy(15, 9);
    printf("┃**************************┃");
    gotoxy(15, 10);
    printf("┃*        COMBO EVENT       *┃");
    gotoxy(15, 11);
    printf("┃**************************┃");
    gotoxy(15, 12);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
   
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
    _getch();

    // 안내 메시지 지움
    gotoxy(DIALOG_X, DIALOG_Y + DIALOG_LINES + 3);
    printf("                                         ");
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
    dialog_line("나", lines7, 2);

    const char* lines8[] = {
        " ",
        "흐음... 여기를 어떻게 나간담...",
        "일단 가보자!"
    };
    dialog_line("나", lines8, 3);

    system("cls");
}



void Printer::mirror_stage() {
    printf("뭐야 여긴!! 사방이 거울이잖아!!");
    printf("이래서 길을 찾을 수 있나...");
    printf("?? : 반가워ㅎㅎ");
    printf("누구세요? 여기서 어떻게 나가죠?");
    printf("흠...너 아무것도 모르는 구나");
    printf("여긴 거울 나라야~ 어느 방향인지 헷갈리게 하는 아주 재밌는 곳이지");
    printf("조금 도와주자면 뒤죽박죽인 방향을 조심해~");
    printf("한번 잘 살아남아봐");
    printf("방향이 뒤죽박죽이라고...?");

    system("cls");

    printf("<system>");
    printf("방향키의 조작이 마음대로 바뀐다??");
    printf("당신은 거울나라에 도착했습니다!");
    printf("테트리스의 방향키가 계속해서 바뀌니 조심하세요!");
}

void Printer::reverse_stage() {
    printf("힘들게 거울 나라를 빠져나왔더니 여긴 또 어디야 --");
    printf("분명 탈출구가 있다고 했는데!");
    printf("모두가 거꾸로 매달려 있네... 머리 안아픈가");
    printf("저기요 여기서 어떻게 나가요?");
    printf("뭐야 넌 여기가 처음이야? 이상한 애네");
    printf("흠...불쌍해보이니 도와주자면 여긴 모든것이 거꾸로야");
    printf("거꾸로인게 어쨌단 거지...");


    system("cls");

    printf("<system>");
    printf("세상이 거꾸로 뒤집혔다!");
    printf("당신은 거꾸로나라에 도착했습니다!");
    printf("테트리스의 맵이 거꾸로 뒤집히니 조심하세요!");
}

void Printer::miro_stage() {
    printf("아니 힘들게 거꾸로 나라까지 지나왔는데 여긴 또 뭐야");
    printf("슬슬 짜증이 나네...심지어 여기 사방에 큰 벽이 있잖아!!!");
    printf("어라 거기 뭐 좀 물어보자");
    printf("내 휴식을 방해하면서 거기라니!! 뭐야 이 이상한 앤");
    printf("아니..여기서 길을 잃었는데 어떻게 나가지?");
    printf("ㅋㅋㅋㅋㅋ당연하지 여긴 미로니까");
    printf("미로..?");


    system("cls");

    printf("<system>");
    printf("당신은 미로에 갇혔다!");
    printf("당신은 미로나라에 도착했습니다!");
    printf("테트리스에 미로 장애물이 나타나니 미로 끝에 잘 도달해보세요!");

}

void Printer::ending() {
    printf("와...쉽지 않았다 진짜...드디어 집에 갈수 있나....");
    system("cls");
    printf("?? : 잘가...간만에 즐거웠다..");
    system("cls");
    printf("(졸린 눈을 뜨며)");
    printf("내가 잠들었었나...");
    printf("손에 이 블럭은 뭐지?");
    printf("에잇 나도 몰라 밥먹으러 가야겠다");
    system("cls");
    //테트리스 맵을 한번더 보여줌
}


