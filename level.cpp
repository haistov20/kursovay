#include "includes.h"
#include "level.h"
#include <stdio.h>
#include <cstring>



Level::Level(Setup* passed_setup)
{
	dest = 0;
	lvl_num = 0;
	click = 0;
	setup = passed_setup;
	char str[30];
	for (int i = 0; i < 10; i++)
	{
		try_again[i] = true;
	}
	for (int i = 0; i < LVL; i++)
	{
		sprintf_s(str,27,"%s%i%s", "Data/img/level_",i, ".png");
		printf("%s\n", str);
		lvl[i] = new Sprite(setup->getRender(), str, 0, 0, SCREEN_W, SCREEN_H);
	}
	for (int i = 0; i < LAVA; i++)
	{
		lava[i] = new Sprite(setup->getRender(), "Data/img/lava.png", dest, LAVA_Y, 14 * 6, 20 * 6	);
		lava[i]->setUpAnimation(14, 1);
		dest += 180;
	}

	dest = 190;
	for (int i = 0; i < ARROW; i++)
	{
		arrow[i] = new Sprite(setup->getRender(), "Data/img/arrow.png", dest, START_ARROW_Y, 20 * 5, 20 * 5);
		dest += rand() % 300 + 170;
	}
	dest = 190;
	for (int i = 0; i < PLATFORM; i++)
	{
		platform[i] = new Sprite(setup->getRender(), "Data/img/platform.png", dest, START_PLATFORM_Y, 10 * 9, 10 * 5);
		platform[i]->setUpAnimation(11, 1);
		dest += 170;
	}

	dest = 20;
	for (int i = 0; i < FIRE; i++)
	{
		fire[i] = new Sprite(setup->getRender(), "Data/img/fire.png", dest, START_FIRE_Y, 20*5, 30*5);
		fire[i]->setUpAnimation(4, 1);
		dest += 430;
	}
	dest = 240;
	for (int i = 0; i < LEDDER; i++)
	{
		ledder[i] = new Sprite(setup->getRender(), "Data/img/ledder.png", dest, START_LEDDER_Y, 10 * 10, 45 * 5);
		dest += 240;
	}
	dest = 340;
	for (int i = 0; i < BOMB; i++)
	{
		bomb[i] = new Sprite(setup->getRender(), "Data/img/bomb.png", dest, START_BOMB_Y, 12 * 6, 20 * 6);
		bomb[i]->setUpAnimation(8, 1);
		dest += 480;
	}

	bomerang = new Bomerang(setup);
	ghost = new Sprite(setup->getRender(), "Data/img/ghost.png",540, START_HERO_POSY - 140, 20 * 7, 20 * 7);
	ghost->setUpAnimation(4, 1);

	spike = new  Sprite(setup->getRender(), "Data/img/spike_ceiling.png",0, SPIKE_POS_Y, SCREEN_W , SCREEN_H );

	player = new Player(setup);
	bat = new Sprite(setup->getRender(), "Data/img/bat.png", BAT1_START_X, BAT1_START_Y, 10*INCREASE_HERO_X, 12 * INCREASE_HERO_Y);
	bat->setUpAnimation(4, 1);

	boss = new Sprite(setup->getRender(), "Data/img/boss.png", START_BOSS_X, START_BOSS_Y, 28 * 7 , 35 * 6);
	boss->setUpAnimation(2, 1);
	hp_metr = new Sprite(setup->getRender(), "Data/img/force_meter.png", boss->getX() - 100, boss->getY() - 20, 200 , 30);
	for (int i = 0; i < HP; i++)
		hp[i] = new Sprite(setup->getRender(), "Data/img/red.png", hp_metr->getX() + 7, hp_metr->getY() + 5, 5 * 3, 3 * 5);
	timeCheck = SDL_GetTicks();
	dest = 300;
	for (int i = 0; i < ROCK; i++)
	{
		rock[i] = new Sprite(setup->getRender(), "Data/img/rock.png", dest, START_ROCK, 10 * 7, 10 * 7);
		dest += 140;
	}

	dest = 10;
	for (int i = 0; i < CLICK; i++)
	{
		you_click[i] = new Sprite(setup->getRender(), "Data/img/font.png", dest, 5, 30*1.25, 35*1.25);
		you_click[i]->setUpAnimation(10, 1);
		dest += 30;
	}

	bomerang_effect= Mix_LoadWAV("Data/audio/boomerang.wav");
	if (bomerang_effect == NULL) puts("Can`t find Data/audio/boomerang.wav");

	ghost_effect = Mix_LoadWAV("Data/audio/ghost.wav");
	if (ghost_effect == NULL) puts("Can`t find Data/audio/ghost.wav");

	hurt = Mix_LoadWAV("Data/audio/hurt.wav");
	if (hurt == NULL) puts("Can`t find Data/audio/hurt.wav");
	boss_dead = Mix_LoadWAV("Data/audio/boss_dead.wav");
	if (boss_dead == NULL) puts("Can`t find Data/audio/boss_dead.wav");

	jumpB = Mix_LoadWAV("Data/audio/boss_jump.wav");
	if (jumpB== NULL) puts("Can`t find Data/audio/boss_jump.wav");

	music = Mix_LoadMUS("Data/audio/theme.wav");
	if (music == NULL) puts("Can`t find Data/audio/theme.wav");
	Mix_PlayMusic(music, -1);

	vik = Mix_LoadMUS("Data/audio/victory.wav");
	if (vik == NULL) puts("Can`t find Data/audio/victory.wav");
	Victory = new Sprite(setup->getRender(), "Data/img/end.png", 0, 0, SCREEN_W, SCREEN_H);

	Mix_Volume(-1, MIX_MAX_VOLUME);
	Mix_VolumeMusic(MIX_MAX_VOLUME/3);
	flyUp = true;
	die = false;
	shoot = false;
	run = true;
}


