#pragma once
#include "Table_for_bot.h"



class EasyBotik
{
public:

	void CardMove(int OnTable, CardBot* table);
	void easyMove(int OnTable, CardBot* table);
	void mediumMove(int OnTable, CardBot* table);
	void hardMove(int OnTable, CardBot* table);

	void CardCover(CardBot OpponentCard, CardBot* table);
	void easyCover(CardBot OpponentCard, CardBot* table);
	void mediumCover(CardBot OpponentCard, CardBot* table);
	void hardCover(CardBot OpponentCard, CardBot* table);

	void Make_bot(int trump, int mod);

	int upCount(int flag);// flag = 1 -> count++;
						  // flag = -1 ->count--;
						  // flag = 0 -> nothing;
	CardBot hand[36];
	int cardsInDeck = 0;
	int cardsInOpponentHand = 0;


private:
	int botMod = 0;
	int countCardsB = 0;
	int trumpSuit = 0;
};

