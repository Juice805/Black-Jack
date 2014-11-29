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
    hand.clear();
    splitHand.clear();
    doubled = false;
    staying = false;
    surrendered = false;
    handSplit = false;
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
            hand.push_back(game->grabCard(cardNum));        //add to hand
            placedInHand = true;
        } else placedInHand = false;        //else try again
    }
}

void Hand::showHand(){
    for (int i = 0; i < hand.size(); i++) {
        cout << "╔══════╗ ";
    } cout << "\n";
    
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].viewSymbol() == '0') {
            cout << "║ " << hand[i].viewSuit() << "10" << "  ║ ";
        } else
            cout << "║ " << hand[i].viewSuit() << hand[i].viewSymbol() << "   ║ ";
    } cout << "\n";
    
    for (int i = 0; i < hand.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    for (int i = 0; i < hand.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].viewSymbol() == '0') {
            cout << "║  " << hand[i].viewSuit() << "10" << " ║ ";
        } else
            cout << "║   " << hand[i].viewSuit() << hand[i].viewSymbol() << " ║ ";
    } cout << "\n";
    
    for (int i = 0; i < hand.size(); i++) {
        cout << "╚══════╝ ";
    } cout << "\n";
}


bool Hand::bust(){
    handValue = 0;
    int  aces = 0;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].isAce()) {
            aces++;
        } else handValue += hand[i].getValue();
    }
    otherVal = handValue; //in case no aces
    
    //wait till other cards are counted to deal with aces
    for (int i = 0; i < aces; i++) {
        if ((handValue + 11) > 21) {
            handValue += 1; //adds one if 11 goes over 21
            if (aces > 1) {
                otherVal = handValue -10;
            } else
                otherVal = handValue;
        } else {
            if (i != aces - 1) {
                handValue += 1;     //if there are more than one aces, the first ones only add one
            }
            handValue += 11;
            otherVal = handValue - 10;
        }
    }
    
    if (handValue > 21) {
        return true;
    } else return false;
}

bool Hand::canSplit(){
    if ( hand.size() == 2 && hand[0].viewSymbol() == hand[1].viewSymbol()) {
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

void Hand::split(){
    handSplit = true;
    splitHand.push_back(hand[1]); //moves second card to splitHand
    hand.pop_back(); //remove card from original hand
    
}


// ---------- Dealer Class ----------- //

void Dealer::showFlop(){
    cout << "╔══════╗ ";
    for (int i = 1; i < hand.size(); i++) {
        cout << "╔══════╗ ";
    } cout << "\n";
    
    cout << "║ ?    ║ ";
    for (int i = 1; i < hand.size(); i++) {
        if (hand[i].viewSymbol() == '0') {
            cout << "║ " << hand[i].viewSuit() << "10" << "  ║ ";
        } else
            cout << "║ " << hand[i].viewSuit() << hand[i].viewSymbol() << "   ║ ";
    } cout << "\n";
    
    cout << "║      ║ ";
    for (int i = 1; i < hand.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    cout << "║      ║ ";
    for (int i = 1; i < hand.size(); i++) {
        cout << "║      ║ ";
    } cout << "\n";
    
    cout << "║    ? ║ ";
    for (int i = 1; i < hand.size(); i++) {
        if (hand[i].viewSymbol() == '0') {
            cout << "║  " << hand[i].viewSuit() << "10" << " ║ ";
        } else
            cout << "║   " << hand[i].viewSuit() << hand[i].viewSymbol() << " ║ ";
    } cout << "\n";
    
    cout << "╚══════╝ ";
    for (int i = 1; i < hand.size(); i++) {
        cout << "╚══════╝ ";
    } cout << "\n";
}






// ---------- Hand Class ----------- //

