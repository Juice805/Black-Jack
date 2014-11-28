//
//  main.cpp
//  Black Jack
//
//  Created by Justin Oroz on 11/20/14.
//  Copyright (c) 2014 Justin Oroz. All rights reserved.
//

#include "main.h"

void Game::welcome(){
    string letsPlay = "";
    for (int i = 0; i < player.size(); i++) {
        if (i != player.size()-1 ) {
            letsPlay.append(player[i].playerName());
            letsPlay.append(", ");
        } else if (player.size() != 1){
            letsPlay.append("and ");
            letsPlay.append(player[i].playerName());
            letsPlay.append(":");
        } else {
            letsPlay.append(player[i].playerName());
            letsPlay.append(":");
        }
    }
    letsPlay.append(" Let's play Black Jack!\n\n");
    
    cout << letsPlay;
}

bool Game::receiveCommand(User* player, string command){
    command = stringtolower(command);
    if (command == "hit" || command == "h") {
        player->hit(&myDeck);
        return true;
    }
    if (command == "stay" || command == "s") {
        player->stay();
        return true;
    }
    if (command == "split" || command == "sp") {
        //if on first turn the two cards match, 2 seperate hands
        return false; //UNIMPLEMENTED
    }
    if (command == "double" || command == "d") {
        //double wager, take a single card and finish
        return false; //UNIMPLEMENTED
    }
    if (command == "surrender" || command == "sur") {
        //give up a half-bet and retire from the game
        return false; //UNIMPLEMENTED
    }


    
    return false;
}

