#include "Normal.h"
#include "Reverse.h"
#include "Printer.h"
#include <iostream>
#include "GameManager.h"

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
    system("mode con cols=120 lines=50");
	GameManager manager;
    manager.run();

	return 0;
}

