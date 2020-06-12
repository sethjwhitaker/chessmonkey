#pragma once

// This will contain everything related to the game, such as board state, current eligible moves, etc.
//			A full list should be created soon.

// Right now some things might need to be cleaned up, but I haven't decided on how to do that yet.


#include <utility>
#include <list>
#include <string>

#include "Board.h"



// Move struct (might change to a class)
struct Move {
	std::string destination;
	Piece piece;
	bool captures;
	std::string location;	// Sometimes necessary if two pieces can land on the same square
};

class Game {

private:

	unsigned short currentMove;
	std::list<Move> movesMade;	// A list of all the moves made this game

	bool blackCanCastle, whiteCanCastle; // whether each player can castle

	Board board;
	

public:

	Game() : currentMove(1), blackCanCastle(1), whiteCanCastle(1) {}
	~Game() {}

	void startGame();

	Board& getBoard();

};

