#include "Game.h"
#include <iostream> // Just for debugging

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

	

	bool verifyMove(Move& move, Board& board) {

		Piece** pieces = board.getPieces();
		std::vector<Piece*> candidates;
		// Find pieces that are the same color and type as the move specifies
		for (int i = 0; i < 32; i++) {
			Piece* currentPiece = pieces[i]; // current piece in pieces array
			// if current piece is not null AND is same color as move piece AND is the same type as move piece
			if (currentPiece != nullptr && move.piece.color == currentPiece->color 
				&& currentPiece->type == move.piece.type) {

				candidates.push_back(currentPiece);
			}
		}

		std::vector<Piece*> narrowedCand;

		// Go through candidates and see if any are legal moves
		switch (move.piece.type) {

		case TypeofPiece::_:
			std::cout << "\nERROR verifyMove: No piece selected!";
			return 0;
		case TypeofPiece::p: // Pawn moves: 1 space forward
							 //				if on rank 2 for white or rank 7 for black, move 2 spaces
							 //				if captures can move diagonally
							 //				if on rank 5 for white or rank 4 for black, en passant
							 //				if on rank 8 for white or rank 1 for black, choose piece

			for (int i = 0; i < candidates.size(); i++) { // go through candidates
				Piece* candidate = candidates[i];	// Current candidate
				char file = candidate->square.file;	// file of cand square
				char rank = candidate->square.rank;	// rank of cand square
				if (move.piece.color == PieceColor::Black) {
					if (move.destination.rank == rank - 1) { // if 1 space in front of cand
						narrowedCand.push_back(candidate);
					}
				}

			}
			break;

		case TypeofPiece::K:	// King move: 1 file OR 1 rank away
								
		{
			Piece* candidate = candidates[0];
			if (abs(move.destination.file - candidate->square.file) <= 1 &&
				abs(move.destination.rank - candidate->square.rank) <= 1 &&
				abs(move.destination.file - candidate->square.file) + 
				abs(move.destination.rank - candidate->square.rank) != 0) {

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
				if (abs(move.destination.file - candidate->square.file) == 1 && 
					abs(move.destination.rank - candidate->square.rank) == 2 ||
					abs(move.destination.file - candidate->square.file) == 2 && 
					abs(move.destination.rank - candidate->square.rank) == 1) {

					narrowedCand.push_back(candidate);
				}
					
			}

			break;

		case TypeofPiece::R:	// Rook moves: 0 files or 0 ranks away
								//			   there is no piece in the way
								//				moves at least 1 space

			for (int i = 0; i < candidates.size(); i++) {
				Piece* candidate = candidates[i];
				if ((abs(move.destination.rank - candidate->square.rank) == 0 || // 0 file or rank away
					abs(move.destination.file - candidate->square.file) == 0) &&
					(abs(move.destination.rank - candidate->square.rank) > 1 || // move at least 1 space
					abs(move.destination.file - candidate->square.file) > 1)) {

					narrowedCand.push_back(candidate);
				}
			}

			break;
			
		default:
			std::cout << "\nERROR verifyMove: No piece selected!";
			return 0;
		}


		// ***ADD Check if pieces are in the way

		// "Assign move" and return 1 if successful
		if (narrowedCand.size() == 1) {
			move.piece.square = narrowedCand[0]->square;
			return 1;
		} else {
			std::cout << "\nERROR verifyMove: There are multiple pieces that can make this move. Please specify which in the move string.\n";
			return 0;
		}

	}

} // End Namespace

