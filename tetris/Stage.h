#pragma once
class Stage
{
private:
	int speed;
	int stick_rate;
	int clear_line;
public:
	Stage();
	~Stage();
	Stage(int speed, int stick_rate, int clear_line);
	int getSpeed();
	int getStick_rate();
	int getClear_line();
};

