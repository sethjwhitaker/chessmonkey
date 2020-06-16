#pragma once

// This class is what a human player and the chess AI will interact with.
// This class will in turn, interact with the game class, which will handle 
//				all aspects related to the actual game.
// Essentially this class should contain an api that can be accessed through a 
//				player controlled interface, or an AI controlled interface.

// What functions do a human need in order to play chess?
//		1. Make Move

	
// What functions might an AI need?
//		1. Get legal moves

#include <vector>
#include <utility>
#include <string>

class Player {

private:
	std::vector<std::pair<char, int>> possibleMoves;
	std::string color;

public:
	std::string getColor() {
		return color;
	}
	void setColor(std::string newColor) {
		color = newColor;
	}


};

