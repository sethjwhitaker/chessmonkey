#include "Board.h"

namespace {
	char pieceToChar(TypeofPiece p) {
		switch (p) {
		case TypeofPiece::_:
			return ' ';
		case TypeofPiece::p:
			return 'P';
		case TypeofPiece::K:
			return 'K';
		case TypeofPiece::Q:
			return 'Q';
		case TypeofPiece::B:
			return 'B';
		case TypeofPiece::N:
			return 'N';
		case TypeofPiece::R:
			return 'R';
		default:
			return ' ';
		}
	}
}

Board::Board() {
	// Set up squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::string square = "";
			square.push_back(i + 97);
			square.push_back(j + 49);
										   
			boardState.insert({square, Piece() }); // insert square and null piece into boardState map
		}
	}

	// Set Up Pieces

	// Pawns
	// Black Pawns
	for (int i = 0; i < 8; i++) {
		std::string s = "";
		s.push_back(i + 97);
		s.push_back(7 + 48);
		boardState[s].type = TypeofPiece::p;
		boardState[s].isBlack = true;
	}
	// White Pawns
	for (int i = 0; i < 8; i++) {
		std::string s = "";
		s.push_back(i + 97);
		s.push_back(2 + 48);
		boardState[s].type = TypeofPiece::p;
		boardState[s].isBlack = false;
	}
	// Kings
	boardState["e8"].type = TypeofPiece::K;
	boardState["e8"].isBlack = true;
	boardState["e1"].type = TypeofPiece::K;
	boardState["e1"].isBlack = false;
	// Queens
	boardState["d8"].type = TypeofPiece::Q;
	boardState["d8"].isBlack = true;
	boardState["d1"].type = TypeofPiece::Q;
	boardState["d1"].isBlack = false;
	// Bishops
	boardState["f8"].type = TypeofPiece::B;
	boardState["f8"].isBlack = true;
	boardState["c8"].type = TypeofPiece::B;
	boardState["c8"].isBlack = true;
	boardState["f1"].type = TypeofPiece::B;
	boardState["f1"].isBlack = false;
	boardState["c1"].type = TypeofPiece::B;
	boardState["c1"].isBlack = false;
	// Knights
	boardState["g8"].type = TypeofPiece::N;
	boardState["g8"].isBlack = true;
	boardState["b8"].type = TypeofPiece::N;
	boardState["b8"].isBlack = true;
	boardState["g1"].type = TypeofPiece::N;
	boardState["g1"].isBlack = false;
	boardState["b1"].type = TypeofPiece::N;
	boardState["b1"].isBlack = false;
	// Rooks
	boardState["h8"].type = TypeofPiece::R;
	boardState["h8"].isBlack = true;
	boardState["a8"].type = TypeofPiece::R;
	boardState["a8"].isBlack = true;
	boardState["h1"].type = TypeofPiece::R;
	boardState["h1"].isBlack = false;
	boardState["a1"].type = TypeofPiece::R;
	boardState["a1"].isBlack = false;
}

std::map<std::string, Piece>& Board::getBoardState() {

	return boardState;
}


// Output the board state
std::ostream& operator <<(std::ostream& out, Board& b) {

	out << "\n";
	
	for (int i = 8; i >= 1; i--) {

		out << " ---- ---- ---- ---- ---- ---- ---- ----\n";
		for (int j = 0; j < 8; j++) {

			char c = j + 97; // ascii 97 is a

			std::string square = ""; 
			square.push_back(c);			// add column
			square.push_back(i+48);			// add row (ascii 48 is 0)
			Piece p = b.boardState[square]; // get piece from board state

			// Figure out color of piece
			char color = ' '; // no piece is a space
			if (p.type != TypeofPiece::_) {
				p.isBlack ? color = 'b' : color = 'w'; // black is b white is w
			}

			out << "|";
			// Use x  x to mark dark squares
			if ((i + j) % 2 == 0)
				out << " " << color << pieceToChar(p.type) << " ";
			else
				out << "x" << color << pieceToChar(p.type) << "x";
		}
		out << "|\n";
		
	}
	out << " ---- ---- ---- ---- ---- ---- ---- ----\n";

	return out;
}

