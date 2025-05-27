// Hannah Davisson
// Player.h defines the Player class
#ifndef PLAYER_H // Include guard to prevent multiple inclusions of the file
#define PLAYER_H

#include "Character.h" // Include the character and advisor classes
#include "Advisor.h"
#include <string>
using namespace std;

class Player
{
private:
    string playerName;   // stores the player's name
    Character character; // stores the player's character choice
    int pathType;        // 0 = Cub Training, 1 = Straight to Pride Lands
    Advisor advisor;     // stores the player's advisor
    int position;
    int previousPosition; // need to track previous position for Hyena's tile
    int movesTaken;
    bool hasAdvisor;

public: // other parts of the program can call these functions
    // Constructors
    Player();                  // blank default
    Player(string playerName); // allows you to pass a name when you create the player

    // Getters (read private variables safely)
    string getPlayerName() const;
    Character getCharacter() const;
    int getPathType() const;
    Advisor getAdvisor() const;
    int getPosition() const;
    int getPreviousPosition() const;
    int getMovesTaken() const;
    bool getHasAdvisor() const;

    // Setters (change private variables safely)
    void setPlayerName(string playerName); // updates the Player's character
    void setCharacter(Character character);
    void setPathType(int pathType);
    void setAdvisor(Advisor advisor);
    void setPosition(int position);
    void setPreviousPosition(int previousPosition);
    void setMovesTaken(int movesTaken);
    void setHasAdvisor(bool hasAdvisor);

    // Game mechanics
    void adjustTraits();
    void moveForward(int spaces);
    void moveBackward(int spaces);
    void applyTileEffect(char tileColor);
    bool isProtectedFromEvent(int advisorRequired);
    void incrementMoves();
    int calculateFinalScore();

    // Print player info to the screen
    void displayPlayerInfo() const;
    void displayStats() const;
};

#endif // include guard (to prevent multiple inclusions of a .h file)