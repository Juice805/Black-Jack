//
//  main.cpp
//  Black Jack
//
//  Created by Justin Oroz on 11/20/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#ifndef __Black_Jack__game__
#define __Black_Jack__game__

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
    
    bool receiveCommand(User* player, string command);
    void printResults();
    
    void settings();
private:
    Deck myDeck;
    Dealer house;
    bool playing = true;
};

#endif /* defined(__Black_Jack__game__) */
