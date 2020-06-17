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

std::ostream& operator <<(std::ostream& out, const Piece& p) {
	if (&p != nullptr) {
		out << "\nPiece: ";
		if (p.isBlack)
			out << "black ";
		else
			out << "white ";
		out << p.type << " on " << p.square;
	}

	return out;
}

std::ostream& operator <<(std::ostream& out, const Move& m) {

	out << "\nMove:";
	out << m.piece;
	out << "\ncaptures: " << m.captures;
	out << "\ndestination: " << m.destination;

	return out;

}