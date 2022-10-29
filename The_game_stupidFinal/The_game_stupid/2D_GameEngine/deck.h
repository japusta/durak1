#pragma once
#include "Table_for_bot.h"


#define	MAX_COUNT_CARD	36		

class DeckadOfCards
{
private:
	int pos = 0;		//Колода		
public:

	CardBot m_trump;//Козырь
	void Make_deck();
	void MixCards(); //Перемешиваем колоду
	CardBot cardBatch[MAX_COUNT_CARD]; //Колода
	CardBot GiveCard();
};