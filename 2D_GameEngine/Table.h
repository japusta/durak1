#pragma once
#include "Game.h"
#include "GameObject.h"



//There we have functions which draw a rectangles on the table
class Table {
public:
	Table(const char* texturename, int x, int y);
	~Table();
	void Update();
	void Render();
	bool isCardOn = false;
	bool isSecCardOn = false;
	
	GameObject* Card = nullptr;
	GameObject* CardOn = nullptr;
	int xpos, ypos;

private:
	SDL_Texture* RectTexture;
	SDL_Rect srcR,destR;
	
};