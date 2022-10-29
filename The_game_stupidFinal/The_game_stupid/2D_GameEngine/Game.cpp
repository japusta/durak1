#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Table.h"
#include "EasyBot.h"
#include "Point.h"

#define MAX_COUNT_OF_CARDS 36

GameObject* hand[36];
GameObject* trumpCard;
SDL_Rect deckRect;

DeckOfCards* deck;
Table *TableRectangles[6];
EasyBot* easyBot;
EasyBot* firstBot,//снизу
	   * secondBot;//сверху

int cardPos = 142,
cardStep = 36,
cardDisplace = 0;

int rectPosX = 71,
rectStep = 100,
rectPosY = 200;

int countCards = 0;
int whichMoving = -1;
int whichTurn = 0; 
int cardsInDeck = 36;
int Mod = 1;

bool UnderControl = false;
bool CanBotMove = false;
bool ifTaken = false;
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* TableTex,
* DeckTex;
Point* point = nullptr;

Game::Game(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen,int mod,bool control)
{
	whichTurn = rand()%2;
	deck = new DeckOfCards();
	cardsInDeck = 36;
	Mod = mod;
	UnderControl = control;
	int flag = 0;
	if (mod != 2 || control) {

		if (fullscreen) {
			flag = SDL_WINDOW_FULLSCREEN;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			std::cout << "SDL subsystems initialised..." << std::endl;

			window = SDL_CreateWindow(title, xpos, ypos, width, heigth, flag);
			if (window) {
				std::cout << "Window created..." << std::endl;
			}

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				TableTex = TextureManager::LoadTexture("bitmaps/Table.bmp");
				std::cout << "Renderer created..." << std::endl;
			}

			isRunning = true;
			trumpCard = new GameObject(deck->m_trump, 680, 235, true);
			DeckTex = TextureManager::LoadTexture("bitmaps/deck.bmp");
			point = new Point();
			if (mod == 1) {// Инициализация Game
				for (int i = 0; i < MAX_COUNT_OF_CARDS; i++) {
					hand[i] = nullptr;
				}
				int ans = 0;
				std::cout << "Choose bot hard from\n0->Easy\n1->Medium\n2->Hard\0" << std::endl;
				std::cout << "bot hard is: \0";
				std::cin >> ans;
				if (ans == 0) {
					easyBot = new EasyBot(deck->m_trump.suit, EASY);
				}
				else if (ans == 1) {
					easyBot = new EasyBot(deck->m_trump.suit, MEDIUM);
				}
				else if (ans == 2) {
					easyBot = new EasyBot(deck->m_trump.suit, HARD);
				}
				else {
					isRunning = false;
				}
				newRaund();
			}
			else if (mod == 2) {// Инициализация Botbattle
				int ans = 0;
				std::cout << "Choose bot hard from\n0->Easy\n1->Medium\n2->Hard\0" << std::endl;
				std::cout << "(this is lower bot)First bot hard is: \0";
				std::cin >> ans;

				if (ans == 0) {
					firstBot = new EasyBot(deck->m_trump.suit, EASY);
				}
				else if (ans == 1) {
					firstBot = new EasyBot(deck->m_trump.suit, MEDIUM);
				}
				else if (ans == 2) {
					firstBot = new EasyBot(deck->m_trump.suit, HARD);
				}
				else {
					isRunning = false;
				}

				std::cout << "Choose bot hard from\n0->Easy\n1->Medium\n2->Hard\0" << std::endl;
				std::cout << "(this is upper bot)Second bot hard is: \0";
				std::cin >> ans;
				
				if (ans == 0) {
					secondBot = new EasyBot(deck->m_trump.suit, EASY);
				}
				else if (ans == 1) {
					secondBot = new EasyBot(deck->m_trump.suit, MEDIUM);
				}
				else if (ans == 2) {
					secondBot = new EasyBot(deck->m_trump.suit, HARD);
				}
				else {
					isRunning = false;
				}

				newRaundBattle();
			}
			else {
				isRunning = false;
			}
		}
	}
	else if (!control && mod == 2){
		isRunning = true;
		firstBot = new EasyBot(deck->m_trump.suit, HARD);
		secondBot = new EasyBot(deck->m_trump.suit, HARD);
		newRaundBattle();
	}
	else {
		isRunning = false;
	}


}

