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

bool Game::reservedName(string name){
    name = stringtolower(name);
    if (name == "quit" || name == "q" || name == "play" || name == "p" || name == "help" || name == "h" || name == "add" || name == "a" || name == "list" || name == "l" || name == "cashout" || name == "remove" || name == "delete" || name == "d" || name == "credits" || name == "cred") { // add more names as more commands
        return true;
    } else return false;
    
}

void Game::showHelp(){
    cout << "\n\t\tCommands Help\n";
    cout << "\n\t[H]it\t\t\t\t\tDraw a card\n";
    cout << "\t[S]tay\t\t\t\t\tEnd your turn\n";
    cout << "\t[Sp]lit\t\t\t\t\tSplit hand, same bet added on second hand\n";
    cout << "\t[Sur]render\t\t\t\tConcede to dealer, lose only half your bet\n";
    cout << "\t[D]ouble\t\t\t\tDouble bet, recieve one more card\n";
    cout << "\tHelp\t\t\t\t\tShow this dialog\n";

}

bool Game::receiveCommand(User* player, Hand* hand, string command){
    command = stringtolower(command);
    if (command == "hit" || command == "h") {
        hand->hit(&myDeck);
        return true;
    }
    if (command == "stay" || command == "s") {
        hand->stay();
        return true;
    }
    
    if (command == "split" || command == "sp") {
        //if on first turn the two cards match, 2 seperate hands
        if (hand->canSplit() && player->didSplit == false) {
            player->split();
            player->hand.hit(&myDeck);
            player->splitHand.hit(&myDeck);
        } else error = "\nUnable to split hand";
        return true; //NOT FULLY IMPLEMENTED
    }
    if (command == "double" || command == "d") {
        //double wager, take a single card and finish
        player->placeBet(); //place second bet
        hand->doubleHand(&myDeck); //hits and stays
        return true;
    }
    if (command == "surrender" || command == "sur") {
        //give up a half-bet and retire from the game
        hand->surrender();
        return true;
    }

    if (command == "help") {//explain options
        needHelp = true;
    } return true;
    
    return false;
}

void Game::printResultList(const vector<User*> userList, string singleResult, string multipleResult = ""){
    if (multipleResult == "") {     //if no inputed multiple, use single
        multipleResult = singleResult;
    }
    
    bool duplicate = false;
    for (int i = 0; i < userList.size(); i++) { //count the number of users in the list
        for (int j = i+1; j < userList.size(); j++) {
            if (userList[i]->playerName() == userList[j]->playerName()) {
                duplicate = true;
            }
        }
        if (!duplicate) {
            if (userList.size() == 1 ) { //if only one
                if (userList[i]->didSplit) {cout << "[SPLT]";}
                cout << userList[i]->playerName() << "($" << userList[i]->cash() << ")";
                cout << singleResult;
                
            } else if (i == userList.size()-1){ // if the last
                cout << "and ";
                if (userList[i]->didSplit) {cout << "[SPLT]";}
                cout << userList[i]->playerName() << "($" << userList[i]->cash() << ")";
                cout << multipleResult;
            } else if (userList.size() > 2) {  //no comma if only 2 people
                if (userList[i]->didSplit) {cout << "[SPLT]";}
                cout << userList[i]->playerName() << "($" << userList[i]->cash() << ")";
                cout << ", ";
            } else {
                if (userList[i]->didSplit) {cout << "[SPLT]";}
                cout << userList[i]->playerName() << "($" << userList[i]->cash() << ")";
                cout << " ";
            }
        }
    }
}

