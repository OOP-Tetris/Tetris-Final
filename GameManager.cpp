#include "GameManager.h"
#include "Normal.h"
#include "Maze.h"
#include "Reverse.h"
#include "Mirror.h"
#include "Weird.h"
#include <iostream>
#include <conio.h>

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

        //&& buf[0] >= '1' && buf[0] <= '9'

		// 문자열이 정수형 숫자 하나로만 이루어졌는지 확인 - test: enable level 10
		if (strlen(buf) <= 2 ) {
			//i = buf[0] - '0'; // 문자 → 정수로 변환
            i = atoi(buf); // 문자열을 정수로 변환
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
	return i - 1;
}

void GameManager::run() {
	printer.hideCursor();
	printer.show_logo();
	std::cout << "\nPress Enter to start...\n";
	while (1) {
		int manager_level = input_level(); // GameManager의 현재 레벨을 저장하는 변수
		system("cls");

		while (manager_level < 10) { // GameManager의 레벨이 9 미만일 때만 루프
			Game* game = nullptr;

			if (manager_level == 0 || manager_level == 3 || manager_level == 6) {
				game = new Reverse();
			}
			else if (manager_level == 1 || manager_level == 4 || manager_level == 7) {
				game = new Mirror();
			}
			else if (manager_level == 2 || manager_level == 5 || manager_level == 8) {
				game = new Maze();
			}
			else if (manager_level == 9) {
                game = new Weird();
			}
            else {
                std::cout << "Invalid level!" << std::endl;
                return; // 잘못된 레벨인 경우 프로그램 종료
            }

			game->setLevel(manager_level); // GameManager의 레벨을 새로 생성된 Game 객체에 전달

			game->run(); // 게임 플레이 시작. 이 함수가 종료되어야 다음 코드 실행.

			// Game 객체 내부에서 cleared가 true로 설정되었는지 확인
			bool game_cleared_result = game->getCleared();
			// Game 객체 내부에서 실제로 레벨이 몇으로 바뀌었는지 확인 (디버깅용)
			int final_game_level = game->getLevel();



			// Game 객체가 클리어되었고, Game 객체 내부 레벨이 GameManager의 레벨보다 높다면
			// (즉, 레벨업이 발생했다면) GameManager의 레벨도 업데이트합니다.
			if (game_cleared_result && final_game_level > manager_level) { // 클리어되었는지 확인
				manager_level = final_game_level; // GameManager의 레벨을 Game 객체의 최종 레벨로 업데이트!;
			}
			else if (!game_cleared_result && final_game_level == 10) {
				printer.show_clear_screen(game->getScore());
			}
			else {
				break;
			}
			system("cls");


		}
	}
	


}