Level::~Level()
{
	int i = 0;
	for (i = 0; i < LVL; i++)
		delete lvl[i];
	for (i = 0; i < LAVA; i++)
		delete lava[i];
	for (i = 0; i < PLATFORM; i++)
		delete platform[i];
	for (i = 0; i < ARROW; i++)
		delete arrow[i];
	for (i = 0; i < BOMB; i++)
		delete bomb[i];
	for (i = 0; i < LEDDER; i++)
		delete ledder[i];
	for (i = 0; i < HP; i++)
		delete hp[i];
	for (i = 0; i < FIRE; i++)
		delete fire[i];
	for (i = 0; i < CLICK; i++)
		delete you_click[i];
	for (i = 0; i < ROCK; i++)
		delete rock[i];
	delete bat;
	delete ghost;
	delete spike;
	delete hp_metr;
	delete Victory;
	delete bomerang;
	delete boss;
	delete player;
	Mix_FreeChunk(bomerang_effect);
	Mix_FreeChunk(ghost_effect);
	Mix_FreeChunk(hurt);
	Mix_FreeChunk(boss_dead);
	Mix_FreeChunk(jumpB);
	Mix_FreeMusic(music);
}

void Level::draw(int i)
{
	lvl[i]->draw();
	if (i)
	{
		for (int j = 0; j < LAVA; j++)
		{
			lava[j]->draw();
			if (lava[j]->playOne(0, 13, 100))
				lava[j]->setX(rand() % SCREEN_W);
				
		}

		for (int j = 0; j < FIRE; j++)
		{
			fire[j]->draw();
			fire[j]->playOne(0, 3, 60);
		}
		
	}	
	
}

void Level::update()
{
	static bool key_pressed = false;
	if (lvl_num < LVL)draw(lvl_num);
	if (player->getX() + 80 >= SCREEN_W) {
		if (lvl_num + 1 < LVL )
		{
			lvl_num++;
			player->setX(0);
			player->setY(START_HERO_POSY);
		}

	}
	if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN) //кол-во кликов
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			key_pressed = true;
	
	switch (lvl_num)
	{
	case 0:
		lvl_0();
		break;
	case 1:
		lvl_1();
		break;
	case 2:
		lvl_2();
		break;
	case 3:
		lvl_3();
		break;
	case 4:
		lvl_4();
		break;
	case 5:
		lvl_5();
		break;
	case 6:
		lvl_6();
		break;
	case 7:
		lvl_7();
		break;
	case 8:
		lvl_8();
		break;
	case 9:
		lvl_9();
		break;
	
	default:
		break;
	}
	if (player->getX() + 80 >= SCREEN_W  && lvl_num+1==LVL) victory();
	else if (key_pressed )
	{
		if (setup->getEvent()->type == SDL_MOUSEBUTTONUP && mousePos())
		{
			click++;
			key_pressed = false;
		}

	}
	if(!final) writeText(20, 10,50,33, 255, 255, 255);

}

