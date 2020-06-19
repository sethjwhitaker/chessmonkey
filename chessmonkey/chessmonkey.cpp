// This is the startup project, but this might eventually evolve into a
//		simple console based chess engine

// Currently this is only being used to test class implementations

#include <iostream>
#include <string>

#include "src/Game.h"
#include "src/Player.h"
#include "src/Board.h"

void displayMenu();
void startGame();

int main() {
	srand(time(0)); // initialize random seed

	std::cout << "Welcome to Chess Monkey!\n\n";

	displayMenu();
}

// Display menu for user and call corresponding function based on choice
void displayMenu() {
	using std::cout;
	
	int choice;

	cout << "\n   ----------------";
	cout << "\n         Menu      ";
	cout << "\n   ----------------";
	cout << "\n   1. Start Game   ";
	cout << "\n   0. Quit         ";
	cout << "\n   ----------------";
	cout << "\n";

	std::cin >> choice;
	
	switch (choice) {
	case 0:
		break;
	case 1:
		startGame();
		break;
	}
	
}

void startGame() {

	Game game = Game();

	Player p1 = Player();
	Player p2 = Player();

	game.setPlayer(p1, "white");
	game.setPlayer(p2, "black");

	std::cout << game.getBoard();

	std::string move = "";
	while (move != "quit") {

		while (true) {
			std::cout << "\nWhite's Turn. Enter a move: ";
			std::cin >> move;

			if (!p1.movePiece(move)) {
				std::cout << "Invalid move.";
			} else {
				std::cout << game.getBoard();
				break;
			}

		}

		while (true) {
			std::cout << "\nBlack's Turn. Enter a move: ";
			std::cin >> move;

			if (!p2.movePiece(move)) {
				std::cout << "Invalid move.";
			} else {
				std::cout << game.getBoard();
				break;
			}

		}
	}
}