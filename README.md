# Schneider_CSCI2270_FinalProject

This is a basic C++ implementation of Vegas-style BlackJack.
In this game, you are able to play 1-on-1 BlackJack against the dealer (computer).
Since there is no real money involved, having betting in the game is pointless. Just play cards and try to beat the dealer.

Basic Rules:
- Card values based on number, Face cards are 10, Aces are dynamic and can be 1 or 11 at any time. 
- Goal of the game is to get 21, or as close to it as possible without going over 21.
- You get 2 cards faced up. The dealer has 1 card showing, and 1 faced-down to start.
- If the first 2 cards have values adding to 21, we call it "BlackJack".
- BlackJack is an automatic win, for the player or the dealer. If you both get BlackJack, it's called "Push" and neither player wins.
- After getting 2 initial cards, you can "hit" to get another card or "stay".
- After you "stay", the dealer will begin to play his hand. He will then try to beat your number or "push" with it.
- The dealer must hit if his cards value at 16 or less. He is also forced to hit if he has an Ace and 6 (Soft 17).


Good luck!!

**This is a final project for CSCI-2270 at CU Boulder. For this project, I will be implementing many algorithms to play Blackjack, as well as vectors to store the Deck of cards, the User's hand, and the Dealer's hand.**

