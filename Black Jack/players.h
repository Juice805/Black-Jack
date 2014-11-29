//
//  players.h
//  Black Jack
//
//  Created by Justin Oroz on 11/26/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#ifndef __Black_Jack__players__
#define __Black_Jack__players__

#include <stdio.h>
#include <iostream>
#include "deck.h"
using namespace std;

class GenericPlayer {
public:
    string playerName() const {
        return name;
    }
protected:
    string name;
};



// HAND CLASS
class Hand: public GenericPlayer{
public:
    Hand(){
    }
    
    void deal(Deck* deck);
    void showHand();
    bool bust();
    void stay();
    bool isStaying() {return staying;};
    void hit(Deck* deck);
    void surrender();
    bool isSurrendered(){return surrendered;}
    void doubleHand(Deck* deck);
    bool isDoubled(){ return doubled; }
    bool canSplit();
    void split();
    bool isSplit(){return handSplit;}
    int addCards(){ return handValue; }
    void newHand();
    int alternateValue(){return otherVal;} //returns other possible value if an ace
    void setBetAmount(int amount){
        bet = amount;
    }
    int getBet() const {return bet;}
protected:
    vector<Card> hand, splitHand;
    int handValue = 0;
    int otherVal; // true if ace is in hand
    int bet;
    
private:
    void drawCard(Deck* game);
    bool doubled = false;
    bool staying = false;
    bool surrendered = false;
    bool handSplit = false;

};


// DEALER CLASS
class Dealer: public Hand {
public:
    Dealer(){name="Dealer";}
    void showFlop();
};


// USER CLASS
class User: public Hand {
public:
    User(){    }
    User(string userName){
        name = userName;
    }
    void setName(string username){
        name = username;
    }
    void placeBet(){
        if (bet > money) {
            bet = money;
            money = 0;
        } else
            money -= bet;
    }
    
    void win(int amount){
        money += amount;
    }
    
    int cash() const{ return money;}
    
private:

    int money = 500;
};



#endif /* defined(__Black_Jack__players__) */
