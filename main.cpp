//
//  main.cpp
//  Final - Blackjack
//
//  Created by Dylan Schneider on 4/24/16.
//  Copyright © 2016 Dylan Schneider. All rights reserved.
//

#include <iostream>
#include "Blackjack.h"
#include <cstdlib>
#include <stdlib.h>

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand(unsigned(time(NULL))); //Seed random

    Blackjack Game; //instance of class, builds the deck, initializes some variables
    
    char option; //Game while loop to play multiple times.
    string brk; //Enter any input to continue...
    
    
    do{
        cout<<"The Deck is shuffled and ready to go. Enter any input to continue..."<<endl;
        cin>>brk;
        cout<<"     -----------------     "<<endl;
        
        for(int i=0; i<50; i++)
            cout<<endl;
        
        Game.resetGame(); //reset variables for a new game, shuffles deck
        Game.initDeal(); //First round deal, update, print hand.
        Game.gameLoop(); //Loops that play the game
    
        cout<<endl;
        cout<<"Do you want to play again?: (Y)es or (N)o"<<endl;
        cin>>option;
        
        
    }while(option == 'y' || option == 'Y');
    
    
    
}

