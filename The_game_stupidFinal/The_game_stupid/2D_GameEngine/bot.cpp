#include "bot.h"


void EasyBotik::Make_bot(int trump, int mod)
{
	cardsInDeck = 0;
	cardsInOpponentHand = 0;
	countCardsB = 0;
	botMod = mod;
	trumpSuit = trump;
	for (int i = 0; i < 36; i++) {
		hand[i].suit = 0;
		hand[i].value = 0;
	}
}


void EasyBotik::CardMove(int OnTable, CardBot* table)
{
	switch (botMod)
	{
	case 0: {
		easyMove(OnTable, table);
		break;
	}
	case 1: {
		mediumMove(OnTable, table);
		break;
	}
	case 2: {
		hardMove(OnTable, table);
		break;
	}
	default:
		break;
	}

}

void EasyBotik::easyMove(int OnTable, CardBot* table)
{
	if (cardsInOpponentHand == 0) {
		return;
	}
	if (OnTable == 0) {
		int numCard = rand() % countCardsB;
		*table = hand[numCard];

		for (int i = numCard; i < countCardsB - 1; i++) {
			hand[i] = hand[i + 1];
		}
		hand[countCardsB - 1].suit = 0;
		hand[countCardsB - 1].value = 0;
		countCardsB--;
		return;
	}
	else if (OnTable != 0) {
		for (int i = 0; i < countCardsB; i++)
		{
			if (hand[i].value == OnTable) {
				*table = hand[i];

				for (int y = i; y < countCardsB - 1; y++) {
					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1].suit = 0;
				hand[countCardsB - 1].value = 0;
				countCardsB--;
				return;
			}
		}
		return;
	}
	return;
}

