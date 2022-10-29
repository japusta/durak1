#include "EasyBot.h"


EasyBot::EasyBot(int trump,BotMod mod)
{
	botMod = mod;
	trumpSuit = trump;
	for (int i = 0; i < 36; i++) {
		hand[i] = nullptr;
	}
}

EasyBot::~EasyBot()
{
	for (int i = 0; i < countCardsB; i++) {
		delete(hand[i]);       
	}
}

bool EasyBot::CardMove(int PosForCard, int OnTable, Table* table)
{
	switch(botMod)
	{
	case EASY:{
		return easyMove(PosForCard, OnTable, table);
		break;
	}
	case MEDIUM: {
		return mediumMove(PosForCard, OnTable, table);
		break;
	}
	case HARD: {
		return hardMove(PosForCard, OnTable, table);
		break;
	}
	default:
		break;
	}
	
}

bool EasyBot::easyMove(int PosForCard, int OnTable, Table* table)
{
	if (cardsInOpponentHand == 0) {
		return false;
	}
	if (OnTable == 0) {
		int numCard = rand() % countCardsB;
		hand[numCard]->xpos = PosForCard;
		hand[numCard]->ypos = 200;
		table->Card = hand[numCard];

		for (int i = numCard; i < countCardsB - 1; i++) {
			hand[i + 1]->xpos -= 36;
			hand[i] = hand[i + 1];
		}
		hand[countCardsB - 1] = nullptr;
		countCardsB--;
		return true;
	}
	else {
		for (int i = 0; i < countCardsB; i++)
		{
			if (hand[i]->card.value == OnTable) {
				hand[i]->xpos = PosForCard;
				hand[i]->ypos = 200;
				table->Card = hand[i];

				for (int y = i; y < countCardsB - 1; y++) {
					hand[y + 1]->xpos -= 36;
					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1] = nullptr;
				countCardsB--;
				return true;
			}
		}
		return false;
	}
	return false;
}
<<<<<<< HEAD
=======

