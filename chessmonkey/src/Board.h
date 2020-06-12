#pragma once

// This class will contain the state of the board, i.e. a 
//		list of all squares and which pieces are at each square.

// Potentially an update board state function should be implemented next,
//		and an initialize board, maybe just initialize the board in the 
//		default constructor

#include <map>
#include <fstream>
#include <string>

#include "Piece.h"

class Board {

private:
	std::map<std::string, Piece> boardState; // Each Location has a piece and a square.

public:
	Board(); // Set up squares

	std::map<std::string, Piece>& getBoardState();

	friend std::ostream& operator <<(std::ostream& out, Board& b);
	
};