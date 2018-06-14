#pragma once
#include "sprite.h"
#include "setup.h"
class Bomerang  {
public:
	Bomerang(Setup* passed_setup);
	~Bomerang();
	void draw();
	void drawFlip(double angle);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
private:
	Sprite* bomerang;
	Setup* setup;
	
};

