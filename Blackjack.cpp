//
//  Blackjack.cpp
//  Final - Blackjack
//
//  Created by Dylan Schneider on 4/24/16.
//  Copyright © 2016 Dylan Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Blackjack.h"

using namespace std;

Blackjack::Blackjack(){
    cout<<"Welcome to console Blackjack! You will be playing along against the Computer(dealer). Good luck!!"<<endl;
    cout<<"If you have Aces in your hand, the program will intelligently show your best possible score!"<<endl;
    string userName;
    cout<<endl;
    cout<<"Please enter your name: ";
    getline(cin, userName);
    
    User.Name = userName; //Give User a name only once
    Computer.Name = "Dealer"; //Computer named Dealer
    
    buildDeck(); //only needs to happen once
    
    resetGame(); //initialize game
}

Blackjack::~Blackjack(){
    cout<<"Thank you for playing Blackjack!"<<endl;
}

void Blackjack::resetGame(){
    User.myTurn = true; //Starts as Users turn
    User.mustHit = false; //User is never forced to Hit
    User.Bust = false;
    User.hand.clear(); //Clear hand for extra games
    User.currentValue = 0; //Reset current value
    User.Aces = 0;
    User.win = false;
    User.lose = false;
    User.gotBlackjack = false;
    
    Computer.myTurn = false;
    Computer.mustHit = false; //Must hit if his value <= 16, or has {A,6}
    Computer.Bust = false;
    Computer.hand.clear(); //Clear hand
    Computer.currentValue = 0; //Reset current value
    Computer.Aces = 0;
    Computer.win = false;
    Computer.lose = false;
    Computer.gotBlackjack = false;
    
    winner = false; //reset winner
    push = false; //reset push
    
    shuffleDeck();

}

void Blackjack::buildDeck(){  //Deck[0] is bottom, Deck[51] is top;
    
    // Create Hearts
    for(int i = 2; i <= 10; i++){
        string num = to_string(i);
        Deck.push_back(Card(num, "Heart", "♡", i, false));  //Value cards
    }
    Deck.push_back(Card("J", "Heart", "♡", 10, false));
    Deck.push_back(Card("Q", "Heart", "♡", 10, false));  //Face Cards
    Deck.push_back(Card("K", "Heart", "♡", 10, false));
    Deck.push_back(Card("A", "Heart", "♡", 11, true));  //Ace
    
    
    // Create Diamonds
    
    for(int i = 2; i <= 10; i++){
        string num = to_string(i);
        Deck.push_back(Card(num, "Diamond", "♢", i, false));  //Value cards
    }
    Deck.push_back(Card("J", "Diamond", "♢", 10, false));
    Deck.push_back(Card("Q", "Diamond", "♢", 10, false));  //Face Cards
    Deck.push_back(Card("K", "Diamond", "♢", 10, false));
    Deck.push_back(Card("A", "Diamond", "♢", 11, true));  //Ace
    
    
    
    // Create Spades
    for(int i = 2; i <= 10; i++){
        string num = to_string(i);
        Deck.push_back(Card(num, "Spade", "♠", i, false));  //Value cards
    }
    Deck.push_back(Card("J", "Spade", "♠", 10, false));
    Deck.push_back(Card("Q", "Spade", "♠", 10, false));  //Face Cards
    Deck.push_back(Card("K", "Spade", "♠", 10, false));
    Deck.push_back(Card("A", "Spade", "♠", 11, true));  //Ace
    
    
    
    // Create Clubs
    for(int i = 2; i <= 10; i++){
        string num = to_string(i);
        Deck.push_back(Card(num, "Club", "♣", i, false));  //Value cards
    }
    Deck.push_back(Card("J", "Club", "♣", 10, false));
    Deck.push_back(Card("Q", "Club", "♣", 10, false));  //Face Cards
    Deck.push_back(Card("K", "Club", "♣", 10, false));
    Deck.push_back(Card("A", "Club", "♣", 11, true));  //Ace
    
    for(int i=0; i<Deck.size(); i++) { //Tell each card that it is in the Deck
        Deck[i].inDeck = true;
    }
    
    
}

int myrandom(int i){  //random Int
    return std::rand()%i;
}

void Blackjack::shuffleDeck(){
    random_shuffle(Deck.begin(), Deck.end(), myrandom);
}




void Blackjack::initDeal(){
    
    User.hand.push_back(Deck.back());
    Deck.pop_back(); //remove from Deck.
    
    Computer.hand.push_back(Deck.back()); //dealer's second Card isFaceUp stays false until User finishes their turn.
    Deck.pop_back();
    
    User.hand.push_back(Deck.back());
    Deck.pop_back();
    
    Computer.hand.push_back(Deck.back());
    Deck.pop_back();
    
    Computer.hand[0].inDeck = false;
    Computer.hand[0].isFaceUp = false; //1st card of Dealer stays faced down until it's their turn
    if(Computer.hand[0].isAce){Computer.Aces++;}
    Computer.hand[1].inDeck = false;
    Computer.hand[1].isFaceUp  = true;
    if(Computer.hand[1].isAce){Computer.Aces++;}
    
    
    User.hand[0].isFaceUp = true;
    User.hand[0].inDeck = false;
    if(User.hand[0].isAce){User.Aces++;}
    User.hand[1].isFaceUp = true;
    if(User.hand[1].isAce){User.Aces++;}
    User.hand[1].inDeck = false;
    
    updateValue();
    printHand();
    checkBlackjack();
    return;
}


