#pragma once
class Sprite
{
public:
	Sprite(SDL_Renderer* passed_render, std :: string FilePath, int x, int y, int w, int h);
	~Sprite();
	void draw();
	void drawFlip(double angle , SDL_Point* centre);
	void setX(int x);
	void setY(int y);
	void setPosition(int x,int y);
	int getX();
	int getY();
	bool playOne(int beginFrame, int endFrame,  float speed);
	void setUpAnimation(int passed_amount_frameX,int passed_amount_frameY);
	bool playAnimation(int beginFrame, int endFrame, int row, float speed);
private:
	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;
	SDL_Renderer* render;
	int img_w;
	int img_h;
	int currentFrame;
	int timeCheck;

	int amount_frameX;
	int amount_frameY;

};

