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
		std::vector<Piece*> candidates;
		// Find pieces that are the same color and type as the move specifies
		for (int i = 0; i < 32; i++) {
			Piece* currentPiece = pieces[i]; // current piece in pieces array
			// if current piece is not null AND is same color as move piece AND is the same type as move piece
			if (currentPiece != nullptr && move.piece.isBlack == currentPiece->isBlack 
				&& currentPiece->type == move.piece.type) {

				candidates.push_back(currentPiece);
			}
		}

		std::vector<Piece*> narrowedCand;

		// Go through candidates and see if any are legal moves
		switch (move.piece.type) {

		case TypeofPiece::_:

			return 0;
		case TypeofPiece::p: // Pawn moves: 1 space forward
							 //				if on rank 2 for white or rank 7 for black, move 2 spaces
							 //				if captures can move diagonally
							 //				if on rank 5 for white or rank 4 for black, en passant
							 //				if on rank 8 for white or rank 1 for black, choose piece

			for (int i = 0; i < candidates.size(); i++) { // go through candidates
				Piece* candidate = candidates[i];	// Current candidate
				char file = candidate->square[0];	// file of cand square
				char rank = candidate->square[1];	// rank of cand square
				if (move.piece.isBlack) {
					if (move.destination[1] == rank - 1) { // if 1 space in front of cand
						narrowedCand.push_back(candidate);
					}
				}

			}
			break;

		case TypeofPiece::K:	// King move: 1 file OR 1 rank away
								
		{
			Piece* candidate = candidates[0];
			if (abs(move.destination[1] - candidate->square[1]) == 1 ||
				abs(move.destination[0] - candidate->square[0]) == 1) {

				narrowedCand.push_back(candidate);
			}
		}

			break;

		case TypeofPiece::Q:

			break;

		case TypeofPiece::B: 

			break;

		case TypeofPiece::N:	// Knight moves: Either 1 file away AND 2 ranks away
								//				 Or 1 rank away AND 2 files away
			for (int i = 0; i < candidates.size(); i++) {
				Piece* candidate = candidates[i];
				if (abs(move.destination[1] - candidate->square[1]) == 1 && 
					abs(move.destination[0] - candidate->square[0]) == 2 ||
					abs(move.destination[1] - candidate->square[1]) == 2 && 
					abs(move.destination[0] - candidate->square[0]) == 1) {

					narrowedCand.push_back(candidate);
				}
					
			}

			break;

		case TypeofPiece::R:	// Rook moves: 0 files or 0 ranks away
								//			   there is no piece in the way
								//				moves at least 1 space

			for (int i = 0; i < candidates.size(); i++) {
				Piece* candidate = candidates[i];
				if ((abs(move.destination[1] - candidate->square[1]) == 0 || // 0 file or rank away
					abs(move.destination[0] - candidate->square[0]) == 0) &&
					(abs(move.destination[1] - candidate->square[1]) > 1 || // move at least 1 space
					abs(move.destination[0] - candidate->square[0]) > 1)) {

					narrowedCand.push_back(candidate);
				}
			}

			break;
			
		default:
			return 0;
		}

		// "Assign move" and return 1 if successful
		if (narrowedCand.size() == 1) {
			move.piece.square = narrowedCand[0]->square;
			return 1;
		} else
			return 0;

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

void Game::setPlayer(Player& player, std::string color) {
	player.setGame(this); // Assign Game to player

	if (color == "black" && black == nullptr) {
		black = &player;
		player.setColor("black");
	} else if (color == "white" && white == nullptr) {
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

	if (verifyMove(move, board)) {
		board.movePiece(move);
		whitesTurn = !whitesTurn; // change turns
		return true;
	}

	return false;
	
}



