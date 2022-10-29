#include "bot_fight.h"
#include "Table_for_bot.h"
#include "deck.h"


uint8_t whichTurn;
uint8_t cardsInDeck;
bool ifTook = false;
DeckadOfCards* deck;

void Bot_battle(int numOfGames)
{

	int Who_winner[3] = { 0 };

	EasyBotik* bot_1, * bot_2;
	deck = new DeckadOfCards();
	bot_1 = new EasyBotik();
	bot_2 = new EasyBotik();

	bTable table[6];

	int botmod1 = 0,
		botmod2 = 0;
	int remBefore = 0,
		remAfter = 0;




	std::cout << "Please, enter bot hardness" << std::endl;
	std::cout << "hardness first bot: ";
	std::cin >> botmod1;
	std::cout << "hardness second bot: ";
	std::cin >> botmod2;

	unsigned int start = clock();
	int num = numOfGames;
	while (num > 0) {
		srand(time(NULL));
		ifTook = false;
		whichTurn = rand() % 2;
		deck->Make_deck();
		cardsInDeck = 36;
		system("cls");
		fprintf(stdout, "%d", num);
		for (int i = 0; i < 6; i++) {
			table[i].put.value = 0;
			table[i].put.suit = 0;
			table[i].cover.value = 0;
			table[i].cover.suit = 0;
		}

		bot_1->Make_bot(deck->m_trump.suit, botmod1);
		bot_2->Make_bot(deck->m_trump.suit, botmod2);
		num--;

		NewRaund(bot_1, bot_2, table);
		while (bot_1->upCount(0) != 0 && bot_2->upCount(0) != 0) {
			remBefore = 0;
			remAfter = 0;

			for (int i = 0; i < 6; i++) {
				if (table[i].put.value != 0) {
					remBefore = i + 1;
				}
			}
			bot_1->cardsInDeck = cardsInDeck;
			bot_1->cardsInOpponentHand = bot_2->upCount(0);
			botEvents(bot_1, table, 1);

			bot_2->cardsInDeck = cardsInDeck;
			bot_2->cardsInOpponentHand = bot_1->upCount(0);
			botEvents(bot_2, table, 0);

			for (int i = 0; i < 6; i++) {
				if (table[i].put.value != 0) {
					remAfter = i + 1;
				}
			}
			if (remBefore == remAfter) {
				if (whichTurn == 0) {
					for (int i = 0; i < 6; i++) {
						if (table[i].put.value != 0 && table[i].cover.value == 0) {
							ifTook = true;
							TakeCardBot(bot_1, table);
							break;
						}
					}
				}
				if (whichTurn == 1) {
					for (int i = 0; i < 6; i++) {
						if (table[i].put.value != 0 && table[i].cover.value == 0) {
							ifTook = true;
							TakeCardBot(bot_2, table);
							break;
						}
					}
				}
				NewRaund(bot_1, bot_2, table);
			}

		}

		if (cardsInDeck == 0) {
			
			if (bot_1->upCount(0) == 0 && bot_2->upCount(0) > 0) {
				Who_winner[1]++;
			}
			else if (bot_1->upCount(0) > 0 && bot_2->upCount(0) == 0) {
				Who_winner[2]++;
			}
			else{
				Who_winner[0]++;
			}
		}

	}

	system("cls");
	unsigned int finish = clock();

	std::cout << "Time of fights :" << finish - start << std::endl;
	std::cout << "Fist bot won: " << Who_winner[1] << std::endl;
	std::cout << "Second bot won: " << Who_winner[2] << std::endl;
	std::cout << "Draw: " << Who_winner[0] << std::endl;

	delete deck;
	delete bot_1;
	delete bot_2;
}

void botEvents(EasyBotik* bot, bTable* table, int botNum)
{
	if (whichTurn == botNum) {//Œ◊≈–≈ƒ‹ ¡Œ“¿
		int remValue = 0;
		bool tmp = false;
		for (int i = 0; i < 6; i++) {
			if (table[i].put.value == 0) {
				bot->CardMove(remValue, &(table[i].put));
				if (table[i].put.value != 0)
					remValue = table[i].put.value;
			}
			else {
				remValue = table[i].put.value;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (table[i].cover.value != 0) {
				remValue = table[i].cover.value;
				for (int y = 0; y < 6; y++)
				{
					if (table[y].put.value == 0) {
						bot->CardMove(remValue, &table[y].put);
					}
				}
			}
		}
	}
	else if (whichTurn != botNum) {//¡Œ“  –Œ≈“—ﬂ 
		for (int i = 0; i < 6; i++) {
			if (table[i].put.value != 0 && table[i].cover.value == 0) {
				bot->CardCover(table[i].put, &table[i].cover);
			}
		}
	}
}

void NewRaund(EasyBotik* bot_1, EasyBotik* bot_2, bTable* table)
{
	if (whichTurn == 1) {//Ó˜ÂÂ‰¸ 1 
		if (!ifTook) {
			whichTurn = 0;//Œ˜ÂÂ‰¸ ‚ÚÓÓ„Ó ·ÓÚ‡
		}

		while (bot_1->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			bot_1->hand[bot_1->upCount(0)] = deck->GiveCard();
			bot_1->upCount(1);
			cardsInDeck--;
		}
		while (bot_2->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			bot_2->hand[bot_2->upCount(0)] = deck->GiveCard();
			bot_2->upCount(1);
			cardsInDeck--;
		}
	}
	else {
		if (!ifTook) {
			whichTurn = 1;//Œ˜ÂÂ‰¸ 1 ·ÓÚ‡
		}
		while (bot_2->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			bot_2->hand[bot_2->upCount(0)] = deck->GiveCard();
			bot_2->upCount(1);
			cardsInDeck--;
		}
		while (bot_1->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			bot_1->hand[bot_1->upCount(0)] = deck->GiveCard();
			bot_1->upCount(1);
			cardsInDeck--;
		}
	}

	for (int i = 0; i < 6; i++) {
		table[i].put.value = 0;
		table[i].put.suit = 0;
		table[i].cover.value = 0;
		table[i].cover.suit = 0;
	}
	bot_1->cardsInDeck = cardsInDeck;
	bot_1->cardsInOpponentHand = bot_2->upCount(0);

	bot_2->cardsInDeck = cardsInDeck;
	bot_2->cardsInOpponentHand = bot_1->upCount(0);
	ifTook = false;
}

void TakeCardBot(EasyBotik* bot, bTable* table)
{
	for (int i = 0; i < 6; i++) {
		if (table[i].put.value != 0) {
			bot->hand[bot->upCount(0)] = table[i].put;
			bot->upCount(1);
			if (table[i].cover.value != 0) {
				bot->hand[bot->upCount(0)] = table[i].cover;
				bot->upCount(1);
			}
		}
	}
}