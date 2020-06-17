#include "Game.h"
#include <iostream>

namespace {

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

	Move moveStringParse(std::string moveString, bool isBlack) {
		using std::cout;
		Move move;
		move.destination = moveString.substr(1, 2);
		move.piece = { charToPieceType(moveString[0]), isBlack, "" }; // change to type of piece
		move.captures = 0;
	
		cout << move;

		return move;
	}

	bool verifyMove(Move& move, Board& board) {

		Piece** pieces = board.getPieces();
		Piece* target = nullptr;
		for (int i = 0; i < 32; i++) {
			Piece* currentPiece = pieces[i];
			if (currentPiece != nullptr && move.piece.isBlack == currentPiece->isBlack
				&& currentPiece->type == move.piece.type) {

				move.piece.square = currentPiece->square;
			}
		}

		return 1;
	}

}

void Game::setPlayer(Player& player) {

	player.setGame(this); // Assign Game to player
	
	// Assign Player to game
	
	if (white == nullptr && black == nullptr) { 
		// If neither white or black have been chosen yet
		// Pick random color for player
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

bool Game::movePiece(std::string moveString, const Player* player) {
	bool isBlack;
	// Make sure it is the player's turn and figure out the color
	if (player->getColor() == "black") {
		if(whitesTurn)
			return false;
		isBlack = 1;
	} else if (player->getColor() == "white") {
		if (!whitesTurn)
			return false;
		isBlack = 0;
	} else {
		return false;
	}

	// parse move string
	Move move = moveStringParse(moveString, isBlack);

	if(verifyMove(move, board)) board.movePiece(move);

	return true;
}