void EasyBotik::hardMove(int OnTable, CardBot* table)
{
	if (cardsInOpponentHand == 0) {
		return;
	}
	if (OnTable == 0) {
		if (cardsInDeck > 0) {
			int remNum = 0;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i].value < hand[remNum].value && hand[i].suit != trumpSuit) {
					remNum = i;
				}
			}
			if (hand[remNum].suit == trumpSuit) {
				for (int i = 0; i < 6; i++) {
					if (hand[i].value < hand[remNum].value) {
						remNum = i;
					}
				}
			}
			*table = hand[remNum];

			for (int i = remNum; i < countCardsB - 1; i++) {
				hand[i] = hand[i + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		else if (cardsInDeck == 0)
		{
			//assessment of the condition in the hand
			int count1 = 1,
				count2 = 0,//This is a counts of the same cards in hand
				remNum = 0;
			bool flag = false,//this is the time flag to know about trump in repetitive cards
				InRepetitiveTrump = false;

			for (int i = 0; i < countCardsB; i++) {
				for (int y = i; y < countCardsB; y++) {
					if (hand[i].value == hand[y].value)
					{
						count2++;
						if (hand[y].suit == trumpSuit) {
							flag = true;
						}
					}
				}
				if ((count2 < count1) ||
					(count1 == count2 && hand[i].value > hand[remNum].value)) {
					InRepetitiveTrump = flag;
					count1 = count2;
					remNum = i;
				}
			}

			if (countCardsB - count1 == 1) {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i].value >= 12 && hand[i].suit == trumpSuit) {
						*table = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1].suit = 0;
						hand[countCardsB - 1].value = 0;
						countCardsB--;
						return;
					}
				}
			}
			else {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i].suit != trumpSuit &&
						hand[i].value != hand[remNum].value) {

						*table = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1].suit = 0;
						hand[countCardsB - 1].value = 0;
						countCardsB--;
						return;
					}
				}
			}
			if (!InRepetitiveTrump) {

				*table = hand[remNum];

				for (int y = remNum; y < countCardsB - 1; y++) {

					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1].suit = 0;
				hand[countCardsB - 1].value = 0;
				countCardsB--;
				return;
			}

			else if (countCardsB > 3 && count1 >= 2) {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i].value != hand[remNum].value &&
						hand[i].suit != trumpSuit) {

						*table = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1].suit = 0;
						hand[countCardsB - 1].value = 0;
						countCardsB--;
						return;
					}

					else if (i == (countCardsB - 1)) {

						*table = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1].suit = 0;
						hand[countCardsB - 1].value = 0;
						countCardsB--;
						return;
					}
				}
				return;
			}

			else {
				int num = 0;
				for (int i = 0; i < countCardsB; i++) {
					if (hand[num].suit == trumpSuit && hand[i].suit != trumpSuit) {
						num = i;
					}
					else if (hand[num].suit == trumpSuit && hand[i].suit == trumpSuit &&
						hand[num].value > hand[i].value) {
						num = i;
					}
					else if (hand[num].value > hand[i].value) {
						num = i;
					}
				}

				*table = hand[num];

				for (int y = num; y < countCardsB - 1; y++) {
					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1].suit = 0;
				hand[countCardsB - 1].value = 0;
				countCardsB--;
				return;
			}
		}
	}
	else {
		if (cardsInDeck > 0) {
			for (int i = 0; i < countCardsB; i++)
			{
				if (hand[i].value == OnTable) {
					if (hand[i].suit != trumpSuit) {

						*table = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1].suit = 0;
						hand[countCardsB - 1].value = 0;
						countCardsB--;
						return;
					}
				}
			}
			return;
		}
		else if (cardsInDeck == 0) {
			if (countCardsB >= 5) {
				for (int i = 0; i < countCardsB; i++)
				{
					if (hand[i].value == OnTable) {
						if (hand[i].suit != trumpSuit) {

							*table = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1].suit = 0;
							hand[countCardsB - 1].value = 0;
							countCardsB--;
							return;
						}
					}
				}
			}
			else {
				int countNotTrumps = 0;
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i].suit != trumpSuit) {
						countNotTrumps++;
					}
				}
				if (countCardsB - countNotTrumps <= 1) {
					for (int i = 0; i < countCardsB; i++)
					{
						if (hand[i].value == OnTable) {

							*table = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1].suit = 0;
							hand[countCardsB - 1].value = 0;
							countCardsB--;
							return;
						}
					}
				}
				else {
					for (int i = 0; i < countCardsB; i++)
					{
						if (hand[i].value == OnTable) {
							if (hand[i].suit != trumpSuit) {

								*table = hand[i];

								for (int y = i; y < countCardsB - 1; y++) {
									hand[y] = hand[y + 1];
								}
								hand[countCardsB - 1].suit = 0;
								hand[countCardsB - 1].value = 0;
								countCardsB--;
								return;
							}
						}
					}
				}
				return;
			}
			return;
		}
	}
	return;
}

void EasyBotik::mediumMove(int OnTable, CardBot* table)
{
	if (cardsInOpponentHand == 0) {
		return;
	}
	if (OnTable == 0) {

		int remNum = 0;
		for (int i = 0; i < countCardsB; i++) {
			if (hand[i].value < hand[remNum].value && hand[i].suit != trumpSuit) {
				remNum = i;
			}
		}
		if (hand[remNum].suit == trumpSuit) {
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i].value < hand[remNum].value) {
					remNum = i;
				}
			}
		}

		*table = hand[remNum];
		for (int i = remNum; i < countCardsB - 1; i++) {
			hand[i] = hand[i + 1];
		}
		hand[countCardsB - 1].suit = 0;
		hand[countCardsB - 1].value = 0;
		countCardsB--;
		return;
	}

	else {
		if (cardsInDeck != 0) {
			int remNum = -1;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i].value == OnTable && (hand[i].suit != trumpSuit
					|| (hand[i].suit == trumpSuit && hand[i].value < 11))) {
					remNum = i;
				}
			}
			if (remNum == -1) {
				return;
			}
			else {

				*table = hand[remNum];
				for (int i = remNum; i < countCardsB - 1; i++) {
					hand[i] = hand[i + 1];
				}
				hand[countCardsB - 1].suit = 0;
				hand[countCardsB - 1].value = 0;
				countCardsB--;
				return;
			}

		}
		else if (cardsInDeck == 0) {
			int remNum = -1;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i].value == OnTable) {
					remNum = i;
				}
			}
			if (remNum == -1) {
				return;
			}
			else {

				*table = hand[remNum];
				for (int i = remNum; i < countCardsB - 1; i++) {
					hand[i] = hand[i + 1];
				}
				hand[countCardsB - 1].suit = 0;
				hand[countCardsB - 1].value = 0;
				countCardsB--;
				return;
			}
		}
	}
	return;
}