void Game::printResults(){
    int winners = 0, busted = 0, losers = 0, tied = 0, accountedFor = 0;
    if (house.bust()) {
        cout << house.playerName() << " Busted! ";
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust()) {
                winners++;
                player[i].win(player[i].getBet()*2);
            } else losers++;
        }
        
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust()) {
                if (winners == 1 ) { //if only one winner
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" wins!\n";
                    
                } else if (accountedFor == winners-1){ // if the last winner
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " win!\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }
        accountedFor = 0;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (player[i].bust()) {
                if (busted == 1 ) { //if only one winner
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" busted!\n";
                    
                } else if (accountedFor == busted-1){ // if the last winner
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " busted!\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }
        
        if (winners == 0) {
            cout << "\nAll players bust, Dealer wins!\n";
        }
    } else {
        cout << house.playerName() << " stayed at " << house.addCards() << endl;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust() && player[i].addCards() > house.addCards()) {
                winners++;
                player[i].win(player[i].getBet()*2);
            } else if (!player[i].bust() && player[i].addCards() == house.addCards()){
                tied++;
                player[i].win(player[i].getBet());
            } else if (!player[i].bust() && player[i].addCards() < house.addCards()){
                losers++;
            } else busted++;
        }
        
        accountedFor = 0;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust() && player[i].addCards() > house.addCards()) { //if a winner
                if (winners == 1 ) { //if only one winner
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" wins!\n";
                    
                } else if (accountedFor == winners-1){ // if the last winner
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " win!\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }

        accountedFor = 0;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust() && player[i].addCards() == house.addCards()) {
                if (tied == 1 ) { //if only one tied
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" ties\n";
                    
                } else if (accountedFor == tied-1){ // if the last tied
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " tied\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }
        
        accountedFor = 0;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (!player[i].bust() && player[i].addCards() < house.addCards()) {
                if (losers == 1 ) { //if only one winner
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" lost!\n";
                    
                } else if (accountedFor == losers-1){ // if the last winner
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " lost!\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }
        
        accountedFor = 0;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (player[i].bust()) {
                if (busted == 1 ) { //if only one winner
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout <<" busted!\n";
                    
                } else if (accountedFor == busted-1){ // if the last winner
                    cout << "and ";
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << " busted!\n";
                } else {
                    cout << player[i].playerName() << "($" << player[i].cash() << ")";
                    cout << ", ";
                }
                accountedFor++;
            }
        }
        
        if (winners == 0 && tied == 0) {
            cout << endl << house.playerName() << " wins!\n";
        }

    }
    
    int broke = 0;
    vector<User>::iterator iter;
    for (int i = 0; i < player.size(); i++) {
        if (player[i].cash() == 0) {
            broke++; //counts people without money
        }
    }
    
    accountedFor = 0;
    for (int i = 0; i < player.size(); i++) { //removes broke people
        if (player[i].cash() == 0) {
            if (broke == 1 ) { //if only one broke
                cout << player[i].playerName();
                cout <<" ran out of money! Leaving table...\n";
            } else if (accountedFor == broke-1){ // if the last broke
                cout << "and ";
                cout << player[i].playerName();
                cout << " ran out of money! Leaving table...\n";
            } else {
                cout << player[i].playerName();
                cout << ", ";
            }
            iter = player.begin();
            iter += i;
            player.erase(iter);
            accountedFor++;
        }
    }

}

void Game::settings(){
    string username, parameter; int number; bool unique; int user = 0; vector<User>::iterator iter;
    bool continueGame = false, usernameMatch = false;
    playing = true;
    
    if (player.size() == 0) {
        cout << "\nAll players are broke! Enter a new player name:\n";
        cin >> parameter;
        unique = false;
        while (!unique) {
            unique = true;
            for (int i = 0; i < player.size(); i++){
                if (stringtolower(parameter) == stringtolower(player[i].playerName())) {
                    unique = false;
                    cout << "\nName must be unique! Enter new name\n";
                    cin >> parameter;
                }
            }
            
            if (stringtolower(parameter) == "quit" || stringtolower(parameter) == "play" || stringtolower(parameter) == "help" || stringtolower(parameter) == "add" || stringtolower(parameter) == "p" || stringtolower(parameter) == "remove" || stringtolower(parameter) == "delete" || stringtolower(parameter) == "list") { // add more names as more commands
                cout << "\nInvalid name\n";
                
            }
        }
        
        cout << "\nEnter a bet amount, Max 100\n";
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cout << "Invalid number!\n\n";
        }
        while ((number%10) != 0 || number < 10 || number > 100) {
            
            cout << "Bets must be a multiple of 10. Max of 100. Enter new bet:\n";
            cin >> number;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cout << "Invalid number!\n\n";
            }
        }
        
        
        
        // add user to game
        player.push_back(User(parameter));
        iter = player.end() - 1;
        cout << endl << iter->playerName()<< "($" << iter->cash() << ") has been added to the game!\n";
        iter -> setBetAmount(number);
    }
    
    
    
    while (!continueGame) {
        cout << "\nType user setting commands, or \"play\". Type\"help\" for command list\n";
        cin >> username;
        username = stringtolower(username);
        
        if (username == "play" || username == "p") {
            playing = true;
            continueGame = true;
        } else if (username == "quit"){
            playing = false;
            continueGame = true;
        } else if (username == "help"){
            // print help
            continueGame = false;
        } else if (username == "list"){
            // print player list
            cout << endl;
            for (int i = 0; i < player.size(); i++) {
                cout << player[i].playerName()<< "($" << player[i].cash() << ") is betting $" << player[i].getBet() << "\n";
            }
            cout << endl;
            continueGame = false;
        } else {
            usernameMatch = false;
            for (int i = 0; i < player.size(); i++) {
                if (stringtolower(username) == stringtolower(player[i].playerName())) {
                    usernameMatch = true;
                    user = i;
                }
            }
            
            if (usernameMatch) {
                //read next parameter
                cin >> parameter;
                parameter = stringtolower(parameter);
                
                if (parameter == "bet") {
                    //read in last parameter for bet amount
                    cin >> number;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                        cout << "Invalid number!\n\n";
                    }
                    while ((number%10) != 0 || number < 10 || number > 100) {
                        
                        cout << "Bets must be a multiple of 10. Max of 100. Enter new bet:\n";
                        cin >> number;
                        cout << endl;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');
                            cout << "Invalid number!\n\n";
                        }
                    }
                    player[user].setBetAmount(number);
                    cout << endl << player[user].playerName()<< "($" << player[user].cash() << ") is now betting $" << player[user].getBet() << "\n";

                }
                
                if (parameter == "cashout" || parameter == "remove" || parameter == "delete") {
                    cout << endl << player[user].playerName()<< "($" << player[user].cash() << ") has cashed out!\n";
                    iter = player.begin();
                    iter += user;
                    player.erase(iter);
                }
                continueGame = false;
                
            } else if (username == "add"){
                if  (player.size() < 7) {
                    cin >> parameter;
                    unique = false;
                    while (!unique) {
                        unique = true;
                        for (int i = 0; i < player.size(); i++){
                            if (stringtolower(parameter) == stringtolower(player[i].playerName())) {
                                unique = false;
                                cout << "\nName must be unique! Enter new name\n";
                                cin >> parameter;
                            }
                        }
                        
                        if (stringtolower(parameter) == "quit" || stringtolower(parameter) == "play" || stringtolower(parameter) == "help" || stringtolower(parameter) == "add") { // add more names as more commands
                            cout << "\nInvalid name\n";
                            
                        }
                    }
                    
                    cout << "\nEnter a bet amount, Max 100\n";
                    cin >> number;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                        cout << "Invalid number!\n\n";
                    }
                    while ((number%10) != 0 || number < 10 || number > 100) {
                        
                        cout << "Bets must be a multiple of 10. Max of 100. Enter new bet:\n";
                        cin >> number;
                        cout << endl;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');
                            cout << "Invalid number!\n\n";
                        }
                    }
                    

                    
                    // add user to game
                    player.push_back(User(parameter));
                    iter = player.end() - 1;
                    cout << endl << iter->playerName()<< "($" << iter->cash() << ") has been added to the game!\n";
                    iter -> setBetAmount(number);
                    
                } else cout << "\nToo many players!\n";
                continueGame = false;
            }else{
                cout << "\nNo matching user or command found\n";
                continueGame = false;
            }
            
            
        }
    }
}

