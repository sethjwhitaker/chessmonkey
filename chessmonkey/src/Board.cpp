#include "Board.h"

Board::Board() {
	// Set up squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Square square (i + 97, j + 1); // i+97 is converted to char, starting at 'a'
										   
			boardState.insert({square, Piece::_ }); // insert square and null piece into boardState map
		}
	}
}

std::map<Square, Piece>& Board::getBoardState() {

	return boardState;
}

