#pragma once
#include <iostream>




struct CardBot {
	int value = 0;
	int suit = 0;
};


struct bTable {
	struct CardBot put;
	struct CardBot cover;
};
