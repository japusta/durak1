#pragma once
#include "Table_for_bot.h"


#define	MAX_COUNT_CARD	36		

class DeckadOfCards
{
private:
	int pos = 0;		//������		
public:

	CardBot m_trump;//������
	void Make_deck();
	void MixCards(); //������������ ������
	CardBot cardBatch[MAX_COUNT_CARD]; //������
	CardBot GiveCard();
};