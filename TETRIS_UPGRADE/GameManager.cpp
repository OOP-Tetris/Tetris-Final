#include "GameManager.h"
#include "Normal.h"
#include "Maze.h"
#include "Reverse.h"
#include <iostream>
#include <conio.h>

int GameManager::input_level() {
	int i = 0;

	char buf[5];

	//�Է°� ���� �ذ� --> scanf_s()�� �ް� �Ǵ� ��� 1.0�� 1�� �ν��ϴ� ��� ����, 
	//���� ���� 0�� ����ϱ� ������ ������ �ذ��ϱ� ���� ���ڸ� �Է¹޴°����� �ٲ�
	while (1) {
		printer.show_keys();

		fgets(buf, sizeof(buf), stdin);

		// '\n'�� ���� �ȿ� ���ԵǾ� ������ �� �׳� �����ϰ� �Ѿ
		if (strchr(buf, '\n')) {
			buf[strcspn(buf, "\n")] = '\0';
		}
		// '\n'�� ������ �� �� �ʰ��� �� �� getchar�� ������ ���� ����
		else {
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
		}

		// ���ڿ��� ������ ���� �ϳ��θ� �̷�������� Ȯ��
		if (strlen(buf) == 1 && buf[0] >= '1' && buf[0] <= '8') {
			i = buf[0] - '0'; // ���� �� ������ ��ȯ
			break;
		}
		else {
			printer.gotoxy(10, 4);
			printf("�ùٸ� ���ڸ� �Է����ּ���.");
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
	while (1) {
		int manager_level = input_level(); // GameManager�� ���� ������ �����ϴ� ����
		system("cls");

		while (manager_level < 10) { // GameManager�� ������ 9 �̸��� ���� ����
			Game* game = nullptr;

			if (manager_level == 0 || manager_level == 3 || manager_level == 6) {
				game = new Reverse();
			}
			else if (manager_level == 2 || manager_level == 5 || manager_level == 8) {
				game = new Maze();
			}
			else {
				game = new Normal();
			}

			game->setLevel(manager_level); // GameManager�� ������ ���� ������ Game ��ü�� ����

			game->run(); // ���� �÷��� ����. �� �Լ��� ����Ǿ�� ���� �ڵ� ����.

			// Game ��ü ���ο��� cleared�� true�� �����Ǿ����� Ȯ��
			bool game_cleared_result = game->getCleared();
			// Game ��ü ���ο��� ������ ������ ������ �ٲ������ Ȯ�� (������)
			int final_game_level = game->getLevel();



			// �ڡڡ� ���Ⱑ �߿�: Game ��ü�� Ŭ����Ǿ���, Game ��ü ���� ������ GameManager�� �������� ���ٸ�
			// (��, �������� �߻��ߴٸ�) GameManager�� ������ ������Ʈ�մϴ�.
			if (game_cleared_result && final_game_level > manager_level) { // Ŭ����Ǿ����� Ȯ��
				manager_level = final_game_level; // �ڡڡ� GameManager�� ������ Game ��ü�� ���� ������ ������Ʈ!;
			}
			else if (!game_cleared_result && final_game_level ==10) {
				printer.show_clear_screen(game->getScore());
			}
			else {
				break;
			}
			system("cls");


		}
	}

   
}