//
//  game.hpp
//  Black Jack
//
//  Created by Justin Oroz on 3/2/17.
//  Copyright © 2017 Justin Oroz. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "players.h"
#include "deck.h"
#include "juice.h"
using namespace std;

class Game {
public:
	Game(){}
	Game(int playerCount){
		play(playerCount);
	}

	bool play(int playerCount);
	vector<User> player;
	void welcome();
	void printResults();
	bool reservedName(string name);
	void settings();
	void playerTurn(User* player, bool flop = false, bool firstHand = false);
	void showHelp();
private:
	Deck myDeck;
	Dealer house;
	bool receiveCommand(User* player, Hand* hand, string command);
	bool playing = true;
	bool needHelp = false;
	void printResultList(const vector<User*> userList, string singleResult, string multipleResult);
	string error = "";
};


#endif /* game_hpp */