Game::~Game()
{
	for (int i = 0; i < countCards; i++) {
		delete hand[i];
		std::cout << "card " << i << " in your hand was cleaned" << std::endl;
	}
	if (Mod == 1) {
		easyBot->~EasyBot();
		for (int i = 0; i < 6; i++) {
			TableRectangles[i]->~Table();
		}
		SDL_DestroyTexture(TableTex);
		SDL_DestroyTexture(DeckTex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	else if (Mod == 2 && UnderControl) {
		delete firstBot;
		delete secondBot;
		SDL_DestroyTexture(TableTex);
		SDL_DestroyTexture(DeckTex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	else {
		delete firstBot;
		delete secondBot;
	}
	delete deck;
	delete trumpCard;
}


// There we have a handling events 
int Game::HandleEvents()
{
	switch (Mod)
	{
	case 1: {
		botEvents();
		CanBotMove = false;
		personEvents();

		break;
	}
	case 2: {
		if (UnderControl) {
			
			botEventsFirst();

			secondBot->cardsInDeck = cardsInDeck;
			secondBot->cardsInOpponentHand = firstBot->upCount(0);
			botEventsSecond();

			firstBot->cardsInDeck = cardsInDeck;
			firstBot->cardsInOpponentHand = secondBot->upCount(0);
			personControl();
		}
		else {
			int remBefore = 0,
				remAfter = 0;

			for (int i = 0; i < 6; i++) {
				if (TableRectangles[i]->isCardOn) {
					remBefore = i+1;
				}
			}
			firstBot->cardsInDeck = cardsInDeck;
			firstBot->cardsInOpponentHand = secondBot->upCount(0);
			botEventsFirst();

			secondBot->cardsInDeck = cardsInDeck;
			secondBot->cardsInOpponentHand = firstBot->upCount(0);
			botEventsSecond();
			
			for (int i = 0; i < 6; i++) {
				if (TableRectangles[i]->isCardOn) {
					remAfter = i + 1;
				}
			}
			if (remBefore == remAfter) {
				if (whichTurn == 0) {
					for (int i = 0; i < 6; i++) {
						if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
							ifTaken = true;
							takeCardBotFirst();
							break;
						}
					}
				}
				if (whichTurn == 1) {
					for (int i = 0; i < 6; i++) {
						if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
							ifTaken = true;
							takeCardBotSecond();
							break;
						}
					}
				}
				newRaundBattle();
			}

			if (cardsInDeck == 0) {
				if (firstBot->upCount(0) == 0 && secondBot->upCount(0) > 0) {
					isRunning = false;
					return 1;//победил 1
				}
				else if (firstBot->upCount(0) > 0 && secondBot->upCount(0) == 0) {
					isRunning = false;
					return 2;//победил 2
				}
				else if (firstBot->upCount(0) == 0 && secondBot->upCount(0) == 0) {
					isRunning = false;
					return 0;//ничья
				}
			}
		}
		break;
	}
	default:
		break;
	}
	return 0;
}
void Game::botEvents()
{
	if (whichTurn == 0 && CanBotMove) {//ОЧЕРЕДЬ БОТА
		int remValue = 0;
		for (int i = 0; i < 6; i++) {
			if (!TableRectangles[i]->isCardOn) {
				TableRectangles[i]->isCardOn =
					easyBot->CardMove(TableRectangles[i]->xpos, remValue, TableRectangles[i]); 
				if(TableRectangles[i]->isCardOn)
					remValue = TableRectangles[i]->Card->card.value;
			}	
			else {
				remValue = TableRectangles[i]->Card->card.value;
			}
		}
		for (int i = 0; i<6; i++){
			if (TableRectangles[i]->isSecCardOn) {
					remValue = TableRectangles[i]->CardOn->card.value;
					for (int y = 0; y<6; y++)
					{
						if (!TableRectangles[y]->isCardOn) {
							TableRectangles[y]->isCardOn =
								easyBot->CardMove(TableRectangles[y]->xpos, remValue, TableRectangles[y]);
						}
					}
			}
		}
	}
	else if(whichTurn == 1) {//БОТ КРОЕТСЯ 
		for (int i = 0; i < 6; i++) {
			if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->isSecCardOn = 
					easyBot->CardCover(TableRectangles[i]->xpos, TableRectangles[i]->Card->card, TableRectangles[i]);
				break;
			}
		}
	}
}
void Game::botEventsFirst()
{
	if (whichTurn == 1) {//ОЧЕРЕДЬ БОТА
		int remValue = 0;
		for (int i = 0; i < 6; i++) {
			if (!TableRectangles[i]->isCardOn) {
				TableRectangles[i]->isCardOn =
					firstBot->CardMove(TableRectangles[i]->xpos, remValue, TableRectangles[i]);
				break;
				if (TableRectangles[i]->isCardOn)
					remValue = TableRectangles[i]->Card->card.value;
			}
			else {
				remValue = TableRectangles[i]->Card->card.value;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (TableRectangles[i]->isSecCardOn) {
				remValue = TableRectangles[i]->CardOn->card.value;
				for (int y = 0; y < 6; y++)
				{
					if (!TableRectangles[y]->isCardOn) {
						TableRectangles[y]->isCardOn =
							firstBot->CardMove(TableRectangles[y]->xpos, remValue, TableRectangles[y]);
					}
				}
			}
		}
	}
	else if (whichTurn == 0) {//БОТ КРОЕТСЯ 
		for (int i = 0; i < 6; i++) {
			if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->isSecCardOn =
					firstBot->CardCover(TableRectangles[i]->xpos, TableRectangles[i]->Card->card, TableRectangles[i]);
			}
		}
	}
}
void Game::botEventsSecond()
{
	if (whichTurn == 0) {//ОЧЕРЕДЬ БОТА
		int remValue = 0;
		for (int i = 0; i < 6; i++) {
			if (!TableRectangles[i]->isCardOn) {
				TableRectangles[i]->isCardOn =
					secondBot->CardMove(TableRectangles[i]->xpos, remValue, TableRectangles[i]);
				if (TableRectangles[i]->isCardOn)
					remValue = TableRectangles[i]->Card->card.value;
			}
			else {
				remValue = TableRectangles[i]->Card->card.value;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (TableRectangles[i]->isSecCardOn) {
				remValue = TableRectangles[i]->CardOn->card.value;
				for (int y = 0; y < 6; y++)
				{
					if (!TableRectangles[y]->isCardOn) {
						TableRectangles[y]->isCardOn =
							secondBot->CardMove(TableRectangles[y]->xpos, remValue, TableRectangles[y]);
					}
				}
			}
		}
	}
	else if (whichTurn == 1) {//БОТ КРОЕТСЯ 
		for (int i = 0; i < 6; i++) {
			if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->isSecCardOn =
					secondBot->CardCover(TableRectangles[i]->xpos, TableRectangles[i]->Card->card, TableRectangles[i]);
				break;
			}
		}
	}
}
void Game::personEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN: {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			if (whichTurn == 0) {
				for (int i = 0; i < 6; i++) {
					if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
						ifTaken = true;
						takeCardPerson();
						break;
					}
				}
			}
			if (whichTurn == 1) {
				for (int i = 0; i < 6; i++) {
					if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
						ifTaken = true;
						takeCardBot();
						break;
					}
				}
			}
			newRaund();
			if (cardsInDeck == 0) {
				if (easyBot->upCount(0) == 0 && countCards > 0) {
					std::cout << "Bot has won" << std::endl;
					isRunning = false;
				}
				else if (countCards == 0 && easyBot->upCount(0) > 0) {
					std::cout << "Person has won" << std::endl;
					isRunning = false;
				}
				else if (countCards == 0 && easyBot->upCount(0) == 0) {
					std::cout << "This wonderfull game finished with draw" << std::endl;
					isRunning = false;
				}
			}
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		int curPosX, curPosY;
		SDL_GetMouseState(&curPosX, &curPosY);

		for (int i = 0; i < countCards; i++) {
			if (hand[i]->isOnTable == false &&
				curPosX > hand[i]->xpos && curPosX < hand[i]->xpos + 71 &&
				curPosY > hand[i]->ypos && curPosY < hand[i]->ypos + 96) {
				whichMoving = i;
				break;
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		if (whichTurn == 1) {
			stroke();
		}
		else if (whichTurn == 0) {
			cover();
		}
		whichMoving = -1;
		break;
	}
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::personControl() 
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN: {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: {
			if (whichTurn == 0) {
				for (int i = 0; i < 6; i++) {
					if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
						ifTaken = true;
 						takeCardBotFirst();
						break;
					}
				}
			}
			if (whichTurn == 1) {
				for (int i = 0; i < 6; i++) {
					if (TableRectangles[i]->isCardOn && !TableRectangles[i]->isSecCardOn) {
						ifTaken = true;
						takeCardBotSecond();
						break;
					}
				}
			}
			newRaundBattle();
			if (cardsInDeck == 0) {
				if (firstBot->upCount(0) == 0 && secondBot->upCount(0) > 0) {
					std::cout << "First bot has won" << std::endl;
					isRunning = false;
				}
				else if (firstBot->upCount(0) > 0 && secondBot->upCount(0) == 0) {
					std::cout << "Second bot has won" << std::endl;
					isRunning = false;
				}
				else if (firstBot->upCount(0) == 0 && secondBot->upCount(0) == 0) {
					std::cout << "This wonderfull game finished with draw" << std::endl;
					isRunning = false;
				}
			}
			break;
		}
		}
		break;
	}
	case SDL_QUIT: {
		isRunning = false;
		break;
	}
	default:
		break;
	}

}


