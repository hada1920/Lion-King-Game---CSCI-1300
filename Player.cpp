// Hannah Davisson
#include "Player.h"
#include <iostream>

// Default constructor with blank player and default values
Player::Player()
{
    playerName = "";
    pathType = -1;
    position = 0;
    previousPosition = 0;
    movesTaken = 0;
    hasAdvisor = false;
}

// Parameterized constructor
Player::Player(string playerName)
{                                  // parameter and member variable have the same name, will cause error
    this->playerName = playerName; // sets member's variable playerName to the passed name (also playerName)
    pathType = -1;                 // 0 is cub training, 1 is Pridelands
    position = 0;
    previousPosition = 0;
    movesTaken = 0;
    hasAdvisor = false;
}

// Getters
string Player::getPlayerName() const
{
    return playerName;
}

Character Player::getCharacter() const
{
    return character;
}

int Player::getPathType() const
{
    return pathType;
}

Advisor Player::getAdvisor() const
{
    return advisor;
}

int Player::getPosition() const
{
    return position;
}

int Player::getPreviousPosition() const
{
    return previousPosition;
}

int Player::getMovesTaken() const
{
    return movesTaken;
}

bool Player::getHasAdvisor() const
{
    return hasAdvisor;
}

// Setters
void Player::setPlayerName(string playerName)
{
    this->playerName = playerName;
}

void Player::setCharacter(Character character)
{
    this->character = character;
}

void Player::setPathType(int pathType)
{
    this->pathType = pathType;
}

void Player::setAdvisor(Advisor advisor)
{
    this->advisor = advisor;
    this->hasAdvisor = true;
}

void Player::setPosition(int position)
{
    this->previousPosition = this->position;
    this->position = position;
}

void Player::setPreviousPosition(int previousPosition)
{
    this->previousPosition = previousPosition;
}

void Player::setMovesTaken(int movesTaken)
{
    this->movesTaken = movesTaken;
}

void Player::setHasAdvisor(bool hasAdvisor)
{
    this->hasAdvisor = hasAdvisor;
}

// Game mechanics
void Player::adjustTraits()
{
    // Apply path-specific bonuses and penalties
    if (pathType == 0)
    { // Cub Training
        // Lose 5000 Pride Points
        character.setPridePoints(character.getPridePoints() - 5000);

        // Add 500 to Stamina, 500 to Strength, 1000 to Wisdom
        character.setStamina(character.getStamina() + 500);
        character.setStrength(character.getStrength() + 500);
        character.setWisdom(character.getWisdom() + 1000);
    }
    else if (pathType == 1)
    { // Straight to Pride Lands
        // Gain 5000 Pride Points
        character.setPridePoints(character.getPridePoints() + 5000);

        // Add 200 to all traits
        character.setStamina(character.getStamina() + 200);
        character.setStrength(character.getStrength() + 200);
        character.setWisdom(character.getWisdom() + 200);
    }

    // Ensure traits don't fall below 100
    if (character.getStamina() < 100)
        character.setStamina(100);
    if (character.getStrength() < 100)
        character.setStrength(100);
    if (character.getWisdom() < 100)
        character.setWisdom(100);
}

void Player::moveForward(int spaces)
{
    previousPosition = position;
    position += spaces;

    // Make sure we don't go past the last tile (index 51)
    if (position > 51)
    {
        position = 51;
    }
}

void Player::moveBackward(int spaces)
{
    previousPosition = position;
    position -= spaces;

    // Make sure we don't go before the first tile (index 0)
    if (position < 0)
    {
        position = 0;
    }
}

// Apply effects based on tile color
void Player::applyTileEffect(char tileColor)
{
    switch (tileColor)
    {
    case 'B': // Blue (Oasis)
        // Extra turn handled in game logic
        // Add 200 to all traits
        character.setStamina(character.getStamina() + 200);
        character.setStrength(character.getStrength() + 200);
        character.setWisdom(character.getWisdom() + 200);
        break;

    case 'P': // Pink (Counseling)
        // Add 300 to all traits
        character.setStamina(character.getStamina() + 300);
        character.setStrength(character.getStrength() + 300);
        character.setWisdom(character.getWisdom() + 300);
        // Advisor selection handled in game logic
        break;

    case 'R': // Red (Graveyard)
        // Move back 10 spaces handled in game logic
        // Lose 100 from all traits
        character.setStamina(character.getStamina() - 100);
        character.setStrength(character.getStrength() - 100);
        character.setWisdom(character.getWisdom() - 100);

        // Ensure traits don't fall below 100
        if (character.getStamina() < 100)
            character.setStamina(100);
        if (character.getStrength() < 100)
            character.setStrength(100);
        if (character.getWisdom() < 100)
            character.setWisdom(100);
        break;

    case 'N': // Brown (Hyenas)
        // Return to previous position handled in game logic
        // Lose 300 Stamina
        character.setStamina(character.getStamina() - 300);

        // Ensure stamina doesn't fall below 100
        if (character.getStamina() < 100)
            character.setStamina(100);
        break;

    case 'U': // Purple (Challenge)
        // Riddle challenge handled in game logic
        // If answered correctly, gain 500 Wisdom (handled in game logic)
        break;
    }
}

bool Player::isProtectedFromEvent(int advisorRequired)
{
    if (!hasAdvisor)
    {
        return false;
    }

    return (advisor.getId() == advisorRequired);
}

void Player::incrementMoves()
{
    movesTaken++;
}

int Player::calculateFinalScore()
{
    int finalScore = character.getPridePoints();

    // Convert Leadership Traits to Pride Points
    // For every 100 points in Stamina, Strength, or Wisdom, add 1000 Pride Points
    finalScore += (character.getStamina() / 100) * 1000;
    finalScore += (character.getStrength() / 100) * 1000;
    finalScore += (character.getWisdom() / 100) * 1000;

    return finalScore;
}

// Display player info
void Player::displayPlayerInfo() const
{
    cout << "Player: " << playerName << endl;
    cout << "Character: " << character.getName() << " (Age: " << character.getAge() << ")" << endl;
    cout << "Path: " << (pathType == 0 ? "Cub Training" : "Straight to Pride Lands") << endl;

    if (hasAdvisor)
    {
        cout << "Advisor: " << advisor.getName() << " (" << advisor.getAbility() << ")" << endl;
    }
    else
    {
        cout << "Advisor: None" << endl;
    }

    cout << "Position: " << position << endl;
    cout << "Moves Taken: " << movesTaken << endl;
}

void Player::displayStats() const
{
    cout << "Pride Points: " << character.getPridePoints() << endl;
    cout << "Stamina: " << character.getStamina() << endl;
    cout << "Strength: " << character.getStrength() << endl;
    cout << "Wisdom: " << character.getWisdom() << endl;
}