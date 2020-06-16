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

	
	Game game = Game();

	Player p1 = Player();
	Player p2 = Player();

	//cout << rand();

	game.setPlayer(p1);
	game.setPlayer(p2);

	cout << "Black: "<< game.getBlackPlayer().getColor() << "\nWhite: "<< game.getWhitePlayer().getColor();


	cout << game.getBoard();

}

