#include "Board.h"
#include <iostream>

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
										   
			boardState.insert({square, nullptr }); // insert square and empty piece into boardState map
		}
	}

	// Set Up Pieces
	int j = 0;
	// Black pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		std::string s = "";
		s.push_back(i + 97);
		s.push_back(7 + 48);
		Piece *p = new Piece;
		*p = { TypeofPiece::p, true, s };
		boardState[s] = p;
		pieces[j++] = p;
	}
	// King
	{
		Piece *p = new Piece;
		*p = { TypeofPiece::K, true, "e8" };
		boardState["e8"] = p;
		pieces[j++] = p;
	}
	//Queen
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::Q, true, "d8" };
		boardState["d8"] = p;
		pieces[j++] = p;
	}
	// Bishops
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, true, "c8" };
		boardState["c8"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, true, "f8" };
		boardState["f8"] = p;
		pieces[j++] = p;
	}
	// Knights
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, true, "b8" };
		boardState["b8"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, true, "g8" };
		boardState["g8"] = p;
		pieces[j++] = p;
	}
	// Rooks
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, true, "a8" };
		boardState["a8"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, true, "h8" };
		boardState["h8"] = p;
		pieces[j++] = p;
	}

	// White Pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		std::string s = "";
		s.push_back(i + 97);
		s.push_back(2 + 48);
		Piece* p = new Piece;
		*p = { TypeofPiece::p, false, s };
		boardState[s] = p;
	}
	// King
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::K, false, "e1" };
		boardState["e1"] = p;
		pieces[j++] = p;
	}
	//Queen
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::Q, false, "d1" };
		boardState["d1"] = p;
		pieces[j++] = p;
	}
	// Bishops
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, false, "c1" };
		boardState["c1"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, false, "f1" };
		boardState["f1"] = p;
		pieces[j++] = p;
	}
	// Knights
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, false, "b1" };
		boardState["b1"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, false, "g1" };
		boardState["g1"] = p;
		pieces[j++] = p;
	}
	// Rooks
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, false, "a1" };
		boardState["a1"] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, false, "h1" };
		boardState["h1"] = p;
		pieces[j++] = p;
	}
	
	
}

std::map<std::string, Piece*>& Board::getBoardState() {

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

			// Figure out color of piece
			char color = ' '; // no piece is a space
			char piece = ' ';
			if (b.boardState[square] != nullptr) {
				piece = pieceToChar(b.boardState[square]->type);
				b.boardState[square]->isBlack ? color = 'b' : color = 'w'; // black is b white is w
			}

			out << "|";
			// Use x  x to mark dark squares
			if ((i + j) % 2 == 0)
				out << " " << color << piece << " ";
			else
				out << "x" << color << piece << "x";
		}
		out << "|\n";
		
	}
	out << " ---- ---- ---- ---- ---- ---- ---- ----\n";

	return out;
}