void Level::lvl_0()
{
	static double angle = 0;
	static bool bom_fly = true, bat_die = false;
	static bool keyPressd = false, play_shot = true;
	if (try_again[0]) {
		angle = 0; bat_die = false; keyPressd = false; play_shot = true; try_again[0] = false;
	}
		player->udpate(2);
		if (!shoot)
		{
			bomerang->setX(player->getX() + 115);
			bomerang->draw();
		}
		else
		{
			bomerang->drawFlip(angle);
			if (bomerang->getX() - player->getX() <= 300 && bom_fly)
			{
				bomerang->setX(bomerang->getX() + 4);
				if (bomerang->getX() - bat->getX() >= 50)
				{
					//bom_fly = false;
					bat_die = true;
					
				}
			}
			else {
				bom_fly = false;
				if (bomerang->getX() - player->getX() >= 115) bomerang->setX(bomerang->getX() - 4);
				if (bomerang->getX() - player->getX() <= 115)
				{
					shoot = false;
					bom_fly = true;
					play_shot = true;
				}
			}
			angle += 15;
			if (angle >= 360) angle = 0;
		}
		if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
			if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			{
				keyPressd = true;
			}
				
		if (setup->getEvent()->type == SDL_MOUSEBUTTONUP && keyPressd)
		{
			shoot = true; keyPressd = false;
			if (play_shot)
			{
				Mix_PlayChannel(-1, bomerang_effect, 0);
				play_shot = false;
			}
		}
		if (bat_die)
		{
			bat->draw();
			if (bat->playOne(0, 3, 70))
			{
				bat->setPosition(GETOUT, GETOUT);
				bat_die = false;
			}
				
		}
		else
		{
			bat->draw();
			bat->playOne(0, 1, 200);
			if (timeCheck + 7 < SDL_GetTicks())
			{
				bat->setX(bat->getX() - 3);
				int polet = BAT1_START_X - bat->getX();
				if (!(polet % 6))
				{
					if (flyUp)
					{
						bat->setY(bat->getY() - 2);
						if (BAT1_START_Y - bat->getY() > 10) flyUp = !flyUp;
					}
					else
					{
						bat->setY(bat->getY() + 2);
						if (bat->getY() - BAT1_START_Y > 10) flyUp = !flyUp;
					}
				}
				timeCheck = SDL_GetTicks();
			}
		}
		if ((player->getX() + 50) - bat->getX() >= 0)die = true;
		else player->run(true, 1);

		if (player->getX() + 80 >= SCREEN_W) bat_die = false;
	if (player->die(die,lvl[0]))
	{
		bomerang->setX(player->getX() + 115);
		bat->setPosition(BAT1_START_X, BAT1_START_Y);
		die = false; bat_die = false; shoot = false; 
		lvl[6]->setY(0);
	}
}

void Level::lvl_1()
{
	int j = 0;
	player->udpate(0);
	for (int i = 0; i < ARROW; i++)
		arrow[i]->draw();
	for (int i = 0; i < ARROW; i++)
	{
		if (arrow[i]->getY() < SCREEN_H && arrow[i]->getX() - player->getX() <= 120) {
			j = i; // ближайшая стрела к игроку
			arrow[i]->setY(arrow[i]->getY() + 4);
			if(arrow[i]->getY() > 500) arrow[i]->setX(GETOUT);
			}	
	}
	player->run(run,1);

	if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
	{
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			run = false;
	}
	else if (setup->getEvent()->type == SDL_MOUSEBUTTONUP)
	{
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
		{
			run = true;
		}
	}

	if ((arrow[j]->getY() >= player->getY()) &&
		(arrow[j]->getX() - player->getX() <= 75) && (arrow[j]->getX() - player->getX() <= 160))
	{
		die = true; run = false;
	}
		

	if (player->die(die, lvl[1]))
	{
		dest = 190;
		for (int i = 0; i < ARROW; i++)
		{
			arrow[i]->setPosition(dest, START_ARROW_Y);
			dest += rand() % 200 + 140;
		}
		die = false;
		run = true;
		lvl[4]->setY(0);
	}
}