bool Game::play(int playerCount) {
    
    if (playerCount > 4) {
        myDeck.editDecks((playerCount+4)/8 +1);     //scaled for larger amounts of players
    }
    
    string nameCatcher; int betCatcher; bool unique;
    // User player[playerCount];
    for (int i = 0; i < playerCount; i++) {
        unique = false;
        cout << "\n(Player " << i+1 << ") Enter unique name & bet: \n";
        cin >> nameCatcher >> betCatcher;
        
        while (!unique) {
            unique = true;
            for (int i = 0; i < player.size(); i++){
                if (stringtolower(nameCatcher) == stringtolower(player[i].playerName())) {
                    unique = false;
                    cout << "\nName must be unique! Enter new name\n";
                    cin >> nameCatcher;
                }
            }
            
            if (stringtolower(nameCatcher) == "quit" || stringtolower(nameCatcher) == "play" || stringtolower(nameCatcher) == "help" || stringtolower(nameCatcher) == "add" || stringtolower(nameCatcher) == "p" || stringtolower(nameCatcher) == "remove" || stringtolower(nameCatcher) == "delete" || stringtolower(nameCatcher) == "list") { // add more names as more commands
                cout << "\nInvalid name\n";
                
            }
        }

        
        player.push_back(User(nameCatcher));
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cout << "Invalid Input!\n\n";
        }
        while ((betCatcher%10) != 0 || betCatcher < 10 || betCatcher > 100) {

            cout << "Bets must be a multiple of 10. Max of 100. Enter new bet:\n";
            cin >> betCatcher;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cout << "Invalid Input!\n\n";
            }
        }
        player[i].setBetAmount(betCatcher);
        player[i].placeBet();
    }
    cout << string(100, '\n');
    
    string command; bool firstHand = true;
    while (playing) {       // an entire round of blackjack
        myDeck.shuffle();
        house.newHand();
        house.deal(&myDeck);
                
        for (int i = 0; i < player.size(); i++) { //for each player
            player[i].newHand(); //give back old cards
            if (!firstHand) {player[i].placeBet();}
            
            player[i].deal(&myDeck); //deal the player cards
            

            while (!player[i].bust() && !player[i].isStaying()) { //while he hasnt busted
                
                cout << string(100, '\n');
                
                cout << house.playerName();
                if (i == 0) {
                    cout << " draws:" << endl;
                } else cout << ":" << endl;
                
                house.showFlop();
                
                cout << "\n\n" << player[i].playerName() << " draws:" << endl;
                player[i].showHand();
                
                cout << "\nValue: " << player[i].addCards();
                if (player[i].alternateValue() != player[i].addCards()) { //if there is another possible value for the cards
                    cout << " (or " << player[i].alternateValue() << ")";
                }
                cout << endl;
                cout << "\nWhat would you like to do? (Hit, stay)\n";
                cin >> command;
                while (!receiveCommand(&player[i],command)){
                    cout << "Invalid Command\n";
                    cin >> command;
                }
            }
            
            cout << string(100, '\n');
            if (player[i].bust()) {
                cout << player[i].playerName() << " Busted!\n";
            } else {
                cout << player[i].playerName() << " is staying at " << player[i].addCards() << endl;
            }
            
            player[i].showHand();
            cout << "\nValue: " << player[i].addCards() << endl;

            cout << "Hit Enter to proceed\n";
            cin.ignore(INT_MAX,'\n');
            cin.ignore(INT_MAX,'\n');
            cin.clear();
        }
        
        //dealer plays
        while (!house.bust() && !house.isStaying()) { //while dealer hasnt busted
            if (house.addCards() < 17) {
                house.hit(&myDeck);
            } else
                house.stay();
        }
        cout << string(100, '\n');
        cout << house.playerName() << " draws:" << endl;
        house.showHand();
        cout << endl;
        
        printResults();
        cout << endl << endl;
        
        cin.clear();
        
        firstHand = false;
        settings();
    }
    return playing;
}


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
