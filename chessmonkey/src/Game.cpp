#include "Game.h"

namespace {

	Move moveStringParse(std::string moveString, bool isBlack) {
		Move move;
		move.piece = { charToPieceType(moveString[0]), isBlack, moveString.substr(1, 2) }; // change to type of piece
	
		
	}

	TypeofPiece charToPieceType(char c) {

		switch (c) {
		case 'P':
			return TypeofPiece::p;
		case 'K':
			return TypeofPiece::K;
		case 'Q':
			return TypeofPiece::Q;
		case 'B':
			return TypeofPiece::B;
		case 'N':
			return TypeofPiece::N;
		case 'R':
			return TypeofPiece::R;
		default:
			return TypeofPiece::_;
		}
	}

}

void Game::setPlayer(Player& player) {
	
	// Assign Player to game
	
	if (white == nullptr && black == nullptr) { 
		// If neither white or black have been chosen yet
		// Pick random color for player
		srand(2135);
		int r = rand();
		if (r % 2 == 0) {
			black = &player;
			player.setColor("black");
		} else {
			white = &player;
			player.setColor("white");
		}
	// Otherwise assign the player to the null pointer
	} else if (black == nullptr) {
		black = &player;
		player.setColor("black");
	} else {
		white = &player;
		player.setColor("white");
	}
	
}

bool Game::isMyTurn(std::string color) {
	if (color == "white" || color == "White")
		return whitesTurn;
	else
		return !whitesTurn;
}

Board& Game::getBoard() {

	return board;

}

Player& Game::getBlackPlayer() {
	return *black;
}

Player& Game::getWhitePlayer() {
	return *white;
}

void Game::startGame() {
	board = Board();
}

bool Game::movePiece(std::string moveString, std::string playerColor) {

	// Make sure it is the player's turn
	if (playerColor == "black" && whitesTurn) {
		return false;
	} else if (playerColor == "white" && !whitesTurn) {
		return false;
	}



	return true;
}