void Blackjack::updateValue(){
    
    //Recount the whole hand starting from scratch
    User.currentValue = 0;
    for(int i = 0; i < User.hand.size(); i++)
        User.currentValue+=User.hand[i].value;
    
    Computer.currentValue = 0;
    for(int i = 0; i < Computer.hand.size(); i++)
        Computer.currentValue+=Computer.hand[i].value;
    
        
    //Updates if User has Aces, always shows highest possible value
    if(User.Aces>0 && User.myTurn){
        updateAceValue(&User);  //recalls updateValue
        return;
    }
    
    if(Computer.Aces>0 && Computer.myTurn){
        updateAceValue(&Computer); //recalls updateValue

        return;
    }
    
    
    //Bust >21
    if(User.currentValue > 21){
        User.Bust = true;
        winner = true;
        User.lose = true;
        Computer.win = true;
    }
    else if(Computer.currentValue > 21){
        Computer.Bust = true;
        winner = true;
        Computer.lose = true;
        User.win = true;
    }
    
    
    
    //When the Dealer must hit
    if((Computer.hand[0].isAce && Computer.hand[1].value == 6) || (Computer.hand[1].isAce && Computer.hand[0].value == 6)){
        Computer.mustHit = true;
    }
    else if(Computer.currentValue <= 16){
        Computer.mustHit = true;
    }
    else{
        Computer.mustHit = false;
    }
    
}

void Blackjack::updateAceValue(player* check){
    if(check->currentValue <= 21 && check->Aces == 1){ //only have one Ace that doesnt bust
        return;
    }
    else if(check->currentValue > 21){
        
        int newValue = 0; //value of hand without aces
        for(int i=0; i<check->hand.size(); i++){
            if(check->hand[i].value != 11){
                newValue += check->hand[i].value;
            }
        }
        int handled = 0;
        switch(check->Aces){
                //We will *AT MOST* need to deal with 2 aces at a time, When the third ace is reached the others will have already been fixed
                
            case 1:  //if 1 ace at =11 causes a bust, set its value =1
                if(newValue+11 > 21){
                    for(int i=0; (i<check->hand.size() && handled == 0); i++){
                        if(check->hand[i].value == 11){
                            check->hand[i].value = 1;
                            check->Aces--;
                            //check->currentValue-=10;
                            handled++;
                            
                        }
                    }
                    updateValue(); //only update if we change an Ace value
                }
                return;
                
                
            case 2: //if 2 aces cause bust, we may be able to set one to 1, leave one at 11. Unless newValue+12 > 21, both A=1
                
                if(newValue+12 <= 21){ //Use an ace as 11, another as 1
                    for(int i=0; i<check->hand.size() && handled < 1; i++){ //set one to 11, leave one at 1
                        if(check->hand[i].value == 11){
                            check->hand[i].value = 1;
                            check->Aces--;
                            handled++;
                        }
                    }
                }
                else if(newValue+12 > 21){ //Use both aces as 1, because using an ace as 11 causes bust
                    for(int i=0; (i<check->hand.size() && handled < 2); i++){ //set both =1
                        if(check->hand[i].value == 11){
                            check->hand[i].value = 1;
                            check->Aces--;
                            handled++;
                        }
                    }
                }
                updateValue(); //update no matter what
                return;
                
        }
    }
}


void Blackjack::checkBlackjack(){
    if(User.currentValue == 21 && Computer.currentValue == 21){ //if they both have 21, no one wins
        push = true; //win and lose stay false for both players;
    }
    else if(User.currentValue == 21){
        User.win = true;
        User.gotBlackjack = true;
        Computer.lose = true;
        winner = true;
    }
    else if(Computer.currentValue == 21 && Computer.hand[1].isAce){
        Computer.win = true;
        Computer.gotBlackjack = true;
        User.lose = true;
        winner = true;
    }
    
}



void Blackjack::printHand(){
    cout<<Computer.Name<<": ";
    for(int i = 0; i < Computer.hand.size(); i++){
        if(!Computer.hand[i].isFaceUp)
            cout<<"[ ]";
        else
            cout<<"["<<Computer.hand[i].name+Computer.hand[i].suitID<<"]";
    }
    if(Computer.myTurn && !winner)
        cout<<"  -- value -- "<<Computer.currentValue;
    
    cout<<endl<<endl;
    
    cout<<User.Name<<": ";
    for(int i = 0; i < User.hand.size(); i++){
        cout<<"["<<User.hand[i].name+User.hand[i].suitID<<"]";
    }
    if(User.myTurn && !winner)
        cout<<"  -- value -- "<<User.currentValue;
    cout<<endl;
}



