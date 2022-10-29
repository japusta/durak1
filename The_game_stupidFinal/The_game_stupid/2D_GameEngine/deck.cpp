
#include "deck.h"


void DeckadOfCards::Make_deck()
{
	pos = 0;
	int	number = 0;

	for (int su = 1; su < 5; su++)//Масти. Всего 4 масти
		for (int c1 = 0; c1 < MAX_COUNT_CARD / 4; c1++)
		{   //Заполняем масти
			cardBatch[number].suit = su;//Масть
			cardBatch[number].value = c1 + 6;//Значение
			number++;
		}
	MixCards();
}

void DeckadOfCards::MixCards()//mix our deck
{
	CardBot tmp1;
	CardBot tmp2;
	int	i1, i2;
	srand(time(NULL));
	for (int i = 0; i < 36; i++)
	{
		i1 = rand() % MAX_COUNT_CARD;
		i2 = rand() % MAX_COUNT_CARD;
		tmp1 = cardBatch[i1];
		tmp2 = cardBatch[i2];
		cardBatch[i1] = tmp2;
		cardBatch[i2] = tmp1;
	}

	m_trump = cardBatch[35]; //trump is the last card in our deck 
}

CardBot DeckadOfCards::GiveCard()
{
	pos++;
	return cardBatch[pos - 1];
}