>>>>>>> 6c4ad19 (5th)
bool EasyBot::hardMove(int PosForCard, int OnTable, Table* table)
{
	if (cardsInOpponentHand == 0) {
		return false;
	}
	if (OnTable == 0) {
		if (cardsInDeck > 0) {
			int remNum = 0;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i]->card.value < hand[remNum]->card.value && hand[i]->card.suit != trumpSuit){
					remNum = i;
				}
			}
			if (hand[remNum]->card.suit == trumpSuit) {
				for (int i = 0; i < 6; i++) {
					if (hand[i]->card.value < hand[remNum]->card.value) {
						remNum = i;
					}
				}
			}
			hand[remNum]->xpos = PosForCard;
			hand[remNum]->ypos = 200;
			table->Card = hand[remNum];

			for (int i = remNum; i < countCardsB - 1; i++) {
				hand[i + 1]->xpos -= 36;
				hand[i] = hand[i + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		else if(cardsInDeck == 0)
		{
			//assessment of the condition in the hand
			int count1 = 1,
				count2 = 0,//This is a counts of the same cards in hand
				remNum = 0;
			bool flag = false,//this is the time flag to know about trump in repetitive cards
				 InRepetitiveTrump = false;

			for (int i = 0; i < countCardsB; i++) {
				for (int y = i; y < countCardsB; y++) {
					if (hand[i] == hand[y])
					{
<<<<<<< HEAD
						__asm {
							inc count2
						}

					//	count2++;
=======
						count2++;
>>>>>>> 6c4ad19 (5th)
						if (hand[y]->card.suit == trumpSuit) {
							flag = true;
						}
					}
				}
				if ((count2 < count1)||
					(count1 == count2 && hand[i]->card.value > hand[remNum]->card.value)) {
					InRepetitiveTrump = flag;
					count1 = count2;
					remNum = i;
				}
			}

			if (countCardsB - count1 == 1) {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i]->card.value >= 12 && hand[i]->card.suit == trumpSuit) {
						hand[i]->xpos = PosForCard;
						hand[i]->ypos = 200;
						table->Card = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y + 1]->xpos -= 36;
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1] = nullptr;
						countCardsB--;
						return true;
					}
				}
			}
			else {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i]->card.suit != trumpSuit &&
						hand[i]->card.value != hand[remNum]->card.value) {
						hand[i]->xpos = PosForCard;
						hand[i]->ypos = 200;
						table->Card = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y + 1]->xpos -= 36;
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1] = nullptr;
						countCardsB--;
						return true;
					}
				}
			}
			if (!InRepetitiveTrump) {
				hand[remNum]->xpos = PosForCard;
				hand[remNum]->ypos = 200;
				table->Card = hand[remNum];

				for (int y = remNum; y < countCardsB - 1; y++) {
					hand[y + 1]->xpos -= 36;
					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1] = nullptr;
				countCardsB--;
				return true;
			}

			else if (countCardsB >3 && count1 >=2) {
				for (int i = 0; i < countCardsB; i++) {
					if (hand[i]->card.value != hand[remNum]->card.value &&
						hand[i]->card.suit != trumpSuit){
							hand[i]->xpos = PosForCard;
							hand[i]->ypos = 200;
							table->Card = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y + 1]->xpos -= 36;
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1] = nullptr;
							countCardsB--;
							return true;
						}

					else if (i == (countCardsB - 1)) {
							hand[i]->xpos = PosForCard;
							hand[i]->ypos = 200;
							table->Card = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y + 1]->xpos -= 36;
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1] = nullptr;
							countCardsB--;
							return true;
						}
				}
				return false;
			}

			else {
				int num = 0;
				for (int i = 0; i < countCardsB; i++) {
					if (hand[num]->card.suit == trumpSuit && hand[i]->card.suit != trumpSuit) {
						num = i;
					}
					else if (hand[num]->card.suit == trumpSuit && hand[i]->card.suit == trumpSuit &&
						hand[num]->card.value > hand[i]->card.value){
						num = i;
					}
					else if (hand[num]->card.value > hand[i]->card.value) {
						num = i;
					}
				}
				hand[num]->xpos = PosForCard;
				hand[num]->ypos = 200;
				table->Card = hand[num];

				for (int y = num; y < countCardsB - 1; y++) {
					hand[y + 1]->xpos -= 36;
					hand[y] = hand[y + 1];
				}
				hand[countCardsB - 1] = nullptr;
				countCardsB--;
				return true;
			}
		}
	}
	else {
		if (cardsInDeck > 0) {
			for (int i = 0; i < countCardsB; i++)
			{
				if (hand[i]->card.value == OnTable) {
					if (hand[i]->card.suit != trumpSuit) {
						hand[i]->xpos = PosForCard;
						hand[i]->ypos = 200;
						table->Card = hand[i];

						for (int y = i; y < countCardsB - 1; y++) {
							hand[y + 1]->xpos -= 36;
							hand[y] = hand[y + 1];
						}
						hand[countCardsB - 1] = nullptr;
						countCardsB--;
						return true;
					}
				}
			}
			return false;
			}
		else if (cardsInDeck == 0) {
			if (countCardsB >= 5) {
				for (int i = 0; i < countCardsB; i++)
				{
					if (hand[i]->card.value == OnTable) {
						if (hand[i]->card.suit != trumpSuit) {
							hand[i]->xpos = PosForCard;
							hand[i]->ypos = 200;
							table->Card = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y + 1]->xpos -= 36;
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1] = nullptr;
							countCardsB--;
							return true;
						}
					}
				}
			}
			else {	
				int countNotTrumps = 0;
				for (int i = 0; i < countCardsB; i++) {\
					if (hand[i]->card.suit != trumpSuit) {
<<<<<<< HEAD
						__asm {
							inc countNotTrumps
						}
						//countNotTrumps++;
=======
						countNotTrumps++;
>>>>>>> 6c4ad19 (5th)
					}
				}
				if (countCardsB - countNotTrumps <= 1) {
					for (int i = 0; i < countCardsB; i++)
					{
						if (hand[i]->card.value == OnTable) {
							hand[i]->xpos = PosForCard;
							hand[i]->ypos = 200;
							table->Card = hand[i];

							for (int y = i; y < countCardsB - 1; y++) {
								hand[y + 1]->xpos -= 36;
								hand[y] = hand[y + 1];
							}
							hand[countCardsB - 1] = nullptr;
							countCardsB--;
							return true;
						}
					}
				}
				else {
					for (int i = 0; i < countCardsB; i++)
					{
						if (hand[i]->card.value == OnTable) {
							if (hand[i]->card.suit != trumpSuit) {
								hand[i]->xpos = PosForCard;
								hand[i]->ypos = 200;
								table->Card = hand[i];

								for (int y = i; y < countCardsB - 1; y++) {
									hand[y + 1]->xpos -= 36;
									hand[y] = hand[y + 1];
								}
								hand[countCardsB - 1] = nullptr;
								countCardsB--;
								return true;
							}
						}
					}
				}
				return false;
			}
			return false;
		}
	}
	return false;
}