void Blackjack::userMenu(){
    cout<<"Select your move:"<<endl;
    cout<<"1. Hit"<<endl;
    cout<<"2. Stay"<<endl;
}

void Blackjack::Hit(player *check){
    if(Deck.back().isAce){
        check->Aces++;
    }
    check->hand.push_back(Deck.back()); //Give the player the next card
    check->hand.back().isFaceUp = true;
    Deck.back().inDeck = false;
    Deck.pop_back(); //Take the given card out of the Deck
    
    updateValue(); //Update the current hand
    printHand(); //Print the hands
}





void Blackjack::gameLoop(){
    
    int choice; //User menu choice
    string brk; //Enter any input to continue...
    
    while(!winner && !push){ //Game loop
        //User loop: breaks if they Bust or Stay or have 21
        while(User.myTurn && !User.Bust && User.currentValue!=21){ //No choice if value==21 -> dealer turn
            cout<<endl;
            userMenu();
            cin>>choice;
            switch (choice) {
                case 1:
                    for(int i=0; i<50; i++)
                        cout<<endl;
                    Hit(&User);
                    break;
                    
                case 2:
                    for(int i=0; i<50; i++)
                        cout<<endl;
                    cout<<"Alright, you have "<<User.currentValue<<'.'<<endl<<"Now it is the dealer's turn."<<endl;
                    User.myTurn = false; //ends User turn
                    Computer.myTurn = true; //Dealer only gets a turn if they choose Stay (not bust)
                    break;
            }
            if(User.currentValue == 21){
                
                cout<<"Alright, you have 21."<<endl<<"Now it is the dealer's turn."<<endl;
                Computer.myTurn = true;
            }
            
        }
        //ends User loop
        
        Computer.hand[0].isFaceUp = true; //after User turn, the Dealer will flip up other card
        if(User.Bust) //Break out of Game loop if the user has busted
            break;
        
        
        cout<<"Enter any input to continue..."<<endl;
        cin>>brk;
        for(int i=0; i<50; i++)
            cout<<endl;
        printHand();
        while(Computer.myTurn && !Computer.Bust && !winner){//Game loop Dealer
            //cout<<"REACH"<<endl;
            
            if(Computer.mustHit){ //Hit for dealer
                cout<<endl<<"Dealer must hit, Enter any input to continue..."<<endl;
                cin>>brk;
                for(int i=0; i<50; i++)
                    cout<<endl;
                Hit(&Computer);
            }
            else{ //Determine if dealer will hit or stay(win)
                //determine winner
                if(Computer.currentValue < User.currentValue){ //Not forced to hit, but will lose if they don't
                    cout<<endl<<"Dealer will hit, Enter any input to continue..."<<endl;
                    cin>>brk;
                    for(int i=0; i<50; i++)
                        cout<<endl;
                    Hit(&Computer);
                    continue;
                }
                else if(Computer.currentValue == User.currentValue){ //Not forced to hit, dealer will push
                    push = true;
                    break;
                }
                else if(Computer.currentValue > User.currentValue){ //Dealer not forced to hit and wins
                    winner = true;
                    Computer.win = true;
                    User.lose = true;
                    break;
                }
            }
        }
    }
    cout<<endl<<endl<<endl;
    if(push){
        for(int i=0; i<50; i++)
            cout<<endl;
        printHand();
        cout<<endl;
        cout<<"There is a draw, no one wins this game."<<endl;
        
    }
    else if(winner){
        for(int i=0; i<50; i++)
            cout<<endl;
        printHand();
        cout<<endl;
        printWin();
    }
    
}


void Blackjack::printWin(){
    if(User.win){
        
        if(User.gotBlackjack){
            cout<<"BLACKJACK! You automatically win!"<<endl;
        }
        else{
            cout<<User.Name<<", you win with a score of "<<User.currentValue<<"!"<<endl;
            if(Computer.Bust)
                cout<<"The Dealer busted with a score of "<<Computer.currentValue<<endl;
            else
                cout<<"Sorry "<<Computer.Name<<", you have "<<Computer.currentValue<<"."<<endl;
        }
        
        
    }
    
    else if(Computer.win){
        if(Computer.gotBlackjack){
            cout<<"The Dealer got Blackjack, you automatically lose..."<<endl;
            
        }
        cout<<Computer.Name<<" wins with a score of "<<Computer.currentValue<<endl;
        if(User.Bust)
            cout<<"You busted with a score of "<<User.currentValue<<"."<<endl;
        else
            cout<<"Sorry "<<User.Name<<", you only have "<<User.currentValue<<endl;
    }
    
}



