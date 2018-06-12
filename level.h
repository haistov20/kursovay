#pragma once
#include "sprite.h"
#include "setup.h"
#include "player.h"
#include "bomerang.h"



class Level
{
public:
	Level(Setup* passed_setup);
	~Level();
	int click, lvl_num;
	bool final = false;
	void draw(int i);
	void update();
	void lvl_0();
	void lvl_1();
	void lvl_2();
	void lvl_3();
	void lvl_4();
	void lvl_5();
	void lvl_6();
	void lvl_7();
	void lvl_8();
	void lvl_9();
	void victory();
	void writeText(int x, int y,int h, int w, int r, int g, int b);
	bool mousePos();
private:
	bool try_again[10];
	Sprite* lvl[LVL], *lava[LAVA], *fire[FIRE], *you_click[CLICK];
	//LVL 1
	Sprite* bat;
	Bomerang* bomerang;
	//LVL 2
	Sprite* arrow[ARROW];
	//LVL 3
	Sprite* platform[PLATFORM];
	//LVL 4
	Sprite *ledder[LEDDER], *bomb[BOMB], *ghost;
	// LVL 6
	Sprite* spike;
	// LVL 10
	Sprite* boss, *hp_metr, *hp[HP], *rock[ROCK], *Victory;
	/////////////////
	Player* player;
	Setup* setup;
	Mix_Music *music = NULL, *vik = NULL;
	Mix_Chunk *bomerang_effect = NULL;
	Mix_Chunk *ghost_effect = NULL;
	Mix_Chunk *hurt = NULL;
	Mix_Chunk *boss_dead = NULL;
	Mix_Chunk *jumpB = NULL;
	int timeCheck, dest;
	bool flyUp; // Движение летуч. мыши
	bool die, shoot, run;

};

