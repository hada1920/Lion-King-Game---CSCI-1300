// Hannah Davisson
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace std;

void displayWelcomeMessage()
{
    cout << "==================================================" << endl;
    cout << "     Welcome to THE LION KING Game of Life!       " << endl;
    cout << "==================================================" << endl;
    cout << "Race across the African Savannah to Pride Rock!" << endl;
    cout << "Each player will select a lion character and choose a path." << endl;
    cout << "Navigate through challenges and random events to earn Pride Points." << endl;
    cout << "The player with the most Pride Points at the end will become the next Pride Leader!" << endl;
    cout << "\nPress Enter to start the game...";
    cin.get();
}

int main()
{
    // Seed random number generator
    srand(time(0));

    // Display welcome message
    displayWelcomeMessage();

    // Create and initialize game
    Game lionKingGame;
    lionKingGame.initialize();

    // Play the game
    lionKingGame.playGame();

    return 0;
}