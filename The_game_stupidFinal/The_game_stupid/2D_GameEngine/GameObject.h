#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "DeckObject.h"



class GameObject 
{
public:
	GameObject(Card cardName, int x, int y,bool isBot);
	~GameObject();

	void UpdateJust();
	void UpdateMoving();
	void FixCard(int x,int y);
	void Render();

	int xpos, ypos;
	int curPosX, curPosY;
	bool isOnTable = false;
	bool Bot;
	Card card;
private:
	SDL_Texture* objTexture;
	SDL_Rect srcR, destR; 
};