#include "includes.h"
#include "player.h"


Player::Player()
{
}

Player::Player(Setup* passed_setup)
{
	setup = passed_setup;
	try_again[0] = true;
	try_again[1] = true;
	myHero = new Sprite(setup->getRender(), "Data/img/hero.png", 0, START_HERO_POSY, 19 * INCREASE_HERO_Y, 18 * INCREASE_HERO_X);
	myHero->setUpAnimation(6, 3);
	meter = new Sprite(setup->getRender(), "Data/img/force_meter.png", getX() + 40, getY() - 20, (13 * 7) - 3, 4 * 5);
	for (int i = 0; i < 6; i++)
		red[i] = new Sprite(setup->getRender(), "Data/img/red.png", meter->getX() + 7, meter->getY() + 5, 5 * 5, 2 * 5);
	timeCheck = SDL_GetTicks();
	lvl_num = 0;
	die_effect= Mix_LoadWAV("Data/audio/dead.wav ");
	if (die_effect == NULL) puts("Can`t open Data/audio/dead.wav");
	jump_effect = Mix_LoadWAV("Data/audio/Jump.wav ");
	if (die_effect == NULL)  puts("Can`t open Data/audio/Jump.wav");
	Mix_VolumeChunk(jump_effect, MIX_MAX_VOLUME / 2);

}


Player::~Player()
{
	delete myHero;
	delete meter;
	for (int i = 0; i < 6; i++)
		delete red[i];
	Mix_FreeChunk(die_effect);
	Mix_FreeChunk(jump_effect);
}

void Player::draw()
{
	myHero->draw();
}

void Player::udpate(int i)
{
	double angle = 0;
	myHero->playAnimation(0, 1, i, 200);
	myHero->draw();

}

int Player::getX()
{
	return myHero->getX();
}

int Player::getY()
{
	return myHero->getY();
}

void Player::setX(int x)
{
	myHero->setX(x);
}

void Player::setY(int y)
{
	myHero->setY(y);
}

bool Player::die(bool die, Sprite* passed_sprite)
{
	map = passed_sprite;
	static bool shake = true;
	static int shake_num = 0, play_effect = true;
	if (try_again[0]) {
		shake = true; shake_num = 0; play_effect = true;
		try_again[0] = false;
	}
	if (die)
	{
		if (play_effect)
		{
			Mix_PlayChannel(-1, die_effect, 0);
			play_effect = false;
		}
		if (shake && shake_num <= 3)
		{
			map->setY(map->getY() + 2);
				if (map->getY() >= 10) shake = false;
		}
		else if (shake_num < 3)
		{
			map->setY(map->getY() - 2);
			if (map->getY() <= -10)
			{
				shake = true; shake_num++;
			}

		}
		if (myHero->playAnimation(0, 5, 1, 75) )
		{
			myHero->setPosition(0, START_HERO_POSY);
			map->setY(0);
			shake_num = 0; play_effect = true;
			return true;
		} 	
	}
	
	return false;
}

void Player::run(bool run,int side)
{
	if (run)
	{
		if (timeCheck + 10 < SDL_GetTicks())
		{
			myHero->setX(myHero->getX() + (2*side));
			timeCheck = SDL_GetTicks();
		}
	}
}

bool Player::jump(int k, bool jump,bool draw,bool restart)
{	

	static bool do_it = true, play_effect = true;
	if (try_again[1]) {
		do_it = true; play_effect = true;
		try_again[1] = false;
	}
	if (restart)
	{
		do_it = true;
		play_effect = true;
		jump = false;
	}
	int dest = (25 * k);
	if (draw)
	{
		meter->setPosition(getX() + 40, getY() - 20);
		meter->draw();
		red[0]->setPosition(meter->getX() + 7, meter->getY() + 5);
		for (int i = 0; i < k; i++)
		{
			if (i != 0) red[i]->setPosition(red[i - 1]->getX() + 10, red[i - 1]->getY());
			red[i]->draw();
		}
	}
	if (jump) {
		if (play_effect) {
			Mix_PlayChannel(-1, jump_effect, 0);
			play_effect = false;
		}
		if (do_it)
		{
			if (START_HERO_POSY - getY() >= dest) do_it = false;
			else {
				if (timeCheck + 4 < SDL_GetTicks())
				{
					setY(getY() - 3);
					setX(getX() + 2);
					timeCheck = SDL_GetTicks();
				}
				
			}
			
			
		}
		else {
			if (START_HERO_POSY - getY() <= 0)
			{
				do_it = true; play_effect = true;
				return true;
			}
			else
			{
				if (timeCheck + 4 < SDL_GetTicks())
				{
					setY(getY() + 3);
					setX(getX() + 2);
					timeCheck = SDL_GetTicks();
				}
				
			}
			
		}
	}

	return false;
	
}