void EasyBotik::CardCover(CardBot OpponentCard, CardBot* table)
{
	switch (botMod)
	{
	case 0: {
		easyCover(OpponentCard, table);
		break;
	}
	case 1: {
		mediumCover(OpponentCard, table);
		break;
	}
	case 2: {
		hardCover(OpponentCard, table);
		break;
	}
	default:
		break;
	}
}

void EasyBotik::easyCover(CardBot OpponentCard, CardBot* table)
{
	for (int i = 0; i < countCardsB; i++) {
		if (hand[i].suit == OpponentCard.suit && hand[i].value > OpponentCard.value) {
			*table = hand[i];
			for (int y = i; y < countCardsB - 1; y++) {
				hand[y] = hand[y + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		else if (hand[i].suit == trumpSuit && OpponentCard.suit != trumpSuit)
		{
			*table = hand[i];
			for (int y = i; y < countCardsB - 1; y++) {
				hand[y] = hand[y + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
	}
	return;
}

int EasyBotik::upCount(int flag)
{
	if (flag == 1) {
		countCardsB++;
		return countCardsB;
	}
	else if (flag == -1) {
		countCardsB--;
		return countCardsB;
	}
	else if (flag == 0) {
		return countCardsB;
	}
	return 0;
}

void EasyBotik::hardCover(CardBot OpponentCard, CardBot* table)
{
	int rem[36] = { 0 },
		remNum = -1,
		remElem = 20,
		y = 0;

	for (int i = 0; i < countCardsB; i++) {
		if ((hand[i].suit == OpponentCard.suit && hand[i].value > OpponentCard.value) ||
			(hand[i].suit == trumpSuit && OpponentCard.suit != trumpSuit)) {
			rem[y] = i;
			y++;
		}
	}
	if (OpponentCard.suit == trumpSuit && cardsInDeck > 6) {
		return;
	}
	else if (OpponentCard.suit == trumpSuit && cardsInDeck <= 6) {
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		return;
	}//........................................................
	else if (OpponentCard.suit != trumpSuit) {

		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].suit != trumpSuit &&
				hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		return;
	}
	return;
}

void EasyBotik::mediumCover(CardBot OpponentCard, CardBot* table)
{
	int rem[36] = { 0 },
		remNum = -1,
		remElem = 20,
		y = 0;

	for (int i = 0; i < countCardsB; i++) {
		if ((hand[i].suit == OpponentCard.suit && hand[i].value > OpponentCard.value) ||
			(hand[i].suit == trumpSuit && OpponentCard.suit != trumpSuit)) {
			rem[y] = i;
			y++;
		}
	}
	if (OpponentCard.suit == trumpSuit && cardsInDeck > 6) {
		return;
	}
	else if (OpponentCard.suit == trumpSuit && cardsInDeck <= 6) {
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		return;
	}
	else if (OpponentCard.suit != trumpSuit) {

		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].suit != trumpSuit &&
				hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]].value < remElem) {
				remElem = hand[rem[i]].value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			*table = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1].suit = 0;
			hand[countCardsB - 1].value = 0;
			countCardsB--;
			return;
		}
		return;
	}
	return;
}

