#pragma once

#include <string>
#include <fstream>

// All the types of pieces in chess
enum class TypeofPiece {
	_, p, K, Q, B, N, R
};

struct Piece {
	TypeofPiece type;
	bool isBlack = 0;
	std::string square;
};

// Move struct (might change to a class)
struct Move {
	std::string destination;
	Piece piece;
	bool captures;
};

// Insertion operator overloads for debugging purposes
std::ostream& operator <<(std::ostream& out, TypeofPiece p);
std::ostream& operator <<(std::ostream& out, const Piece& p);
std::ostream& operator <<(std::ostream& out, const Move& m);
