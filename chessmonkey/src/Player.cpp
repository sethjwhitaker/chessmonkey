#include "Player.h"

bool Player::movePiece(std::string moveString) {
	if (game->movePiece(moveString, this))
		return true;
	else
		return false;
}

void Player::setGame(Game* newGame) {
	game = newGame;
}