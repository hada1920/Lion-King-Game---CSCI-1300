// Hannah Davisson
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Board.h"
#include "Player.h"
#include "Character.h"
#include "Advisor.h"
#include "Event.h"
#include "Riddle.h"
using namespace std;

class Game
{
private:
    Board gameBoard;
    vector<Player> players;
    vector<Character> characters;
    vector<Advisor> advisors;
    vector<Event> events;
    vector<Riddle> riddles;
    int currentPlayerIndex;
    bool gameOver;
    int winner;

    // Private helper methods
    bool loadCharacters(string filename);
    bool loadAdvisors();
    bool loadEvents(string filename);
    bool loadRiddles(string filename);
    void displayCharacters();
    void displayAdvisors();
    int rollSpinner();
    void handleTileEffect(int playerIndex, char tileColor);
    void handleRandomEvent(int playerIndex);
    bool handleRiddle(int playerIndex);
    void handleMainMenu(int playerIndex);
    void checkPlayerProgress(int playerIndex);
    void reviewCharacter(int playerIndex);
    void checkPosition(int playerIndex);
    void reviewAdvisor(int playerIndex);
    void convertTraitsToPoints(int playerIndex);
    Advisor selectAdvisor();

public:
    // Constructor
    Game();
    
    // Game setup
    void initialize();
    void setupPlayers();
    
    // Game flow
    void playGame();
    
    // End game
    void determineWinner();
    bool writeGameStats(string filename);
};

#endif