// Parse the string and return a move
Move moveStringParse(std::string moveString, PieceColor color) {

	Move move = Move();

	if (moveString.size() < 2) { // Check if string is long enough to bother parsing
		std::cout << "\nERROR moveStringParse: moveString is too short! All valid strings should be between 2 and 7 characters";
		return move;
	}

	// Assign the correct color to the piece in move
	if (color == PieceColor::Black) {
		move.piece.color = PieceColor::Black;
	} else if (color == PieceColor::White) {
		move.piece.color = PieceColor::White;
	} else {
		std::cout << "\nERROR moveStringParse: Invalid piece color!";
		return move;
	}

	// Look at the first char of the string and figure out what piece it is

	if (moveString[0] == '0' || moveString[0] == 'O') { // Castle

		// Maybe I should be more strict with castling strings
		// Right now it just checks the length to see whether it is short or long
		if (moveString.size() == 3) {
			move.castles = Castle::Short;
		} else if (moveString.size() == 5) {
			move.castles = Castle::Long;
		} else {
			std::cout << "\nERROR moveStringParse: castle string is incorrect length";
		}
		return move;

	} else if (moveString[0] >= 'a' && moveString[0] <= 'h') { // Pawn move

		move.piece.type = TypeofPiece::p;

	} else if (moveString[0] == 'N' || moveString[0] == 'R' || moveString[0] == 'B' ||
		moveString[0] == 'Q' || moveString[0] == 'K') { // Piece move

		move.piece.type = charToPieceType(moveString[0]);
		moveString = moveString.substr(1, moveString.size() - 1); // Get rid of first char (we are done with it)

	} else {
		std::cout << "\nERROR moveStringParse: Invalid 1st character";
		return move;
	}

	// Look at the next 2 char in the string

	// Figure out if there is a disambiguation
	if (moveString.size() < 2) { // Check if string is long enough to bother continue parsing
		std::cout << "\nERROR moveStringParse: moveString is too short! All valid strings should be between 2 and 7 characters";
		return move;
	}

	if (moveString[0] >= '1' && moveString[0] <= '8') { // is digit 1-8

		move.piece.square.rank = moveString[0];
		moveString = moveString.substr(1, moveString.size() - 1); // trim string

	} else if (moveString[0] >= 'a' && moveString[0] <= 'h' && (moveString[1] >= 'a' &&  // format aa
		moveString[1] <= 'h' || moveString[1] == 'x')) {

		move.piece.square.file = moveString[0];
		moveString = moveString.substr(1, moveString.size() - 1); // trim string

	} else if (moveString[0] >= 'a' && moveString[0] <= 'h' && moveString[1] >= '1' &&		// format a1*a or a1*1
		moveString[1] <= '8' && moveString.size() >= 4 && (moveString[3] >= 'a' &&
			moveString[3] <= 'h' || moveString[3] >= '1' && moveString[3] <= '8')) {

		move.piece.square.file = moveString[0];
		move.piece.square.rank = moveString[1];
		moveString = moveString.substr(2, moveString.size() - 1); // trim string
	}

	// Check if captures

	if (moveString.size() > 0 && moveString[0] == 'x') {
		move.captures = true;
		moveString = moveString.substr(1, moveString.size() - 1); // trim string
	}

	// Check destination

	if (moveString.size() < 2) { // Check if string is long enough to bother continue parsing
		std::cout << "\nERROR moveStringParse: moveString is too short! All valid strings should be between 2 and 7 characters";
		return move;
	}

	if (moveString[0] >= 'a' && moveString[0] <= 'h' && moveString[1] >= '1' && moveString[1] <= '8') {
		move.destination = { moveString[0], moveString[1] };
		moveString = moveString.substr(2, moveString.size() - 1); // trim string
	} else {
		std::cout << "\nERROR moveStringParse: Invalid String! Unable to find destination square";
	}

	// Check if promotion

	if (moveString.size() > 0) {

		if (moveString[0] == '=') {
			if (moveString.size() > 1) {
				move.promotion = charToPieceType(moveString[1]);
				moveString = moveString.substr(2, moveString.size() - 1); // trim string
			} else {
				std::cout << "\nERROR moveStringParse: Invalid String! No promotion piece specified";
			}
		}

	}

	// Check if check or mate

	if (moveString.size() > 0) {
		if (moveString[0] == '+') {
			move.check = true;
		} else if (moveString[0] == '#') {
			move.checkmate = true;
		} else {
			std::cout << "\nERROR moveStringParse: Invalid String! Extra characters detected";
		}
	}

	return move;
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
	} else {
		std::cout << "\nERROR Game::setPlayer: Invalid color string or player already assigned!\n";
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

bool Game::movePiece(std::string moveString, const Player* player) {
	PieceColor color = PieceColor::_;
	// Make sure it is the player's turn and figure out the color
	if (player->getColor() == "black") {
		if (whitesTurn) {
			std::cout << "\nERROR Game::movePiece: It is white's turn!\n";
			return false;
		}
		color = PieceColor::Black;
	} else if (player->getColor() == "white") {
		if (!whitesTurn) {
			std::cout << "\nERROR Game::movePiece: It is black's turn!\n";
			return false;
		}
		color = PieceColor::White;
	} else {
		return false;
	}

	// parse move string
	Move move = moveStringParse(moveString, color);

	if (verifyMove(move, board)) {
		std::cout << move;
		board.movePiece(move);
		whitesTurn = !whitesTurn; // change turns
		return true;
	}

	std::cout << "\nERROR Game::movePiece: Invalid Move!\n";
	return false;
	
}



