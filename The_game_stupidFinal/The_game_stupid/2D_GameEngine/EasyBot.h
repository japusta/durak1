#pragma once
#include "Game.h"
#include "Table.h"


enum BotMod
{
	EASY,
	MEDIUM,
	HARD
};
class EasyBot
{
public:
	EasyBot(int trump,BotMod mod);
	~EasyBot();

	bool CardMove(int PosForCard, int OnTable, Table* table);
	bool easyMove(int PosForCard, int OnTable, Table* table);
	bool mediumMove(int PosForCard, int OnTable, Table* table);
	bool hardMove(int PosForCard, int OnTable, Table* table);

	bool CardCover(int PosCard,Card OpponentCard,Table* table);
	bool easyCover(int PosCard, Card OpponentCard, Table* table);
	bool mediumCover(int PosCard, Card OpponentCard, Table* table);
	bool hardCover(int PosCard, Card OpponentCard, Table* table);

	int upCount(int flag);// flag = 1 -> count++;
	                      // flag = -1 ->count--;
						  // flag = 0 -> nothing;
	GameObject* hand[36];
	int cardsInDeck = 0;
	int cardsInOpponentHand = 0;
	

private:
	BotMod botMod;
	int countCardsB = 0;
	int trumpSuit;
};
