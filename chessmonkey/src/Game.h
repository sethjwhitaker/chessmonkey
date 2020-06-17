#pragma once

// This will contain everything related to the game, such as board state, current eligible moves, etc.
//			A full list should be created soon.

// Right now some things might need to be cleaned up, but I haven't decided on how to do that yet.


#include <utility>
#include <list>
#include <string>
#include <time.h>

#include "Board.h"
#include "Player.h"

class Player;



class Game {

private:

	unsigned short currentMove;
	std::list<Move> movesMade;	// A list of all the moves made this game

	bool blackCanCastle, whiteCanCastle; // whether each player can castle
	bool whitesTurn; // True if white's turn false if black's turn

	Board board; // Board holding board state data

	Player *black, *white;
	
	

public:

	Game() : currentMove(1), blackCanCastle(1), whiteCanCastle(1), whitesTurn(1), 
		board(Board()), black(nullptr), white(nullptr) {}

	~Game() {}

	void setPlayer(Player& player); // Queues player into game. Picks random color.
	void setPlayer(Player& player, std::string color); // Queues player into game, with color preference.

	bool isMyTurn(std::string color);

	Board& getBoard();

	Player& getBlackPlayer();

	Player& getWhitePlayer();

	void startGame();

	bool movePiece(std::string moveString, const Player* player); // Player color is a temporary way to identify which player is calling the function

};