void Game::printResults(){
    vector<User*> winners, busted, losers, pushed, surrendered;
    if (house.hand.bust()) {
        cout << house.playerName() << " Busted! ";
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (player[i].hand.isSurrendered()) {
                player[i].win(int(player[i].hand.getBet()/2));
                surrendered.push_back(&player[i]);
            } else if (!player[i].hand.bust()) {
                if (player[i].hand.isDoubled()) { //doubles winning if doubled
                    player[i].win(player[i].hand.getBet()*4);
                } else {
                    player[i].win(player[i].hand.getBet()*2);
                }
                winners.push_back(&player[i]);
            } else busted.push_back(&player[i]);
            
            if (player[i].didSplit) {
                //temporary solution
                if (player[i].splitHand.isSurrendered()) {
                    player[i].win(int(player[i].splitHand.getBet()/2));
                    surrendered.push_back(&player[i]);
                } else if (!player[i].splitHand.bust()) {
                    if (player[i].splitHand.isDoubled()) { //doubles winning if doubled
                        player[i].win(player[i].splitHand.getBet()*4);
                    } else {
                        player[i].win(player[i].splitHand.getBet()*2);
                    }
                    winners.push_back(&player[i]);
                } else busted.push_back(&player[i]);
            }
        }
        
        printResultList(winners, " wins!\n", " win!\n");
        printResultList(busted, " busted!\n");
        printResultList(surrendered, " surrendered!\n");
        
        if (busted.size() == player.size()) {
            cout << "\nAll players busted!";
        }
        
        if (winners.size() == 0) {
            cout << "\nDealer wins!\n";
        }
    } else {
        cout << house.playerName() << " stayed at " << house.hand.addCards() << endl;
        for (int i = 0; i < player.size(); i++) { //count the number of winnners
            if (player[i].hand.isSurrendered()) {
                player[i].win(int(player[i].hand.getBet()/2));
                surrendered.push_back(&player[i]);
            } else if (!player[i].hand.bust() && player[i].hand.addCards() > house.hand.addCards()) {
                if (player[i].hand.isDoubled()) {
                    player[i].win(player[i].hand.getBet()*4);
                } else {
                    player[i].win(player[i].hand.getBet()*2);
                }
                winners.push_back(&player[i]);
            } else if (!player[i].hand.bust() && player[i].hand.addCards() == house.hand.addCards()){
                player[i].win(player[i].hand.getBet());
                pushed.push_back(&player[i]);
            } else if (!player[i].hand.bust() && player[i].hand.addCards() < house.hand.addCards()){
                losers.push_back(&player[i]);
            } else busted.push_back(&player[i]);
            
            if (player[i].didSplit) {
                //temporary solution
                if (player[i].splitHand.isSurrendered()) {
                    player[i].win(int(player[i].splitHand.getBet()/2));
                    surrendered.push_back(&player[i]);
                } else if (!player[i].splitHand.bust() && player[i].splitHand.addCards() > house.hand.addCards()) {
                    if (player[i].splitHand.isDoubled()) {
                        player[i].win(player[i].splitHand.getBet()*4);
                    } else {
                        player[i].win(player[i].splitHand.getBet()*2);
                    }
                    winners.push_back(&player[i]);
                } else if (!player[i].splitHand.bust() && player[i].splitHand.addCards() == house.hand.addCards()){
                    player[i].win(player[i].splitHand.getBet());
                    pushed.push_back(&player[i]);
                } else if (!player[i].splitHand.bust() && player[i].splitHand.addCards() < house.hand.addCards()){
                    losers.push_back(&player[i]);
                } else busted.push_back(&player[i]);
            }
        }
        
        printResultList(winners, " wins!\n", " win!\n");
        printResultList(pushed, " pushes\n", " pushed\n");
        printResultList(losers, " loses!\n", " lost!\n");
        printResultList(busted, " busts!\n", " busted!\n");
        printResultList(surrendered, " surrendered!\n");


        
        if (winners.size() == 0 && pushed.size() == 0) {
            cout << endl << house.playerName() << " wins!\n";
        }

    }
    
    vector<User*> broke;
    for (int i = 0; i < player.size(); i++) {
        if (player[i].cash() == 0) {
            broke.push_back(&player[i]); //counts people without money
        }
    }
    
    printResultList(broke, " ran out of money! Leaving table...\n");

    vector<User>::iterator iter;
    for (int i = 0; i < player.size(); i++) { //removes broke people
        if (player[i].cash() == 0) {
            iter = player.begin();
            iter += i;
            player.erase(iter);
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
                }
            }
            
            if (reservedName(parameter)) {
                cout << "\nReserved command word, please use a different name\n";
                unique = false;
            }
            
            if (!unique) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                }
                cin >> parameter;
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
            
            cout << "\nBets must be a multiple of 10. Max of 100. Enter new bet:\n";
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
        cout << "\nType user setting commands, or [P]lay. Type [H]elp for command list\n";
        cin >> username;
        username = stringtolower(username);
        
        if (username == "play" || username == "p") {
            playing = true;
            continueGame = true;
        } else if (username == "quit" || username == "q"){
            playing = false; cout << endl;
            for (int i = 0; i < player.size(); i++) {
                cout << player[i].playerName()<< "($" << player[i].cash() << ") quit the game\n";
            }
            continueGame = true;
        } else if (username == "credits" || username == "cred"){
            cout << "\n\t\tCoded by Justin Oroz\t\t\t\tjustin.oroz@me.com\n";
            continueGame = false;
        } else if (username == "help" || username == "h"){
            // print help
            cout << "\n\t\tCommands Help\n";
            cout << "\n\t[P]lay\t\t\t\t\tStarts a round of Black Jack\n";
            cout << "\t[Q]uit\t\t\t\t\tEnds the game\n";
            cout << "\t[H]elp\t\t\t\t\tBrings up this dialog\n";
            cout << "\t[A]dd\t\t\t\t\tAdd player to game\n";
            cout << "\t[D]elete\t\t\t\tDelete a player from the game\n";
            cout << "\t[L]ist\t\t\t\t\tLists all players and their betting amounts\n";
            cout << "\t[USER] bet [amount]\t\tChange the bet amount for a user\n";
            cout << "\t[Cred]its\t\t\t\tDisplays credits\n";

            
            continueGame = false;
        } else if (username == "list" || username == "l"){
            // print player list
            cout << endl;
            for (int i = 0; i < player.size(); i++) {
                cout << player[i].playerName()<< "($" << player[i].cash() << ") is betting $" << player[i].hand.getBet() << "\n";
            }
            cout << endl;
            continueGame = false;
        } else if (username == "add" || username == "a"){
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
                    unique = !reservedName(parameter); // reloops if a reserved name
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
        } else if (username == "cashout" || username == "remove" || username == "delete" || username == "d") {
            cin >> parameter;
            if (player.size() > 1){
                usernameMatch = false;
                for (int i = 0; i < player.size(); i++) {
                    if (stringtolower(parameter) == stringtolower(player[i].playerName())) {
                        usernameMatch = true;
                        user = i;
                    }
                }
                cout << endl << player[user].playerName()<< "($" << player[user].cash() << ") has cashed out!\n";
                iter = player.begin();
                iter += user;
                player.erase(iter);
            } else cout << "\nCannot delete last player\n";
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
                    cout << endl << player[user].playerName()<< "($" << player[user].cash() << ") is now betting $" << player[user].hand.getBet() << "\n";

                }
                continueGame = false;
                
            } else{
                cout << "\nNo matching user or command found\n";
                continueGame = false;
            }
            
            
        }
    }
}

