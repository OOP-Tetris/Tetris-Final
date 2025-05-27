#pragma once
#include "Stage.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Stages {
private:
    STAGE stage_data[10];
public:
    Stages();
    int get_clear_line(int level);
    int get_stick_rate(int level);
    int get_speed(int level);
};

