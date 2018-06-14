#pragma once
class Setup
{
public:
	Setup(bool* quit);
	~Setup();
	SDL_Renderer *getRender();
	SDL_Event *getEvent();

	void begin();
	void end();
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event* event;
};