void Game::update()
{
	point->update(whichTurn);
	switch (Mod)
	{
	case 1: {
		updateGame();
		break;
	}
	case 2: {
		updateBattle();
		break;
	}
	default:
		break;
	}

}
void Game::updateGame()
{
	trumpCard->UpdateJust();
	deckRect.h = 100;
	deckRect.w = 71;
	deckRect.x = 690;
	deckRect.y = 200;


	if (whichMoving != -1) {
		for (int i = 0; i < 6; i++) {
			TableRectangles[i]->Update();
		}
	}
	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			TableRectangles[i]->Card->UpdateJust();
			if (TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->CardOn->UpdateJust();
			}
		}
	}
	for (int i = 0; i < countCards; i++) {
		if (i != whichMoving) {
			hand[i]->UpdateJust();
		}
		else {
			hand[i]->UpdateMoving();
		}

	}
	for (int i = 0; i < easyBot->upCount(0); i++) {
		easyBot->hand[i]->UpdateJust();
	}
}
void Game::updateBattle() 
{
	trumpCard->UpdateJust();
	deckRect.h = 100;
	deckRect.w = 71;
	deckRect.x = 690;
	deckRect.y = 200;

	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			TableRectangles[i]->Card->UpdateJust();
			if (TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->CardOn->UpdateJust();
			}
		}
	}

	for (int i = 0; i < firstBot->upCount(0); i++) {
		firstBot->hand[i]->UpdateJust();
	}
	for (int i = 0; i < secondBot->upCount(0); i++) {
		secondBot->hand[i]->UpdateJust();
	}
}

