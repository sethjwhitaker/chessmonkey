// This is the startup project, but this might eventually evolve into a
//		simple console based chess engine

// Currently this is only being used to test class implementations

#include <iostream>
#include <string>

#include "Game.h"
#include "Player.h"
#include "Board.h"


int main() {

	using namespace std;

	cout << "Welcome to Chess Monkey!\n\n";

	srand(time(0)); // initialize random seed

	Game game = Game();

	Player p1 = Player();
	Player p2 = Player();

	game.setPlayer(p1);
	game.setPlayer(p2);

	cout << "Black: "<< game.getBlackPlayer().getColor() << "\nWhite: "<< game.getWhitePlayer().getColor();

	cout << game.getBoard();

	cout << endl << p1.movePiece("Na3");

	cout << endl << p2.movePiece("Na3");

	cout << game.getBoard();

}

