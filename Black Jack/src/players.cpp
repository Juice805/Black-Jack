//
//  players.cpp
//  Black Jack
//
//  Created by Justin Oroz on 11/26/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#include "players.h"





// ---------- Hand Class ----------- //
void Hand::newHand(){
    cards.clear();
    doubled = false;
    staying = false;
    surrendered = false;
}

void Hand::deal(Deck* deck){
    for (int i = 0; i < 2; i++) {
        drawCard(deck);
    }
}

void Hand::drawCard(Deck* game){
    int cardNum;
    bool placedInHand = false;
    while (!placedInHand) {
        cardNum =  int(rand()%(52*game->numOfDecks())); //generate new card number
        if (!game->alreadyDrawn(cardNum)) {     //if card is not already drawn
            cards.push_back(game->grabCard(cardNum));        //add to hand
            placedInHand = true;
        } else placedInHand = false;        //else try again
    }
}

void Hand::showHand(){
    for (int i = 0; i < cards.size(); i++) {
        cout << "╔══════╗ ";
    } cout << "\n";
    
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].viewSymbol() == '0') {
            cout << "║ " << cards[i].viewSuit() << "10" << "  ║ ";
        } else
            cout << "║ " << cards[i].viewSuit() << cards[i].viewSymbol() << "   ║ ";
    } cout << "\n";
    
    for (int i = 0; i < cards.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    for (int i = 0; i < cards.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].viewSymbol() == '0') {
            cout << "║  " << cards[i].viewSuit() << "10" << " ║ ";
        } else
            cout << "║   " << cards[i].viewSuit() << cards[i].viewSymbol() << " ║ ";
    } cout << "\n";
    
    for (int i = 0; i < cards.size(); i++) {
        cout << "╚══════╝ ";
    } cout << "\n";
}


bool Hand::bust(){
    handValue = 0;
    int  aces = 0;
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].isAce()) {
            aces++;
        } else handValue += cards[i].getValue();
    }
    otherVal = handValue; //in case no aces
    
    int acevalue = 0;
    //wait till other cards are counted to deal with aces
    for (int i = 0; i < aces; i++) {
        if ((handValue + acevalue + 11) > 21) {
            acevalue += 1; //adds one if 11 goes over 21
            if (aces > 1 && handValue < 10) { //if handvalue is greater than 10, multiple aces can only be 1 each, if 10 then its 21
                otherVal = handValue + acevalue - 10;
            } else
                otherVal = handValue + acevalue;
        } else {
            if (i != aces - 1) {
                acevalue += 1;     //if there is more than one ace, the first ones only add one
            } else {
                acevalue += 11;
                if (handValue + acevalue == 21) {
                    otherVal = 21;
                } else {
                    otherVal = handValue + acevalue - 10;
                }
            }
        }
    }
    
    handValue+=acevalue;
    
    if (handValue > 21) {
        return true;
    } else return false;
}

bool Hand::canSplit(){
    if ( cards.size() == 2 && cards[0].viewSymbol() == cards[1].viewSymbol()) {
        return true;
    } else return false;
}

void Hand::hit(Deck* deck){
    drawCard(deck);
    staying = false;
}

void Hand::stay(){
    staying = true;
}

void Hand::doubleHand(Deck* deck){
    hit(deck);
    stay();
    doubled =true;
}

void Hand::surrender(){
    surrendered = true;
}

void User::split(){
    didSplit = true;
    splitHand.bet = hand.bet;
    splitHand.cards.push_back(hand.cards[1]); //moves second card to splitHand
    hand.cards.pop_back(); //remove card from original hand
}


// ---------- Dealer Class ----------- //

void Dealer::showFlop(){
    cout << "╔══════╗ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        cout << "╔══════╗ ";
    } cout << "\n";
    
    cout << "║ ?    ║ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        if (hand.cards[i].viewSymbol() == '0') {
            cout << "║ " << hand.cards[i].viewSuit() << "10" << "  ║ ";
        } else
            cout << "║ " << hand.cards[i].viewSuit() << hand.cards[i].viewSymbol() << "   ║ ";
    } cout << "\n";
    
    cout << "║      ║ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    cout << "║      ║ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    cout << "║    ? ║ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        if (hand.cards[i].viewSymbol() == '0') {
            cout << "║  " << hand.cards[i].viewSuit() << "10" << " ║ ";
        } else
            cout << "║   " << hand.cards[i].viewSuit() << hand.cards[i].viewSymbol() << " ║ ";
    } cout << "\n";
    
    cout << "╚══════╝ ";
    for (int i = 1; i < hand.cards.size(); i++) {
        cout << "╚══════╝ ";
    } cout << "\n";
}






// ---------- Hand Class ----------- //