//There we will render our objects on the screen 
void Game::render()
{
	switch (Mod)
	{
	case 1: {
		renderGame();
		break;
	}
	case 2: {
		renderBattle();
		break;
	}
	default:
		break;
	}
}

void Game::renderGame() {
	//FIRSTLY CLEAR THE BUFFER 
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, TableTex, NULL, NULL);
	trumpCard->Render();
	point->render();
	SDL_RenderCopyEx(renderer, DeckTex, NULL, &deckRect, 90, NULL, SDL_FLIP_VERTICAL);
	if (whichMoving != -1) {
		for (int i = 0; i < 6; i++) {
			TableRectangles[i]->Render();
		}
	}
	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			TableRectangles[i]->Card->Render();
			if (TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->CardOn->Render();
			}
		}
	}
	if (whichTurn == 1) {//если кроется бот
		for (int i = 0; i < countCards; i++) {
			hand[i]->Render();
		}
		for (int i = 0; i < easyBot->upCount(0); i++) {
			easyBot->hand[i]->Render();
		}
	}
	else//если кроется пользователь
	{
		for (int i = 0; i < easyBot->upCount(0); i++) {
			easyBot->hand[i]->Render();
		}
		for (int i = 0; i < countCards; i++) {
			hand[i]->Render();
		}

	}
	//adding stuff to renderer
	SDL_RenderPresent(renderer);//Updating the screen with any rendering performed since the previous call.

}
void Game::renderBattle()
{
	//FIRSTLY CLEAR THE BUFFER 
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, TableTex, NULL, NULL);
	trumpCard->Render();
	point->render();
	SDL_RenderCopyEx(Game::renderer, DeckTex, NULL, &deckRect, 90, NULL, SDL_FLIP_VERTICAL);

	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			TableRectangles[i]->Card->Render();
			if (TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->CardOn->Render();
			}
		}
	}
	if (whichTurn == 1) {//если кроется первый бот
		for (int i = 0; i < secondBot->upCount(0); i++) {
			secondBot->hand[i]->Render();
		}
		for (int i = 0; i < firstBot->upCount(0); i++) {
			firstBot->hand[i]->Render();
		}
	}
	else//если кроется второй бот 
	{
		for (int i = 0; i < firstBot->upCount(0); i++) {
			firstBot->hand[i]->Render();
		}
		for (int i = 0; i < secondBot->upCount(0); i++) {
			secondBot->hand[i]->Render();
		}

	}
	//adding stuff to renderer
	SDL_RenderPresent(Game::renderer);//Updating the screen with any rendering performed since the previous call.

}