void Level::lvl_2()
{
	static int  k = 0;
	static int j = 0, form = -1;
	static bool draw = false, jump = false, key_pressed = false;
	if (try_again[2]) {
		k = 0; j = 0; form = -1;
		draw = false; jump = false; key_pressed = false; try_again[2] = false;
	}
	player->udpate(0);
	for (int i = 0; i < PLATFORM; i++)
	{
		platform[i]->draw();
		if (i > form) platform[i]->playOne(0, 0, 200);
	}
	for (int i = 0; i < PLATFORM; i++)
	{
if (platform[i]->getX() - player->getX() <= 140)
form = i;
	}
	if (!jump)
	{
		if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
		{
			if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			{
				jump = false;
				j++;
				if (j >= 14 && k < 6)
				{
					j = 0;
					k++; key_pressed = true;
				}
				if(k>0) draw = true;
			}
		}
	}

	if (setup->getEvent()->type == SDL_MOUSEBUTTONUP && key_pressed)
	{
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
		{
			draw = false; j = 0; key_pressed = false;
			if (k > 0) jump = true;
		}
	}
	if (player->jump(k, jump, draw, die) || die)
	{
		k = 0; jump = false;

	}

	if (!form)
	{
		if (player->getX() > 30 && player->getX() + 60 < platform[form]->getX() && player->getY() == START_HERO_POSY)
			die = true;
		else
		{
			if (player->getY() == START_HERO_POSY)
				if (platform[0]->playOne(0, 10, 130))  die = true; 
		}
	}
	else if (form > 0 && form + 1 != PLATFORM)
	{
		if (player->getX() - platform[form - 1]->getX() > 30 && player->getX() + 60 < platform[form]->getX() && player->getY() == START_HERO_POSY)
			die = true;
		else {
			if (player->getY() == START_HERO_POSY)
				if (platform[form]->playOne(0, 10, 130)) die = true;


		}
	}

	else if (form + 1 == PLATFORM)
	{
		if (platform[form]->getX() - player->getX() > 80 && player->getY() == START_HERO_POSY) die = true;
		else if (player->getX() - platform[form]->getX() > 20 && player->getX() - platform[form]->getX() < 100 && player->getY() == START_HERO_POSY)
			die = true;
		else if (player->getY() == START_HERO_POSY && player->getX() - platform[form]->getX() < 100)
			if (platform[form]->playOne(0, 10, 130)) die = true;

	}

	if (player->die(die, lvl[2]))
	{
		dest = 190;
		for (int i = 0; i < PLATFORM; i++)
		{
			platform[i]->setX(dest);
			dest += 170;
		}
		die = false; form = -1;
		k = 0;
	}

}

void Level::lvl_3()
{
	bool jump = false;
	static bool keyPressd = false, babam = false, play_effect = true,fly_ghost = true;
	static int boom = -1;
	if (try_again[3]) {
		keyPressd = false; babam = false; play_effect = true; fly_ghost = true; boom = -1; try_again[3] = false;
	}
	int j = 0;
	ghost->draw();
	
	if (timeCheck + 15 < SDL_GetTicks())
	{
		if (fly_ghost)
		{
			ghost->setY(ghost->getY() - 1);
			if (START_HERO_POSY - 140 - ghost->getY() >= 20) fly_ghost = false;
		}
		else
		{
			ghost->setY(ghost->getY() + 1);
			if (START_HERO_POSY - 140 - ghost->getY() < 0) fly_ghost = true;
		}
		timeCheck = SDL_GetTicks();
	}

	if (play_effect && ghost->getX() - player->getX() <= 200)
	{
		Mix_PlayChannel(-1, ghost_effect, 0);
		play_effect = false;
	}

	if (player->getX() - ghost->getX() <= SCREEN_W && player->getX() - ghost->getX() >= -150)
	{
		ghost->playOne(3, 3, 75);
		if (ghost->getX() - player->getX() <= 60 && player->getX() - ghost->getX() <= 60 && player->getY() == START_HERO_POSY - 140)
			die = true;

	}
	else ghost->playOne(0, 0, 200);
	for (int i = 0; i < LEDDER; i++)
	{
		ledder[i]->draw();
	}
	for (int i = 0; i < BOMB; i++)
	{
		bomb[i]->draw();
		if (i > boom)bomb[i]->playOne(0, 0, 200);
	}
	player->udpate(0);
	if(!die)player->run(true,1);

	if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
	{
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			keyPressd = true;
			
	}

	if (setup->getEvent()->type == SDL_MOUSEBUTTONUP  && keyPressd){
		jump = !jump; keyPressd = false; /*MAYBE FIX*/
	}
			
	if (jump)
	{
		for (int i = 0; i < LEDDER; i++)
			if (ledder[i]->getX() - player->getX() <= 70)
				j = i;

			if (ledder[j]->getX() - player->getX() <= 50 && player->getX() - ledder[j]->getX() < 40 && player->getY() == START_HERO_POSY)
			{
				player->setY(START_HERO_POSY - 140);
			}
			else if (ledder[j]->getX() - player->getX() <=50 && player->getX() - ledder[j]->getX() < 40 && player->getY() == (START_HERO_POSY - 140))
				player->setY(START_HERO_POSY );
	}
	for (int i = 0; i < BOMB; i++)
		if (bomb[i]->getX() - player->getX() <= 70 && player->getX() - bomb[i]->getX() <=20 && player->getY() <= bomb[i]->getY() &&
			 bomb[i]->getY() - player->getY() <=60)
			{
				boom = i; die = true; babam = true;
				
			}
	if(boom >= 0 && babam) bomb[boom]->playOne(1, 7, 35);
	if (player->die(die, lvl[3]))
	{
		boom = -1; die = false;
		lvl[8]->setY(0);
		play_effect = true;
	}
	
}

