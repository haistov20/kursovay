#include "includes.h"
#include "sprite.h"
#include "setup.h"

Sprite::Sprite(SDL_Renderer* passed_render,std::string FilePath, int x, int y, int w, int h)
{
	render = passed_render;
	image = NULL;
	image = IMG_LoadTexture(render, FilePath.c_str());
	if (!image) printf("Error: Cant load image %s - %s\n", FilePath.c_str(), SDL_GetError);

	SDL_QueryTexture(image, NULL, NULL, &img_w, &img_h);

	rect.x = x; rect.y = y;
	rect.h = h; rect.w = w;

	crop.x = 0; crop.y = 0; crop.h = img_h; crop.w = img_w;

	currentFrame = 0;
	timeCheck = 0;
}


Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::draw()
{
	SDL_RenderCopy(render, image, &crop, &rect);
}

void Sprite::drawFlip(double angle , SDL_Point* center)
{
	SDL_RenderCopyEx(render, image, &crop, &rect,angle, center,SDL_FLIP_NONE);
}

void Sprite::setX(int x)
{
	rect.x = x;
}

void Sprite::setY(int y)
{
	rect.y = y;
}

void Sprite::setPosition(int x, int y)
{
	rect.x = x; rect.y = y;
}

int Sprite::getX()
{
	return rect.x;
}

int Sprite::getY()
{
	return rect.y;
}

bool Sprite::playOne(int beginFrame, int endFrame, float speed)
{
	bool flag = false; // прохождение 1й анимации
	if (timeCheck + speed < SDL_GetTicks())
	{
		if (endFrame <= currentFrame)
		 {
			 currentFrame = beginFrame;
			 flag = true;
		 }	
		else
		{
			currentFrame++;
			flag = false;
		}
		if(currentFrame == 0) crop.x = 0;
		else crop.x = currentFrame*(img_w / amount_frameX);
		crop.y = 0;
		crop.w = img_w / amount_frameX;
		crop.h = img_h / amount_frameY;
		timeCheck = SDL_GetTicks();
	}
	return flag;
}

void Sprite::setUpAnimation(int passed_amount_frameX, int passed_amount_frameY)
{
	amount_frameX = passed_amount_frameX;
	amount_frameY= passed_amount_frameY;
}

bool Sprite::playAnimation(int beginFrame, int endFrame, int row, float speed)
{
	bool flag = false; // прохождение 1й анимации
	if (timeCheck + speed < SDL_GetTicks())
	{
		if (endFrame <= currentFrame)
		{
			currentFrame = beginFrame;
			flag = true;
		}
		else
		{
			currentFrame++;
			flag = false;
		}
		crop.x = currentFrame*(img_w / amount_frameX -1);
		crop.y = row*(img_h / amount_frameY -2);
		crop.w = img_w / amount_frameX;
		crop.h = img_h / amount_frameY;
		timeCheck = SDL_GetTicks();
	}

	return flag;
}

