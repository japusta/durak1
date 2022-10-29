#include "Table.h"
#include "TextureManager.h"


Table::Table(const char* texturename,int x, int y) 
{

	RectTexture = TextureManager::LoadTexture(texturename);
	xpos = x;
	ypos = y;
}

Table::~Table() 
{
	SDL_DestroyTexture(RectTexture);
}

void Table::Update()
{
	srcR.h = 96;
	srcR.w = 71;
	srcR.x = 0;
	srcR.y = 0;

	destR.h = 96;
	destR.w = 71;
	destR.x = xpos;
	destR.y = ypos;
}

void Table::Render()
{
	SDL_RenderCopy(Game::renderer, RectTexture, &srcR, &destR);
}