void Level::lvl_4()
{
	
	static bool first = true;
	if (try_again[4])
	{
		first = true; try_again[4] = false;
	}
	if (first)
	{
		int dest = 190;
		for (int i = 0; i < ARROW; i++)
		{
			arrow[i]->setPosition(dest, START_ARROW_Y);
			dest += rand() % 300 + 170;
		}
		bat->setPosition(BAT1_START_X - 200, BAT1_START_Y - 45);
		first = false;
	}
	lvl_1();
	bat->playOne(0, 1, 200);
	bat->draw();
	if (timeCheck + 15 < SDL_GetTicks())
	{
		bat->setX(bat->getX() - 3);
		int polet = BAT1_START_X - bat->getX() - 200;
		if (!(polet % 6))
		{
			if (flyUp)
			{
				bat->setY(bat->getY() - 2);
				if (BAT1_START_Y - bat->getY() >= 55) flyUp = !flyUp;
			}
			else
			{
				bat->setY(bat->getY() + 2);
				if (bat->getY() - BAT1_START_Y  >= -35) flyUp = !flyUp;
			}
		}
		timeCheck = SDL_GetTicks();
	}
	if ((player->getX() + 50) - bat->getX() >= 0 && player->getY() - bat->getY() <= 40  && bat->getX() - (player->getX()- 10) >=0) die = true;
	if (die) {
		bat->setPosition(BAT1_START_X - 200, BAT1_START_Y - 30);
		if (player->die(die, lvl[4]))
			die = false;		
			
	}
	

}

void Level::lvl_5()
{
	static bool keyPressd = false;
	static double  i = 0;
	if (try_again[5]) {
		keyPressd = false;  i = 0; try_again[5] = false;
	}
	spike->draw();
	player->udpate(0);
	if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
	{
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			keyPressd = true;
	}
	if (keyPressd)
	{
		if (setup->getEvent()->type == SDL_MOUSEBUTTONUP) {
			i += 0.5; // С каждым нажатием перемещение увеличивается
			keyPressd = false; /*MAYBE FIX*/
		}
	}
	else if (i >= 0)i -= 0.02;

	if (timeCheck + 10 < SDL_GetTicks()) //Плавноге движение
	{
		for (int j = 0; j < i; j++)
		{
			player->setX(player->getX() + 1);
		}
		timeCheck = SDL_GetTicks();
		spike->setY(spike->getY() + 1);
	}
	if (player->getY() - spike->getY() <= 40 + (-SPIKE_POS_Y))
	{
		die = true;
		i = 0;
	}
	if (player->die(die, lvl[5]))
	{
		die = false;  i = 0;
		spike->setY(SPIKE_POS_Y);
	}


}

