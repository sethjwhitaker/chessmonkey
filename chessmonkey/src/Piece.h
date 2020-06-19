#pragma once

#include <string>
#include <fstream>

// All the types of pieces in chess
enum class TypeofPiece {
	_, p, K, Q, B, N, R
};

// types of Castles
enum class Castle {
	_, Short, Long
};

// Colors of pieces
enum class PieceColor {
	_, Black, White
};

struct Square {
	char file = 0; // a through h
	char rank = 0; // 1 through 8
};

struct Piece {
	TypeofPiece type;
	PieceColor color = PieceColor::_;
	Square square;
};

// Move struct (might change to a class)
struct Move {
	Square destination;
	Piece piece;
	bool captures = 0;
	bool check = 0;
	bool checkmate = 0;
	TypeofPiece promotion = TypeofPiece::_;
	Castle castles = Castle::_;
};

// Insertion operator overloads for debugging purposes
std::ostream& operator <<(std::ostream& out, const TypeofPiece p);
std::ostream& operator <<(std::ostream& out, const Square s);
std::ostream& operator <<(std::ostream& out, const Piece& p);
std::ostream& operator <<(std::ostream& out, const Move& m);

// Square operators for storing in std::map
bool operator <(const Square s1, const Square s2);
bool operator ==(const Square s1, const Square s2);

