#include "GameManager.h"
#include "Normal.h"
#include "Reverse.h"
#include <iostream>

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


    while (true) {

        int level = input_level();
        system("cls");

        Game* game = nullptr;
        if (level == 0 || level == 3 || level == 6)
            game = new Reverse();
        else
            game = new Normal();
        std::cout << level;

        game->setLevel(level);
        game->run();

        system("cls");
    }
}