bool EasyBot::mediumMove(int PosForCard, int OnTable, Table* table)
{
	if (cardsInOpponentHand == 0) {
		return false;
	}
	if (OnTable == 0) {

		int remNum = 0;
		for (int i = 0; i < countCardsB; i++) {
			if (hand[i]->card.value < hand[remNum]->card.value && hand[i]->card.suit != trumpSuit) {
				remNum = i;
			}
		}
		if (hand[remNum]->card.suit == trumpSuit) {
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i]->card.value < hand[remNum]->card.value) {
					remNum = i;
				}
			}
		}
		hand[remNum]->xpos = PosForCard;
		hand[remNum]->ypos = 200;
		table->Card = hand[remNum];
		for (int i = remNum; i < countCardsB - 1; i++) {
			hand[i + 1]->xpos -= 36;
			hand[i] = hand[i + 1];
		}
		hand[countCardsB - 1] = nullptr;
		countCardsB--;
		return true;
	}

	else {
		if (cardsInDeck != 0){
			int remNum = -1;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i]->card.value == OnTable && (hand[i]->card.suit != trumpSuit 
					|| (hand[i]->card.suit == trumpSuit && hand[i]->card.value<11))) {
					remNum = i;
				}
			}
			if (remNum == -1) {
				return false;
			}
			else {
				hand[remNum]->xpos = PosForCard;
				hand[remNum]->ypos = 200;
				table->Card = hand[remNum];
				for (int i = remNum; i < countCardsB - 1; i++) {
					hand[i + 1]->xpos -= 36;
					hand[i] = hand[i + 1];
				}
				hand[countCardsB - 1] = nullptr;
				countCardsB--;
				return true;
			}
			
		}
		else if (cardsInDeck == 0) {
			int remNum = -1;
			for (int i = 0; i < countCardsB; i++) {
				if (hand[i]->card.value == OnTable) {
					remNum = i;
				}
			}
			if (remNum == -1) {
				return false;
			}
			else {
				hand[remNum]->xpos = PosForCard;
				hand[remNum]->ypos = 200;
				table->Card = hand[remNum];
				for (int i = remNum; i < countCardsB - 1; i++) {
					hand[i + 1]->xpos -= 36;
					hand[i] = hand[i + 1];
				}
				hand[countCardsB - 1] = nullptr;
				countCardsB--;
				return true;
			}
		}
	}
	return false;
}

bool EasyBot::CardCover(int PosCard,Card OpponentCard,Table* table)
{
	switch (botMod)
	{
	case EASY: {
		return easyCover(PosCard, OpponentCard, table);
		break;
	}
	case MEDIUM: {
		return mediumCover(PosCard, OpponentCard, table);
		break;
	}
	case HARD: {
		return hardCover(PosCard, OpponentCard, table);
		break;
	}
	default:
		break;
	}
}

