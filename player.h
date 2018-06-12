#pragma once
#include "sprite.h"
#include "setup.h"
#include "bomerang.h"
class Player
{
public:
	Player();
	Player(Setup* passed_setup);
	~Player();
	void draw();
	void udpate(int i);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	bool die(bool die, Sprite* passed_sprite);
	void run(bool run,int side);
	bool jump(int k,bool jump,bool draw, bool restart);
private:
	Sprite* myHero;
	Setup* setup;
	Sprite* map;
	Sprite* meter;
	Sprite* red[6];
	Mix_Chunk *die_effect= NULL;
	Mix_Chunk *jump_effect = NULL;
	int timeCheck;
	int lvl_num;
	bool try_again[2];

};

