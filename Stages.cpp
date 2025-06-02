#include "Stages.h"

Stages::Stages() {
    stage_data[0].speed=40; //각 레벨 별 떨어지는 속도 지정
	stage_data[0].stick_rate=20;	
	stage_data[0].clear_line=2; //쉬운 확인을 위해 클리어해야하는 줄의 수 1로 변경
	stage_data[1].speed=38;
	stage_data[1].stick_rate=18;
	stage_data[1].clear_line=2;
	stage_data[2].speed=35;
	stage_data[2].stick_rate=18;
	stage_data[2].clear_line=2;
	stage_data[3].speed=30;
	stage_data[3].stick_rate=17;
	stage_data[3].clear_line=2;
	stage_data[4].speed=25;
	stage_data[4].stick_rate=16;
	stage_data[4].clear_line=2;
	stage_data[5].speed=20;
	stage_data[5].stick_rate=14;
	stage_data[5].clear_line=2;
	stage_data[6].speed=15;
	stage_data[6].stick_rate=14;
	stage_data[6].clear_line=2;
	stage_data[7].speed=10;
	stage_data[7].stick_rate=13;
	stage_data[7].clear_line=2;
	stage_data[8].speed=6;
	stage_data[8].stick_rate=12;
	stage_data[8].clear_line=2;
    stage_data[9].speed = 20;         // for testing purposes, speed is set to 20
	stage_data[9].stick_rate=11;
	stage_data[9].clear_line=2;
}

int Stages::get_clear_line(int level) {
	return stage_data[level].clear_line;
}

int Stages::get_stick_rate(int level) {
	return stage_data[level].stick_rate;
}

int Stages::get_speed(int level) {
	return stage_data[level].speed;
}
