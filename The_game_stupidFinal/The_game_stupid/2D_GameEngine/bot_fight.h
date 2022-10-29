#pragma once
#include "bot.h"
#include <iostream>
#include "Table_for_bot.h"
#include "deck.h"



void TakeCardBot(EasyBotik* bot, bTable* table);
void NewRaund(EasyBotik* bot_1, EasyBotik* bot_2, bTable* table);
void botEvents(EasyBotik* bot, bTable* table, int botNum);

void Bot_battle(int numOfGames);