bool Game::stroke()
{
	int curPosX, 
		curPosY;

	bool isEmpty = true;
	SDL_GetMouseState(&curPosX, &curPosY);

	for (int i = 0; i < 6; i++) {
		if (whichMoving != -1 && inRectangle(curPosX, TableRectangles[i]->xpos, curPosY, TableRectangles[i]->ypos) &&
			!(TableRectangles[i]->isCardOn)){ 
			for (int j = 0; j < 6; j++) {
				if (TableRectangles[j]->isCardOn) {
					isEmpty = false;
				}
				if (TableRectangles[j]->isCardOn && TableRectangles[j]->Card->card.value == hand[whichMoving]->card.value) {
					TableRectangles[i]->isCardOn = true;
					hand[whichMoving]->FixCard(TableRectangles[i]->xpos, TableRectangles[i]->ypos);
					TableRectangles[i]->Card = hand[whichMoving];

					for (int y = whichMoving; y < countCards - 1; y++) {
						hand[y + 1]->xpos -= cardStep;
						hand[y] = hand[y + 1];
					}
					hand[countCards - 1] = nullptr;
					countCards--;
					return true;
				}
				else if (TableRectangles[j]->isSecCardOn && TableRectangles[j]->CardOn->card.value == hand[whichMoving]->card.value) {
					TableRectangles[i]->isCardOn = true;
					hand[whichMoving]->FixCard(TableRectangles[i]->xpos, TableRectangles[i]->ypos);
					TableRectangles[i]->Card = hand[whichMoving];

					for (int y = whichMoving; y < countCards - 1; y++) {
						hand[y + 1]->xpos -= cardStep;
						hand[y] = hand[y + 1];
					}
					hand[countCards - 1] = nullptr;
					countCards--;
					return true;
				}
			}
			if (isEmpty) {
				TableRectangles[i]->isCardOn = true;
				hand[whichMoving]->FixCard(TableRectangles[i]->xpos, TableRectangles[i]->ypos);
				TableRectangles[i]->Card = hand[whichMoving];

				for (int y = whichMoving; y < countCards - 1; y++) {
					hand[y + 1]->xpos -= cardStep;
					hand[y] = hand[y + 1];
				}
				hand[countCards - 1] = nullptr;
				countCards--;
				return true;
			}
		}
	}

	return false;
}

bool Game::cover()
{
	int curPosX, curPosY;
	SDL_GetMouseState(&curPosX, &curPosY);
	for (int i = 0; i < 6; i++) {
		if (whichMoving != -1 && inRectangle(curPosX, TableRectangles[i]->xpos, curPosY, TableRectangles[i]->ypos)
			&& TableRectangles[i]->isCardOn) {
			if ((hand[whichMoving]->card.suit == TableRectangles[i]->Card->card.suit &&
				hand[whichMoving]->card.value > TableRectangles[i]->Card->card.value)//cards, that have one suit
				||
				(hand[whichMoving]->card.suit == deck->m_trump.suit && //when person want cover by trump 
					TableRectangles[i]->Card->card.suit != deck->m_trump.suit)){

				TableRectangles[i]->isSecCardOn = true;
				hand[whichMoving]->FixCard(TableRectangles[i]->xpos + 20, TableRectangles[i]->ypos + 20);
				TableRectangles[i]->CardOn = hand[whichMoving];

				for (int y = whichMoving; y < countCards - 1; y++) {
					hand[y + 1]->xpos -= cardStep;
					hand[y] = hand[y + 1];
				}
				hand[countCards - 1] = nullptr;
				countCards--;
				CanBotMove = true;
				return true;
			}
		}
	}

	return false;

}

