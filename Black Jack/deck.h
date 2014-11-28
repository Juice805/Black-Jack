//
//  deck.h
//  Black Jack
//
//  Created by Justin Oroz on 11/26/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#ifndef __Black_Jack__deck__
#define __Black_Jack__deck__

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;


class Card{
public:
    Card(){}
    Card(char card, char cardSuit); //Constructor: gives card attributes based on input
    void showCard(); //debugging
    
    // attribute Getters
    char viewSymbol(){return symbol;}
    string viewSuit(){return suit;}
    int getValue(){return value;}
    bool isAce(){return ace;}
    
private:
    int value;
    bool ace = false;
    char symbol;
    string suit;
};


//DECK CLASS
class Deck{
public:
    Deck();
    Deck(int numOfDecks);
    
    Card grabCard(int card){
        cardDrawn[card] = true;
        return deck[card];
    }
    
    bool alreadyDrawn(int card) {
        return cardDrawn[card];
    }
    
    void editDecks(int number){
        if (number > 0) {
            decks = number;
        } else decks = 1;
        addCards();
    }
    
    int numOfDecks(){ return decks; }
    
    void shuffle(){
        for (int i = 0; i < cardDrawn.size(); i++) {
            cardDrawn[i] = false;
        }
    }
    
    
    
protected:
    const int cardsInADeck = 52;
    int decks = 1;

    vector<Card> deck;
    //Card deck[cardsInADeck];

    vector<bool> cardDrawn;
    //bool cardDrawn[cardsInADeck*decks];
private:
    void addCards();
    
};


#endif /* defined(__Black_Jack__deck__) */
