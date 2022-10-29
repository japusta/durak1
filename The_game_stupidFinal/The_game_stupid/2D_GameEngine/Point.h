#pragma once
#include "Game.h"
class Point
{
public:
	Point();
	~Point();

	void update(int pos);
	void render();
private:
	SDL_Texture* objTexture;
	SDL_Rect srcR, destR;
};
