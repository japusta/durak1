#include "Point.h"
#include "TextureManager.h"

Point::Point()
{

	objTexture = TextureManager::LoadTexture("bitmaps/point.bmp");

}

Point::~Point()
{
}

void Point::update(int pos)
{
	srcR.h = srcR.w = 40;
	srcR.x = srcR.y = 0;

	destR.h = destR.w = 40;
	if (pos == 0) {
		destR.x = 10;
		destR.y = 10;
	}
	else{
		destR.x = 10;
		destR.y = 520;
	}
}

void Point::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcR, &destR);
}
