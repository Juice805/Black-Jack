//
//  main.cpp
//  Black Jack
//
//  Created by Justin Oroz on 11/20/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#include "main.h"


int main(int argc, const char * argv[]) {
    int playerCount;
    std::cout << "Welcome to Black Jack!\n\n";
    do {
    cout << "How many players? (8 Max)\n";
    cin >> playerCount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cout << "Invalid Input!\n\n";
        }
    } while (playerCount > 8 || playerCount < 1);
    
    Game blackJack(playerCount);
    
    return 0;
}
