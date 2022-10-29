#pragma once

#include<SDL.h>
#include <SDL_image.h>
#include <iostream>


class Game {
public:
	Game(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen,int mod,bool control);
	~Game();

	int HandleEvents();
	void personEvents();
	void botEvents();
	void botEventsFirst();
	void botEventsSecond();
	void personControl();


	void update();
	void updateGame();
	void updateBattle();

	void render();
	void renderGame();
	void renderBattle();

	void newRaund();
	void newRaundBattle();

	void takeCardPerson();
	void takeCardBot();
	void takeCardBotFirst();
	void takeCardBotSecond();

	bool stroke();
	bool cover();
	bool inRectangle(int MoveX, int borderX, int MoveY, int borderY);

	static SDL_Renderer* renderer;

	bool running() { return isRunning; };
private:
	bool isRunning;
	SDL_Window* window = nullptr;
};