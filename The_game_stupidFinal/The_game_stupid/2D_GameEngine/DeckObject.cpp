#include "DeckObject.h"

DeckOfCards::~DeckOfCards()
{
	delete cardBatch;
}

DeckOfCards::DeckOfCards()
{
	int	number = 0;
	cardBatch = new Card[MAX_COUNT_CARD];

	for (int su = 1; su < 5; su++)//Масти. Всего 4 масти
		for (int c1 = 0; c1 < MAX_COUNT_CARD / 4; c1++)
		{   //Заполняем масти
			cardBatch[number].suit = su;//Масть
			cardBatch[number].value = c1 + 6;//Значение
<<<<<<< HEAD
			//
			__asm {
			mov edx, DWORD PTR number
				add edx, 1
				mov DWORD PTR number, edx
		}
			//number++;
=======
			number++;
>>>>>>> 6c4ad19 (5th)
		}
	MixCards();
}

void DeckOfCards::MixCards()//mix our deck
{ 
	Card tmp1;
	Card tmp2;
	int	i1, i2;
	srand(time(NULL));
	for (int i = 0; i < 36; i++)
	{
<<<<<<< HEAD
		int i3 = rand();
		int i4 = rand();
		__asm {
			mov eax, i3
			xor edx, edx
			mov ecx, MAX_COUNT_CARD
			div ecx
			mov i1, edx

			mov eax, i4
			xor edx, edx
			mov ecx, MAX_COUNT_CARD
			div ecx
			mov i2, edx

		}
		//i1 = rand() % MAX_COUNT_CARD;
		//i2 = rand() % MAX_COUNT_CARD;
=======
		i1 = rand() % MAX_COUNT_CARD;
		i2 = rand() % MAX_COUNT_CARD;
>>>>>>> 6c4ad19 (5th)
		tmp1 = cardBatch[i1];
		tmp2 = cardBatch[i2];
		cardBatch[i1] = tmp2;
		cardBatch[i2] = tmp1;
	}

	m_trump = cardBatch[35]; //trump is the last card in our deck 
}

Card DeckOfCards::GiveCard()
{
	pos++;
	return cardBatch[pos-1];
}