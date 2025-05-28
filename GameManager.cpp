#include "GameManager.h"
#include "Normal.h"
#include "Reverse.h"
#include <iostream>

int GameManager::input_level() {
	int i = 0;

	char buf[5];

	//입력값 오류 해결 --> scanf_s()로 받게 되는 경우 1.0도 1로 인식하는 경우 생김, 
	//또한 선행 0을 허용하기 때문에 문제를 해결하기 위해 문자를 입력받는것으로 바꿈
	while (1) {
		printer.show_keys();

		fgets(buf, sizeof(buf), stdin);

		// '\n'이 버퍼 안에 포함되어 있으면 → 그냥 제거하고 넘어감
		if (strchr(buf, '\n')) {
			buf[strcspn(buf, "\n")] = '\0';
		}
		// '\n'이 없으면 → 길어서 초과된 것 → getchar로 나머지 버퍼 비우기
		else {
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
		}

		// 문자열이 정수형 숫자 하나로만 이루어졌는지 확인
		if (strlen(buf) == 1 && buf[0] >= '1' && buf[0] <= '8') {
			i = buf[0] - '0'; // 문자 → 정수로 변환
			break;
		}
		else {
			printer.gotoxy(10, 4);
			printf("올바른 숫자를 입력해주세요.");
			Sleep(1000);
			printer.gotoxy(10, 4);
			printf("                            ");
			system("cls");
		}
	}
	system("cls");
	return i-1;
}

void GameManager::run() {
    printer.hideCursor();
    printer.show_logo();
    std::cout << "\nPress Enter to start...\n";


    while (true) {

        int level = input_level();
        system("cls");

        Game* game = nullptr;
        if (level == 0 || level == 3 || level == 6)
            game = new Reverse();
        else
            game = new Normal();
        //std::cout << level;

        game->setLevel(level);
        game->run();

        system("cls");
    }
}