void Level::lvl_6()
{
	static bool first = true;
	static int boom = -1;
	if (try_again[6]) {
		first = true; boom = -1; try_again[6] = false;
		bomerang->setX(player->getX() + 115);
	}
	if (first)
	{
		bat->setPosition(BAT1_START_X, BAT1_START_Y);
		first = false;
	}
	lvl_0();
	for (int i = 0; i < BOMB; i++)
	{
		bomb[i]->draw();
		if (i > boom) bomb[i]->playOne(0, 0, 200);
	}
	for (int i = 0; i < BOMB; i++)
	{
		if (bomb[i]->getX() - player->getX() <= 70 && player->getX() - bomb[i]->getX() <= 60)
		{
			die = true;  boom = i;
		}
		else if (bomerang->getX() - bomb[i]->getX() >= 50 && bomerang->getX() - bomb[i]->getX() <= 60)
		{
			boom = i;
		}
	}
	if (boom>-1) if (bomb[boom]->playOne(1, 7, 35)) bomb[boom]->setX(GETOUT);
	if (die)
	{
		player->die(die, lvl[6]);
		boom = -1; dest = 340;
		for (int i = 0; i < BOMB; i++)
		{
			bomb[i]->setX(dest); dest += 480;
		}
	}
}

void Level::lvl_7()
{
	player->udpate(0);
	int here = 0; // 1st bomb
	static bool first = true, key_pressed = false, play_effect=true;
	static int  k = 0, j = 0;
	static bool draw = false, jump = false, boom = false;
	if (try_again[7]) {
		first = true; key_pressed = false; play_effect = true;
		k = 0; j = 0;
		draw = false; jump = false; boom = false;
		try_again[7] = false;
		player->jump(0, false, false, true);
	}
	if (first)
	{
		bat->setPosition(BAT1_START_X - 240, BAT1_START_Y );
		ghost->setPosition(BAT1_START_X - 35, BAT1_START_Y + 30);
		bomb[here]->setX(BAT1_START_X - 470);
		first = false; boom = false; play_effect = true;
	}
	if (!die) player->run(true,1);
	ghost->draw();
	bat->draw();
	bat->playOne(0, 1, 200);


	if (timeCheck + 15 < SDL_GetTicks())
	{
		bat->setX(bat->getX() - 3);
		int polet = BAT1_START_X - bat->getX();
		if (!(polet % 6))
		{
			if (flyUp)
			{
				bat->setY(bat->getY() - 2);
				ghost->setY(ghost->getY() - 1);
				if (BAT1_START_Y - bat->getY() > 10) flyUp = !flyUp;
			}
			else
			{
				bat->setY(bat->getY() + 2);
				ghost->setY(ghost->getY() + 1);
				if (bat->getY() - BAT1_START_Y > 10) flyUp = !flyUp;
			}
		}
		timeCheck = SDL_GetTicks();
	}
	if (bat->getX() - player->getX() <= 30 && player->getX() - bat->getX() <= 20 && bat->getY() - player->getY() <= 90) {
		die = true; 
	}

	if (!jump)
	{
		if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
		{
			if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
			{
				jump = false; 
				j++;
				if (j >= 14 && k < 6)
				{
					j = 0; key_pressed = true;
					k++;
				}
				if (k>0) draw = true;
			}

		}
	}
	if (setup->getEvent()->type == SDL_MOUSEBUTTONUP && key_pressed){
		if (setup->getEvent()->button.button == SDL_BUTTON_LEFT){
				draw = false; j = 0; key_pressed = false;
				if (k > 0) jump = true;
		}
	}
	if (bomb[here]->getX() - player->getX() <= 50 && bomb[here]->getY() - player->getY() <= 100 && player->getX() - bomb[here]->getX() <=10)
	{
		die = true; boom = true; 
	}
	if (!boom) bomb[here]->playOne(0, 0, 200);
	else bomb[here]->playOne(0, 7, 45);
	bomb[here]->draw();
	if (player->jump(k, jump, draw, die) || die)
	{
		k = 0; jump = false;

	}
	if (player->getX() - ghost->getX() <= SCREEN_W && player->getX() - ghost->getX() >= -150)
	{
		ghost->playOne(3, 3, 45);

		if (ghost->getX() - player->getX() <= 50 && ghost->getY() - player->getY() <= 110 && player->getX() - ghost->getX() <= 20) {
			die = true; 
		}

	}
	else if (ghost->getX() - player->getX() <= 150)
	{
		ghost->playOne(0, 3, 75);

	}
	else ghost->playOne(0, 0, 200);

	if (play_effect && ghost->getX() - player->getX() <= 250)
	{
		Mix_PlayChannel(-1, ghost_effect, 0);
		play_effect = false;
	}

	if (player->die(die, lvl[7]))
	{
		die = false;
		k = 0;
		first = true;
	}

	
}

