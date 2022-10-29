#include "GameObject.h"

GameObject::GameObject(Card cardName, int x, int y, bool isBot)
{
	card = cardName;
	if (card.value < 10) {
		char TextureName[16] = { 'b','i','t','m','a','p','s','/',' ','-',' ','.','b','m','p','\0' };
		TextureName[8] = card.suit + '0';
		TextureName[10] = card.value + '0';
		objTexture = TextureManager::LoadTexture(TextureName);
	}
	else {
		char TextureName[17] = { 'b','i','t','m','a','p','s','/',' ','-','1',' ','.','b','m','p','\0' };
		TextureName[8] = card.suit + '0';
		TextureName[11] = (card.value % 10) + '0';
		objTexture = TextureManager::LoadTexture(TextureName);
	}
	Bot = isBot;
	xpos = x;
	ypos = y;

}
GameObject::~GameObject(){
	SDL_DestroyTexture(objTexture);
}

void GameObject::UpdateJust() {
	if (!Bot) {
		srcR.h = 96;
		srcR.w = 71;
		srcR.x = 0;
		srcR.y = 0;

		if (!isOnTable) {
			SDL_GetMouseState(&curPosX, &curPosY);
			if (ypos > 484 &&
				curPosX > destR.x && curPosX<destR.x + 71 &&
				curPosY > destR.y && curPosY < destR.y + 96) {
				ypos--;
			}
			else if (ypos < 520) {
				ypos++;
			}
		}

		destR.h = 96;
		destR.w = 71;
		destR.x = xpos;
		destR.y = ypos;
	}
	else
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
}
void GameObject::UpdateMoving() 
{
	if (!isOnTable) {
		SDL_GetMouseState(&curPosX, &curPosY);

		destR.h = 96;
		destR.w = 71;
		destR.x = curPosX - 35;
		destR.y = curPosY - 48;
	}
}

void GameObject::FixCard(int x,int y)
{
	isOnTable = true;

	xpos = x;
	ypos = y;

	destR.h = 96;
	destR.w = 71;
	destR.x = xpos;
	destR.y = ypos;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcR, &destR);
}