bool EasyBot::easyCover(int PosCard, Card OpponentCard, Table* table)
{
	for (int i = 0; i < countCardsB; i++) {
		if (hand[i]->card.suit == OpponentCard.suit && hand[i]->card.value > OpponentCard.value) {
			hand[i]->xpos = PosCard + 20;
			hand[i]->ypos = 220;
			table->CardOn = hand[i];
			for (int y = i; y < countCardsB - 1; y++) {
				hand[y + 1]->xpos -= 36;
				hand[y] = hand[y + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		else if (hand[i]->card.suit == trumpSuit && OpponentCard.suit != trumpSuit)
		{
			hand[i]->xpos = PosCard + 20;
			hand[i]->ypos = 220;
			table->CardOn = hand[i];
			for (int y = i; y < countCardsB - 1; y++) {
				hand[y + 1]->xpos -= 36;
				hand[y] = hand[y + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
	}
	return false;
}
<<<<<<< HEAD
=======

>>>>>>> 6c4ad19 (5th)
bool EasyBot::hardCover(int PosCard, Card OpponentCard, Table* table)
{
	int rem[36] = {0},
		remNum = -1,
		remElem = 20, 
		y = 0;

	for (int i = 0; i < countCardsB; i++) {
		if ((hand[i]->card.suit == OpponentCard.suit && hand[i]->card.value > OpponentCard.value)||
			(hand[i]->card.suit == trumpSuit && OpponentCard.suit != trumpSuit)) {
			rem[y] = i;
<<<<<<< HEAD
			__asm {
				inc y
			}
			//y++;
=======
			y++;
>>>>>>> 6c4ad19 (5th)
		}
	}
	if (OpponentCard.suit == trumpSuit && cardsInDeck > 6) {
		return false;
	}
	else if (OpponentCard.suit == trumpSuit && cardsInDeck <= 6) {
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		return false;
	}//........................................................
	else if (OpponentCard.suit != trumpSuit) {
		
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.suit != trumpSuit &&
				hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		return false;
	}
	return false;
}
<<<<<<< HEAD
=======

>>>>>>> 6c4ad19 (5th)
bool EasyBot::mediumCover(int PosCard, Card OpponentCard, Table* table)
{
	int rem[36] = { 0 },
		remNum = -1,
		remElem = 20,
		y = 0;

	for (int i = 0; i < countCardsB; i++) {
		if ((hand[i]->card.suit == OpponentCard.suit && hand[i]->card.value > OpponentCard.value) ||
			(hand[i]->card.suit == trumpSuit && OpponentCard.suit != trumpSuit)) {
			rem[y] = i;
<<<<<<< HEAD
			__asm {
				inc y
			}
			//y++;
=======
			y++;
>>>>>>> 6c4ad19 (5th)
		}
	}
	if (OpponentCard.suit == trumpSuit && cardsInDeck > 6) {
		return false;
	}
	else if (OpponentCard.suit == trumpSuit && cardsInDeck <= 6) {
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		return false;
	}
	else if (OpponentCard.suit != trumpSuit) {

		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.suit != trumpSuit &&
				hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		for (int i = 0; i < y; i++) {
			if (hand[rem[i]]->card.value < remElem) {
				remElem = hand[rem[i]]->card.value;
				remNum = rem[i];
			}
		}
		if (remNum != -1) {
			hand[remNum]->xpos = PosCard + 20;
			hand[remNum]->ypos = 220;
			table->CardOn = hand[remNum];
			for (int j = remNum; j < countCardsB - 1; j++) {
				hand[j + 1]->xpos -= 36;
				hand[j] = hand[j + 1];
			}
			hand[countCardsB - 1] = nullptr;
			countCardsB--;
			return true;
		}
		return false;
	}
	return false;
}

int EasyBot::upCount(int flag)
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