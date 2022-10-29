#pragma once
#include "Game.h"

#define	MAX_COUNT_CARD	36		

typedef struct Cards {
	int suit;
	int value;
}Card;

class DeckOfCards
{
private:
	int	m_cardCount;//Количество карт в колоде
	int pos=0;		//Колода		
		

public:
	
	DeckOfCards();
	Card m_trump;//Козырь
	~DeckOfCards();
	void MixCards(); //Перемешиваем колоду
	Card* cardBatch; //Колода
	Card GiveCard();
};