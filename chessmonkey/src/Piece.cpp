#include "Piece.h"

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

std::ostream& operator <<(std::ostream& out, TypeofPiece p) {
	out << pieceToChar(p);
	return out;
}

std::ostream& operator <<(std::ostream& out, const Square s) {
	out << s.file << s.rank;
	return out;
}

std::ostream& operator <<(std::ostream& out, const Piece& p) {
	
	if (&p != nullptr) {
		if (p.color == PieceColor::Black)
			out << "black ";
		else
			out << "white ";
		out << p.type << " on " << p.square;
	}

	return out;
}

std::ostream& operator <<(std::ostream& out, const Move& m) {

	out << m.piece;
	if (m.captures) {
		out << " captures on ";
	} else {
		out << " moves to ";
	}
	out << m.destination;

	return out;

}

bool operator <(const Square s1, const Square s2) {
	if (s1.file < s2.file) { // compare file first
		return true;
	} else if (s1.file > s2.file) {
		return false;
	} else {						// if file is equal
		if (s1.rank < s2.rank) {	// compare rank
			return true;
		} else {
			return false;
		}
	}
}

bool operator ==(const Square s1, const Square s2) {
	return s1.file == s2.file && s1.rank == s2.rank;
}