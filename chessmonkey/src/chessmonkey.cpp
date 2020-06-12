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
	
	Board b = Board();

	auto bs = b.getBoardState();

	for (auto i = bs.begin(); i != bs.end(); i++) {
		cout << (int)i->second<< " " << i->first.first << i->first.second  << endl;
	}

}