void Game::takeCardPerson()
{
	int i = 0;
	while(TableRectangles[i]->isCardOn){
		hand[countCards] = TableRectangles[i]->Card;
		hand[countCards]->xpos = cardPos + (cardStep * countCards);
		hand[countCards]->ypos = 520;
		hand[countCards]->Bot = false;
		hand[countCards]->isOnTable = false;
 		countCards++;
		if (TableRectangles[i]->isSecCardOn) {
			hand[countCards] = TableRectangles[i]->CardOn;
			hand[countCards]->xpos = cardPos + (cardStep * countCards);
			hand[countCards]->ypos = 520;
			hand[countCards]->Bot = false;
			hand[countCards]->isOnTable = false;
			countCards++;
		}
		i++;
	}
}
void Game::takeCardBotFirst()
{
	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			firstBot->hand[firstBot->upCount(0)] = TableRectangles[i]->Card;
			firstBot->hand[firstBot->upCount(0)]->xpos = cardPos + (cardStep * firstBot->upCount(0));
			firstBot->hand[firstBot->upCount(0)]->ypos = 520;
			firstBot->hand[firstBot->upCount(0)]->Bot = true;
			firstBot->hand[firstBot->upCount(0)]->isOnTable = false;
			firstBot->upCount(1);
			if (TableRectangles[i]->isSecCardOn) {
				firstBot->hand[firstBot->upCount(0)] = TableRectangles[i]->CardOn;
				firstBot->hand[firstBot->upCount(0)]->xpos = cardPos + (cardStep * firstBot->upCount(0));
				firstBot->hand[firstBot->upCount(0)]->ypos = 520;
				firstBot->hand[firstBot->upCount(0)]->Bot = true;
				firstBot->hand[firstBot->upCount(0)]->isOnTable = false;
				firstBot->upCount(1);
			}
		}
	}
}
void Game::takeCardBotSecond()
{
	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			secondBot->hand[secondBot->upCount(0)] = TableRectangles[i]->Card;
			secondBot->hand[secondBot->upCount(0)]->xpos = cardPos + (cardStep * secondBot->upCount(0));
			secondBot->hand[secondBot->upCount(0)]->ypos = 10;
			secondBot->hand[secondBot->upCount(0)]->Bot = true;
			secondBot->hand[secondBot->upCount(0)]->isOnTable = false;
			secondBot->upCount(1);
			if (TableRectangles[i]->isSecCardOn) {
				TableRectangles[i]->isSecCardOn = false;
				secondBot->hand[secondBot->upCount(0)] = TableRectangles[i]->CardOn;
				secondBot->hand[secondBot->upCount(0)]->xpos = cardPos + (cardStep * secondBot->upCount(0));
				secondBot->hand[secondBot->upCount(0)]->ypos = 10;
				secondBot->hand[secondBot->upCount(0)]->Bot = true;
				secondBot->hand[secondBot->upCount(0)]->isOnTable = false;
				secondBot->upCount(1);
			}
		}
	}
}


void Game::takeCardBot()
{
	for (int i = 0; i < 6; i++) {
		if (TableRectangles[i]->isCardOn) {
			easyBot->hand[easyBot->upCount(0)] = TableRectangles[i]->Card;
			easyBot->hand[easyBot->upCount(0)]->xpos = cardPos + (cardStep * easyBot->upCount(0));
			easyBot->hand[easyBot->upCount(0)]->ypos = 10;
			easyBot->hand[easyBot->upCount(0)]->Bot = true;
			easyBot->hand[easyBot->upCount(0)]->isOnTable = false;
			easyBot->upCount(1);
			if (TableRectangles[i]->isSecCardOn) {
				easyBot->hand[easyBot->upCount(0)] = TableRectangles[i]->CardOn;
				easyBot->hand[easyBot->upCount(0)]->xpos = cardPos + (cardStep * easyBot->upCount(0));
				easyBot->hand[easyBot->upCount(0)]->ypos = 10;
				easyBot->hand[easyBot->upCount(0)]->Bot = true;
				easyBot->hand[easyBot->upCount(0)]->isOnTable = false;
				easyBot->upCount(1);
			}
		}
	}
}

