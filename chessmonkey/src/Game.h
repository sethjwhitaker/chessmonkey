#pragma once
#include <utility>
#include <list>

#include "Player.h"

class Game {

private:

	Player black;	// The player playing black
	Player white;	// The player playing white

	std::list<std::pair<char, int>> movesMade;	// A list of all the moves made this game
	
public:

	Game() {}
	~Game() {}

	void startGame();
};