void Level::lvl_8()
{
	static bool first = true;
	int here = 1; // 1st bomb
	int bat_x = 500, bat_y = 245;
	int side = 1;
	static double speed = 3;
	if (try_again[8]) {
		first = true; speed = 3;
		try_again[8] = false;
	}
	if (first)
	{
		bat->setPosition(BAT1_START_X - 440, BAT1_START_Y + 75);
		ghost->setX(GETOUT);
		bomb[here]->setY(245);
		dest = 340;
		for (int i = 0; i < BOMB; i++)
		{
			bomb[i]->setX(dest);
			dest += 200;
		}
		bat->setPosition(bat_x, bat_y);
		side = 1;
		speed = 3;
		first = false;
	}
	if (player->getX() >= ledder[1]->getX())
	{
		bat_x = 400, bat_y = BAT1_START_Y; side = -1;
	}
	if (player->getX() == ledder[1]->getX())
	{
		side = -2;
		bat->setPosition(bat_x, bat_y);
	}
	if (side == -1) speed += 0.015;
	if (timeCheck + 15 < SDL_GetTicks())
	{
		bat->setX(bat->getX() - (speed*side));
	
			if (flyUp)
			{
				bat->setY(bat->getY() - 2);
				if (bat_y - bat->getY() > 10) flyUp = !flyUp;
			}
			else
			{
				bat->setY(bat->getY() + 2);
				if (bat->getY() - bat_y > 10) flyUp = !flyUp;
			}
		timeCheck = SDL_GetTicks();
	}
	lvl_3();
	bat->draw();
	bat->playOne(0, 1, 200);
	if ((player->getX() + 50) - bat->getX() >= 0 && (player->getX() + 40) - bat->getX() <= 20  &&  
		player->getY() <= bat->getY() && bat->getY() - player->getY() <= 80) die = true;
	if (die)
	{
		player->die(die, lvl[8]);
		first = true;

	}
	
}