void Game::playerTurn(User* player, bool flop, bool firstHand){
    string command;
    player->newHand(); //give back old cards
    if (!firstHand) {player->placeBet();}
    
    player->hand.deal(&myDeck); //deal the player cards
    
    cout << string(100, '\n');
    while (!player->hand.bust() && !player->hand.isStaying() && !player->hand.isSurrendered()) { //while he hasnt busted
        
        cout << house.playerName();
        if (flop == true) {
            cout << " draws:" << endl;
            flop = false;
        } else cout << ":" << endl;
        
        house.showFlop();
        
        cout << "\n\n" << player->playerName();
        if (player->didSplit) {
            cout << "'s First Hand:" << endl;
        } else
            cout << " draws:" << endl;
        player->hand.showHand();
        
        cout << "\nValue: " << player->hand.addCards();
        if (player->hand.alternateValue() != player->hand.addCards()) { //if there is another possible value for the cards
            cout << " (or " << player->hand.alternateValue() << ")";
        }
        cout << endl;
        if (needHelp) {
            showHelp();
            needHelp = false;
        }
        if (error != "") {
            cout << "\nError: " << error;
            error = "";
        }
        
        cout << endl;
        cout << "\nWhat would you like to do? ([H]it, [S]tay, Help)\n";
        cin >> command;
        while (!receiveCommand(player, &player->hand,command)){
            cout << "Invalid Command\n";
            cin >> command;
        }
        cout << string(100, '\n');

    }
    
    cout << player->playerName();
    if (player->didSplit) {
        cout << "'s first hand";
    }
    if (player->hand.bust()) {
        cout << " busted!";
    } else if (player->hand.isStaying()){
        cout << " is staying at " << player->hand.addCards();
    } else if (player->hand.isSurrendered()){
        cout << " surrendered";
    }
    cout << endl;
    
    player->hand.showHand();
    cout << "\nValue: " << player->hand.addCards() << endl;
    
    if (Game::player.size() != 1 || player->hand.bust()) {
        cout << "\nPress Enter to proceed\n";
        cin.ignore(INT_MAX,'\n');
        cin.ignore(INT_MAX,'\n');
        cin.clear();
    }
    
    //Split Hand
    if (player->didSplit) {
        while (!player->splitHand.bust() && !player->splitHand.isStaying() && !player->splitHand.isSurrendered()) { //while he hasnt busted
            
            cout << string(100, '\n');

            
            cout << house.playerName() << ":" << endl;
            
            house.showFlop();
            
            cout << "\n\n" << player->playerName() << "'s Second Hand:" << endl;

            
            player->splitHand.showHand();
            
            cout << "\nValue: " << player->splitHand.addCards();
            if (player->splitHand.alternateValue() != player->splitHand.addCards()) { //if there is another possible value for the cards
                cout << " (or " << player->splitHand.alternateValue() << ")";
            }
            cout << endl;
            if (needHelp) {
                showHelp();
                needHelp = false;
            }
            if (error != "") {
                cout << "\nError: " << error;
                error = "";
            }
            
            cout << endl;
            cout << "\nWhat would you like to do? ([H]it, [S]tay, Help)\n";
            cin >> command;
            while (!receiveCommand(player, &player->splitHand,command)){
                cout << "Invalid Command\n";
                cin >> command;
            }
            cout << string(100, '\n');
        }
        
        cout << player->playerName();
        cout << "'s second hand";
        if (player->splitHand.bust()) {
            cout << " busted!";
        } else if (player->splitHand.isStaying()){
            cout << " is staying at " << player->splitHand.addCards();
        } else if (player->splitHand.isSurrendered()){
            cout << " surrendered";
        }
        cout << endl;
        
        player->splitHand.showHand(); //we know the player split his hand
        cout << "\nValue: " << player->splitHand.addCards() << endl;
        
        if (Game::player.size() != 1 || player->splitHand.bust()) {
            cout << "\nPress Enter to proceed\n";
            cin.ignore(INT_MAX,'\n');
            cin.ignore(INT_MAX,'\n');
            cin.clear();
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
            
            if (reservedName(nameCatcher)) {
                cout << "\nReserved command word, please use a different name\n";
                unique = false;
            }
            
            if (!unique) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                }
                cin >> nameCatcher;
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
    
    bool firstHand = true, flop, houseHit;
    while (playing) {       // an entire round of blackjack
        myDeck.shuffle();
        house.hand.newHand();
        house.hand.deal(&myDeck);
        flop = true; houseHit = false;
                
        for (int i = 0; i < player.size(); i++) { //for each player
            if (i != 0) {flop = false;}
            playerTurn(&player[i], flop, firstHand);
            firstHand = false;
        }
        
        //dealer plays
        while (!house.hand.bust() && !house.hand.isStaying()) { //while dealer hasnt busted
            if (house.hand.addCards() < 17) {
                house.hand.hit(&myDeck);
                houseHit = true;
            } else
                house.hand.stay();
        }
        cout << string(100, '\n');
        cout << house.playerName();
        if (houseHit) {
            cout << " draws:" << endl;
        } else cout << ":" << endl;
        house.hand.showHand();
        cout << endl;
        
        printResults();
        cout << endl << endl;
        
        cin.clear();
        
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
