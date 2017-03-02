//
//  deck.cpp
//  Black Jack
//
//  Created by Justin Oroz on 11/26/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#include "deck.h"


Card::Card(char card, char cardSuit){ //Constructor: gives card attributes based on input
    switch (card) {
        case 'A':
            ace = true;
            value = 11;
            symbol = 'A';
            break;
        case '2':
            value = 2;
            symbol = '2';
            break;
        case '3':
            value = 3;
            symbol = '3';
            break;
        case '4':
            value = 4;
            symbol = '4';
            break;
        case '5':
            value = 5;
            symbol = '5';
            break;
        case '6':
            value = 6;
            symbol = '6';
            break;
        case '7':
            value = 7;
            symbol = '7';
            break;
        case '8':
            value = 8;
            symbol = '8';
            break;
        case '9':
            value = 9;
            symbol = '9';
            break;
        case '0':
            value = 10;
            symbol = '0'; //must add a 1 at deal
            break;
        case 'J':
            value = 10;
            symbol = 'J';
            break;
        case 'Q':
            value = 10;
            symbol = 'Q';
            break;
        case 'K':
            value = 10;
            symbol = 'K';
            break;
            
        default:
            cout << "Card not Found\n" << card << endl;
            break;
    }
    
    switch (cardSuit) {
        case 's':
            suit = "♠";     //Spade
            break;
        case 'c':
            suit = "♣";     //Club
            break;
        case 'h':
            suit = "♥";     //Heart
            break;
        case 'd':
            suit = "♦";     //Diamond
            break;
            
        default:
            cout << "Suit not found\n";
            break;
    }
    
}

void Card::showCard(){
    cout << "╔══════╗\n";
    cout << "║ " << suit << symbol << "   ║\n";
    cout << "║      ║\n";
    cout << "║      ║\n";
    cout << "║   " << suit << symbol << " ║\n";
    cout << "╚══════╝\n";
}


// DECK CLASS

Deck::Deck(){
    editDecks(decks);
}

Deck::Deck(int numOfDecks){
    editDecks(numOfDecks);
}

void Deck::addCards(){
    deck.clear();
    cardDrawn.clear();
    srand(time(0));
    char symbol = ' ', suit = ' ';
    for (int i = 0; i<(cardsInADeck*decks); i++) { //fills deck
        switch (i%13 + 1) {
            case 1:
                symbol = 'A';
                break;
            case 2:
                symbol = '2';
                break;
            case 3:
                symbol = '3';
                break;
            case 4:
                symbol = '4';
                break;
            case 5:
                symbol = '5';
                break;
            case 6:
                symbol = '6';
                break;
            case 7:
                symbol = '7';
                break;
            case 8:
                symbol = '8';
                break;
            case 9:
                symbol = '9';
                break;
            case 10:
                symbol = '0'; //must add a 1 at deal
                break;
            case 11:
                symbol = 'J';
                break;
            case 12:
                symbol = 'Q';
                break;
            case 13:
                symbol = 'K';
                break;
                
            default:
                cout << "Card not found\n";
                break;
        }
        
        switch (i%4) {
            case 0:
                suit = 's';     //Spade
                break;
            case 1:
                suit = 'c';     //Club
                break;
            case 2:
                suit = 'h';     //Heart
                break;
            case 3:
                suit = 'd';     //Diamond
                break;
                
            default:
                cout << "Suit not found\n";
                break;
        }
        
        deck.push_back(Card(symbol, suit));
        cardDrawn.push_back(false);
    }
}