void Level::lvl_9() 
{
	static double angle = 0;
	static bool first = true;
	static int side = -1, i = 0;
	static bool keyPressd = false, play_shot = true;
	static bool bom_fly = true, boss_run = false,
		bossComeToMe = false, boss_jump = true, play = true;
	static int life_bar = HP, num_jump = 0;
	static bool rock_fall[ROCK] = { 0 };
	if (try_again[9]) {
		angle = 0;  first = true;
		side = -1; i = 0;
		keyPressd = false; play_shot = true;
		bom_fly = true; boss_run = false;
		bossComeToMe = false; boss_jump = true; play = true;
		life_bar = HP; num_jump = 0;
		for (int i = 0; i < ROCK; i++)
			rock_fall[i] = 0;
		try_again[9] = false;
	}
	if (life_bar)
	{
		if (play_shot)
		{
			Mix_PlayChannel(-1, bomerang_effect, 0);
			play_shot = false;
		}
		if (first) // старт/рестарт уровня
		{
			player->setX(100);
			bomerang->setX(player->getX() + 115);
			boss->setPosition(START_BOSS_X, START_BOSS_Y);
			first = false;
			for (int j = 0; j < ROCK; j++)
			{
				rock[j]->setY(START_ROCK);
				rock_fall[j] = false;
			}
			num_jump = 0;
		}
		hp_metr->setPosition(boss->getX(), boss->getY() - 20);  //Здоровье босс
		hp_metr->draw();
		for (int i = 0; i < life_bar; i++) {
			hp[0]->setPosition(hp_metr->getX() + 9, hp_metr->getY() + 8);
			if (i > 0) hp[i]->setPosition(hp[i - 1]->getX() + 14, hp[i - 1]->getY());
			hp[i]->draw();
		}

		for (int j = 0; j < ROCK; j++) // Падение камней и столкновение с ними
		{
			if (rock[j]->getX() - player->getX() <= 100 && player->getX() - rock[j]->getX() <= 30)
				rock_fall[j] = true;
			if(rock_fall[j]) rock[j]->setY(rock[j]->getY() + 3); 
			rock[j]->draw();
			if (rock[j]->getX() - player->getX() <= 70 && player->getX() - rock[j]->getX() <= 0 && player->getY() - rock[j]->getY() <= 20)
				die = true;
			if (rock[j]->getY() >= 500)
			{
				rock[j]->setY(START_ROCK);
				rock_fall[j] = false;
			}
		}

		boss->playOne(0, 1, 200);
		boss->draw();
		player->udpate(2);
		if (!die) player->run(true, pow(side, i));
		if (!bossComeToMe && num_jump < 2) //прыжок 
		{
			if (timeCheck + 4 < SDL_GetTicks())
			{
				if (boss_jump) {
					boss->setY(boss->getY() - 1);
					if (START_BOSS_Y - boss->getY() >= 40)
					{
						Mix_PlayChannel(-1, jumpB, 0);
						boss_jump = !boss_jump;
					}
				}
				else {
					boss->setY(boss->getY() + 2);
					if (START_BOSS_Y <= boss->getY())
					{
						boss_jump = !boss_jump;
						num_jump++;
					}
				}
				timeCheck = SDL_GetTicks();
			}
		}
		if (bomerang->getX() - boss->getX() >= 40) 
		{										
			shoot = true;		// попадание по боссу	
			Mix_PlayChannel(-1, hurt, 0);
			bossComeToMe = true; 
			boss->setY(START_BOSS_Y);
		}
		if ((timeCheck + 10 < SDL_GetTicks()) && bossComeToMe)
		{
			if (boss_run)
			{
				boss->setX(boss->getX() - 2);
				if (START_BOSS_X - boss->getX() >= 80)
					boss_run = false;
			}
			else
			{
				boss->setX(boss->getX() + 2);
				if (boss->getX() >= START_BOSS_X) {
					boss_run = true;
					bossComeToMe = false;
				}

			}
			timeCheck = SDL_GetTicks();
		}

		if (setup->getEvent()->type == SDL_MOUSEBUTTONDOWN && mousePos())
		{
			if (setup->getEvent()->button.button == SDL_BUTTON_LEFT)
				keyPressd = true;
		}

		if (setup->getEvent()->type == SDL_MOUSEBUTTONUP && keyPressd){
			i++; keyPressd = false;
			num_jump = 0;
		}
		bomerang->drawFlip(angle);
		if (bomerang->getX() - player->getX() <= 300 && bom_fly)
		{
			bomerang->setX(bomerang->getX() + 3);
			if (bomerang->getX() - boss->getX() >= 45 && bomerang->getX() - boss->getX() <= 50)
			{
				bom_fly = false;
				if (bomerang->getX() - player->getX() >= 130) 
					life_bar--;
			}
		}
		else {
			bom_fly = false;
			if (bomerang->getX() - player->getX() >= 115) bomerang->setX(bomerang->getX() - 3);
			if (bomerang->getX() - player->getX() <= 115)
			{
				shoot = false;
				bom_fly = true;
				play_shot = true;
			}
		}
		angle += 13;
		if (angle >= 360) angle = 0;

		if (player->getX() < 80 || boss->getX() - player->getX() <= 85) die = true;

		if (player->die(die, lvl[9]))
		{
			life_bar = HP;
			first = true;
			die = false;
			i = 0;
		}
	}
	else
	{	
		if (play) {
			Mix_PlayChannel(-1, boss_dead, 0);
			play = false;
		}
		boss->setY(boss->getY() + 1);
		boss->playOne(0, 1, 200);
		boss->draw();
		player->udpate(0);
		player->draw();
		if (boss->getY() >= SCREEN_H+70) 
			player->run(true, 1);
	}
		
}

void Level::victory()
{
	
	if (try_again[1])
	{
		Mix_PlayMusic(vik, -1);
		remove("Data/checkpoint.bin");
		final = true;
		try_again[1] = false;
	}
	Victory->draw();
	writeText(723,330,67,51, 193,0,32);

}


void Level::writeText(int x, int y,int h,int w,int r,int g,int b)
{
	TTF_Font *gFont = NULL;
	gFont = TTF_OpenFont("Data/font.ttf", 28);
	if (gFont == NULL) {
		printf("Can`t open ttf %s\n", TTF_GetError());
	}
	SDL_Color textColor = { r, g, b, 255 };
	char str[5];
	sprintf_s(str, "%d", click);
	SDL_Rect dest;
	dest.h = h; dest.w = w*strlen(str); dest.y = y; dest.x = x;
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(gFont, str, textColor); //Место
	SDL_Texture* mTexture = SDL_CreateTextureFromSurface(setup->getRender(), textSurface);
	SDL_RenderCopy(setup->getRender(), mTexture, NULL, &dest);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);
	TTF_CloseFont(gFont);
	gFont = NULL;
}

bool Level::mousePos() // Если мышь не на кнопках 
{
	int x = 0, y = 0;
	if(y = setup->getEvent()->motion.y <= 57) return false;
	return true;
}