bool Game::inRectangle(int MoveX,int borderX, int MoveY, int borderY) {
	if (MoveX > borderX && MoveX < borderX + 71 &&
		MoveY > borderY && MoveY < borderY + 96) {
		return true;
	}
	return false;
}

void Game::newRaund()
{
	CanBotMove = true;
	if (whichTurn == 0) {
		if (!ifTaken) {
			whichTurn = 1;//Очередь человека
		}
		cardDisplace = cardStep * easyBot->upCount(0);
		while (easyBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			easyBot->hand[easyBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 10, true);
			cardDisplace += cardStep;
			easyBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = cardStep * countCards;
		while (countCards < 6) {
			if (cardsInDeck == 0)
				break;
			hand[countCards] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 520, false);
<<<<<<< HEAD
			__asm {
				mov eax, cardDisplace
				mov ebx, cardStep
				add eax, ebx
				mov cardDisplace, eax
				inc countCards
				dec cardsInDeck
			}
		//	cardDisplace += cardStep;
			//countCards++;
			//cardsInDeck--;
=======
			cardDisplace += cardStep;
			countCards++;
			cardsInDeck--;
>>>>>>> 6c4ad19 (5th)
		}
		cardDisplace = 0;
	}
	else {
		if (!ifTaken) {
			whichTurn = 0;//Очередь бота
		}
		cardDisplace = cardStep * countCards;
		while (countCards < 6) {
			if (cardsInDeck == 0)
				break;
			hand[countCards] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 520, false);
<<<<<<< HEAD
			__asm {
				mov eax, cardDisplace
				mov ebx, cardStep
				add eax, ebx
				mov cardDisplace, eax
				inc countCards
				dec cardsInDeck
			}
			//cardDisplace += cardStep;
			//countCards++;
			//cardsInDeck--;
=======
			cardDisplace += cardStep;
			countCards++;
			cardsInDeck--;
>>>>>>> 6c4ad19 (5th)
		}
		cardDisplace = cardStep * easyBot->upCount(0);
		while (easyBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			easyBot->hand[easyBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 10, true);
			cardDisplace += cardStep;
			easyBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = 0;
	}

	for (int i = 0; i < 6; i++) {
		delete(TableRectangles[i]);
	}

	for (int i = 0; i < 6; i++) {
		TableRectangles[i] = new Table("bitmaps/PlaceForCard.bmp", rectPosX + (rectStep * i), rectPosY);
	}
	easyBot->cardsInDeck = cardsInDeck;
	easyBot->cardsInOpponentHand = countCards;
	ifTaken = false;
}
void Game::newRaundBattle()
{
	if (whichTurn == 0) {//очередь 1 
		if (!ifTaken) {
			whichTurn = 1;//Очередь второго бота
		}
		cardDisplace = cardStep * firstBot->upCount(0);
		while (firstBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			firstBot->hand[firstBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 520, true);
			cardDisplace += cardStep;
			firstBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = cardStep * secondBot->upCount(0);
		while (secondBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			secondBot->hand[secondBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 10, true);
			cardDisplace += cardStep;
			secondBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = 0;
	}
	else {
		if (!ifTaken) {
			whichTurn = 0;//Очередь 1 бота
		}
		cardDisplace = cardStep * secondBot->upCount(0);
		while (secondBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			secondBot->hand[secondBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 10, true);
			cardDisplace += cardStep;
			secondBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = cardStep * firstBot->upCount(0);
		while (firstBot->upCount(0) < 6) {
			if (cardsInDeck == 0)
				break;
			firstBot->hand[firstBot->upCount(0)] = new GameObject(deck->GiveCard(), cardPos + cardDisplace, 520, true);
			cardDisplace += cardStep;
			firstBot->upCount(1);
			cardsInDeck--;
		}
		cardDisplace = 0;
	}

	for (int i = 0; i < 6; i++) {
		delete(TableRectangles[i]);
	}

	for (int i = 0; i < 6; i++) {
		TableRectangles[i] = new Table("bitmaps/PlaceForCard.bmp", rectPosX + (rectStep * i), rectPosY);
	}
	firstBot->cardsInDeck = cardsInDeck;
	firstBot->cardsInOpponentHand = secondBot->upCount(0);

	secondBot->cardsInDeck = cardsInDeck;
	secondBot->cardsInOpponentHand = firstBot->upCount(0);
	ifTaken = false;
}


