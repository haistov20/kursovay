#include "includes.h"
#include "bomerang.h"


Bomerang::Bomerang (Setup* passed_setup)
{
	setup = passed_setup;
	bomerang=new Sprite(setup->getRender(), "Data/img/boomerang.png", START_BOOMERANG, START_HERO_POSY+65, 20 *6 , 20*6 );
	
}


Bomerang::~Bomerang()
{
	delete bomerang;
}

void Bomerang::draw()
{
	bomerang->draw();
}

void Bomerang::drawFlip(double angle)
{
	SDL_Point centre = {10,10};
	bomerang->drawFlip(angle,&centre);
}

void Bomerang::setX(int x)
{
	bomerang->setX(x);
}

void Bomerang::setY(int y)
{
	bomerang->setY(y);
}

int Bomerang::getX()
{
	return bomerang->getX();
}

int Bomerang::getY()
{
	return bomerang->getY();
}

