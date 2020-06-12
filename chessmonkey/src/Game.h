#pragma once

// This will contain everything related to the game, such as board state, current eligible moves, etc.
//			A full list should be created soon.

// Right now some things might need to be cleaned up, but I haven't decided on how to do that yet.


#include <utility>
#include <list>

// All the types of pieces in chess
enum class Piece {
	_, p, K, Q, B, N, R
};

typedef std::pair<char, int> Square;

// Move struct (might change to a class)
struct Move {
	Square destination;
	Piece piece;
	bool captures;
	Square location;	// Sometimes necessary if two pieces can land on the same square
};

class Game {

private:

	unsigned short currentTurn;
	std::list<Move> movesMade;	// A list of all the moves made this game

	bool blackCanCastle, whiteCanCastle; 
	

public:

	Game() : currentTurn(1), blackCanCastle(1), whiteCanCastle(1) {}
	~Game() {}

	void startGame();

};

