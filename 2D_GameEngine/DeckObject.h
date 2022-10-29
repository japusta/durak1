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
	int	m_cardCount;//���������� ���� � ������
	int pos=0;		//������		
		

public:
	
	DeckOfCards();
	Card m_trump;//������
	~DeckOfCards();
	void MixCards(); //������������ ������
	Card* cardBatch; //������
	Card GiveCard();
};