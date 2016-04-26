# Schneider_CSCI2270_FinalProject

**This is a final project for CSCI-2270 at CU Boulder. For this project, I will be implementing many algorithms to play Blackjack, as well as vectors to store the Deck of cards, the User's hand, and the Dealer's hand.**

This is a basic C++ implementation of Vegas-style BlackJack.
In this game, you are able to play 1-on-1 BlackJack against the dealer (computer).
Since there is no real money involved, betting is pointless. Just play 21 and try to beat the dealer.

Basic Rules:
- Card values based on number, Face cards are 10, Aces are dynamic and can be 1 or 11 at any time. 
- Goal of the game is to get 21, or as close to it as possible without going over 21.
- You get 2 cards faced up. The dealer has 1 card showing, and 1 faced-down to start.
- If the first 2 cards have values adding to 21, we call it "BlackJack".
- BlackJack is an automatic win, for the player or the dealer. If you both get BlackJack, it's called "Push" and neither player wins.
- After getting 2 initial cards, you can "hit" to get another card or "stay".
- After you "stay", the dealer will begin to play his hand. He will then try to beat your number or "push" with it.
- The dealer must hit if his cards value at 16 or less. He is also forced to hit if he has an Ace and 6 (Soft 17).
- Since there is no betting involved, Double Down and Split are NOT available in this game.

Good luck!!

How to Run
This section contains instructions, with examples, of how to run your program.
Dependencies
This section contains a description of any dependencies that your program requires. For example, if your program relies on another third-party library that needs to be installed, you should provide a description of where to find that library and instructions for how to install it or a link to installation instructions.
System Requirements
Is your program for Windows, Mac, Linux? Are there additional system requirements other than the operating system?
Group Members
List the people who worked on the project.
Contributors
List the people who were not on the project team, but may have contributed comments, enhancements, and bug fixes.
Open issues/bugs
List any known bugs in the project, and any open enhancement requests.
