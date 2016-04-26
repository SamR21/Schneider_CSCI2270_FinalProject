//
//  Blackjack.h
//  Final - Blackjack
//
//  Created by Dylan Schneider on 4/24/16.
//  Copyright © 2016 Dylan Schneider. All rights reserved.
//

#ifndef Blackjack_h
#define Blackjack_h

#include <stdio.h>
#include <vector>

using namespace std;

class Blackjack;
struct Card;
struct player;


struct Card{ // 1 instance per card in a deck of cards
    string name;
    string suit;
    string suitID;
    int value;
    bool isAce;
    bool isFaceUp;
    bool inDeck;
    
    Card(string cardName, string currSuit, string Picture, int currValue, bool Ace){
        name = cardName;
        suit = currSuit;
        suitID = Picture;
        value = currValue;
        isFaceUp = false;
        inDeck = true;
        isAce = Ace;
    }
};

struct player{ //1 for user, 1 for computer
    string Name;
    vector<Card> hand; //vector holds the cards that the players are dealt
    int currentValue; //Always displays highest value when Aces are present - Program will deal with Aces if they cause bust
    int Aces; //Keeps track of the number of Aces in the player hand
    bool Bust; //Determines if the player has busted (value>21)
    bool mustHit; //User never has to hit, dealer mustHit when he has 16 or less, or {A,6}
    bool myTurn; //Determines whos turn it is
    bool win; //Determines if you win
    bool lose; //Determines if you lose
    bool gotBlackjack; //Determines if you get 21 on the initDeal
    
    player(){}; //players initialized in class ctor
};


class Blackjack{
    public:
        Blackjack();
        ~Blackjack();
        
        void resetGame(); //Resets game variables
        void initDeal(); //deal the first 2 cards. order(Player -> Dealer(faced down) -> Player -> Dealer)
        void gameLoop(); //driver for the game
    
    private:
    
        vector<Card> Deck; //vector that changes size as cards are added and deleted
    
        player User; //player for the User
        void userMenu();
    
        player Computer; //player for the dealer (Computer)
    
        void shuffleDeck(); //Shuffle vector Deck
        void buildDeck(); //creates the Cards and adds them to the Deck
    
    
        void updateValue(); //give the players new values after receiving new Cards
        void updateAceValue(player*); //Aces start at value=11, function changes A values if Busting, called from UpdateValue.
        void checkBlackjack(); //Checks Blackjack (Ace + 10) on first hand. Dealer will only check if he shows [A]
    
        void Hit(player*); //Adds one card to hand of whichever player is passed in, updates value, prints the hand
        void printHand(); //prints both User and Computer hand cleanly
    
    
    
        bool winner; //Determines if there is a winner
        bool push; //Determines if there is a draw
        void printWin(); //find and print info about the winner
    
};






#endif /* Blackjack_h */
