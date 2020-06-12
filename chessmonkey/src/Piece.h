#pragma once

// All the types of pieces in chess
enum class TypeofPiece {
	_, p, K, Q, B, N, R
};

struct Piece {
	TypeofPiece type;
	bool isBlack;
};