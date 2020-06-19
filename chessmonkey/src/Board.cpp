#include "Board.h"
#include <iostream>



Board::Board() {
	// Set up squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Square square = { i + 97, j + 49 };
										   
			boardState.insert({square, nullptr }); // insert square and empty piece into boardState map
		}
	}

	// TODO REFACTOR for pieces to have square structs

	// Set Up Pieces
	int j = 0;
	// Black pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		Square s = { i + 97, 7 + 48 };
		Piece *p = new Piece;
		*p = { TypeofPiece::p, PieceColor::Black, s };
		boardState[s] = p;
		pieces[j++] = p;
	}
	// King
	{
		Piece *p = new Piece;
		*p = { TypeofPiece::K, PieceColor::Black, Square {'e', '8'} };
		boardState[Square{ 'e', '8' }] = p;
		pieces[j++] = p;
	}
	//Queen
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::Q, PieceColor::Black, Square {'d', '8'} };
		boardState[Square{ 'd', '8' }] = p;
		pieces[j++] = p;
	}
	// Bishops
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, PieceColor::Black, Square {'c', '8'} };
		boardState[Square{ 'c', '8' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, PieceColor::Black, Square {'f', '8'} };
		boardState[Square{ 'f', '8' }] = p;
		pieces[j++] = p;
	}
	// Knights
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, PieceColor::Black, Square {'b', '8'} };
		boardState[Square{ 'b', '8' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, PieceColor::Black, Square {'g', '8'} };
		boardState[Square{ 'g', '8' }] = p;
		pieces[j++] = p;
	}
	// Rooks
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, PieceColor::Black, Square {'a', '8'} };
		boardState[Square{ 'a', '8' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, PieceColor::Black, Square {'h', '8'} };
		boardState[Square{ 'h', '8' }] = p;
		pieces[j++] = p;
	}

	// White Pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		Square s = { i + 97, 2 + 48 };
		Piece* p = new Piece;
		*p = { TypeofPiece::p, PieceColor::White, s };
		boardState[s] = p;
		pieces[j++] = p;
	}
	// King
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::K, PieceColor::White, Square { 'e', '1'} };
		boardState[Square{ 'e', '1' }] = p;
		pieces[j++] = p;
	}
	//Queen
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::Q, PieceColor::White, Square { 'd', '1'} };
		boardState[Square{ 'd', '1' }] = p;
		pieces[j++] = p;
	}
	// Bishops
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, PieceColor::White, Square { 'c', '1'} };
		boardState[Square{ 'c', '1' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::B, PieceColor::White, Square { 'f', '1'} };
		boardState[Square{ 'f', '1' }] = p;
		pieces[j++] = p;
	}
	// Knights
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, PieceColor::White, Square { 'b', '1'} };
		boardState[Square{ 'b', '1' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::N, PieceColor::White, Square { 'g', '1'} };
		boardState[Square{ 'g', '1' }] = p;
		pieces[j++] = p;
	}
	// Rooks
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, PieceColor::White, Square { 'a', '1'} };
		boardState[Square{ 'a', '1' }] = p;
		pieces[j++] = p;
	}
	{
		Piece* p = new Piece;
		*p = { TypeofPiece::R, PieceColor::White, Square { 'h', '1'} };
		boardState[Square{ 'h', '1' }] = p;
		pieces[j++] = p;
	}
	
	
}

Board::~Board() {
	//free memory
	
	for (int i = 0; i < 32; i++)
		delete pieces[i];
	std::cout << "All pieces deleted!";
}

std::map<Square, Piece*>& Board::getBoardState() {

	return boardState;
}

Piece** Board::getPieces() {
	return pieces;
}

void Board::movePiece(Move move) {

	for (int i = 0; i < 32; i++) {
		// Because Game object does the logic calculations, this just moves the piece 
		// based on starting location and destination
		Piece *currentPiece = pieces[i];
		if (currentPiece->square == move.piece.square) {
			currentPiece->square = move.destination;
			boardState[move.destination] = currentPiece;
			boardState[move.piece.square] = nullptr;
		} else if (currentPiece->square == move.destination) {
			currentPiece->square = Square();
		}

	}

}

// Output the board state
std::ostream& operator <<(std::ostream& out, Board& b) {

	out << "\n";
	
	for (int i = 8; i >= 1; i--) {

		out << " ---- ---- ---- ---- ---- ---- ---- ----\n";
		for (int j = 0; j < 8; j++) {

			Square square = { j + 97, i + 48 };
			
			// Figure out color of piece
			char color = ' '; // no piece is a space
			TypeofPiece piece = TypeofPiece::_;
			if (b.boardState[square] != nullptr) {
				piece = b.boardState[square]->type;
				if (b.boardState[square]->color == PieceColor::Black)
					color = 'b';
				else
					color = 'w';
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

