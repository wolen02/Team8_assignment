#include "Stage.h"

Stage::Stage():Stage(0,0,0)
{
}

Stage::~Stage()
{
}

Stage::Stage(int speed, int stick_rate, int clear_line) 
	:speed(speed), stick_rate(stick_rate), clear_line(clear_line)
{
}

int Stage::getSpeed()
{
	return speed;
}

int Stage::getStick_rate()
{
	return stick_rate;
}

int Stage::getClear_line()
{
	return clear_line;
}
