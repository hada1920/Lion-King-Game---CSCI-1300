// Hannah Davisson
#include "Game.h" // Include the Game class header which organizes the game logic
#include <iostream>
#include <fstream> // File I/O for loading characters, events, and riddles
#include <cstdlib> // Srand() seeds number generator rand() spins spinner 1-6
#include <ctime>   // Use time(0) to make the random numbers actually random, not same sequence every time
#include <algorithm>
#include <cctype>

// Constructor that sets up basic starting values for the game
Game::Game()
{
    currentPlayerIndex = 0;
    gameOver = false;
    winner = -1;

    // Seed random number generator with the time to ensure different sequences
    srand(time(0));
}

// Initialize game
void Game::initialize()
{
    // Load game data
    loadCharacters("characters.txt"); // Parameter filename given the value "random_events.txt"
    loadAdvisors();
    loadEvents("random_events.txt");
    loadRiddles("riddles.txt");

    // Create the board
    gameBoard = Board(2); // 2 players

    // Set up players
    setupPlayers();
}

// Load character data from file
bool Game::loadCharacters(string filename) // "random_events.txt" passed as argument to function loadEvents
{
    ifstream file(filename); // Open "characters.txt"
    if (!file.is_open())
    {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    string name;
    int age, strength, stamina, wisdom, pridePoints;

    // Skip header line
    getline(file, line);

    while (file >> name >> age >> strength >> stamina >> wisdom >> pridePoints) // Reads the six values from the file, whitespace separates inputs
    {
        Character character(name, age, strength, stamina, wisdom, pridePoints);
        characters.push_back(character); // vectorName.push_back(objectName) adds the new Character object to the characters vector (holds all playable lions)
    } // Runs as long as a full line of values is successfully read

    file.close();
    return !characters.empty(); // Will return true if the vector is not empty
}

// Load advisor data
bool Game::loadAdvisors()
{
    // Hard-coded advisors using the vectorName.push_back(objectName) method
    advisors.push_back(Advisor("Rafiki", "Invisibility (the ability to become un-seen)", 1));
    advisors.push_back(Advisor("Nala", "Night Vision (the ability to see clearly in darkness)", 2));
    advisors.push_back(Advisor("Sarabi", "Energy Manipulation (the ability to shape and control the properties of energy)", 3));
    advisors.push_back(Advisor("Zazu", "Weather Control (the ability to influence and manipulate weather patterns)", 4));
    advisors.push_back(Advisor("Sarafina", "Super Speed (the ability to run 4x faster than the maximum speed of lions)", 5));

    return !advisors.empty(); // Returns true if the vector is not empty
}

// Load event data from file
bool Game::loadEvents(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line))                 // Loop until there are no lines left in the file
    {                                           // use size_t to represent the positions of '|' in the line
        size_t pos1 = line.find('|');           // Returns the index of the first '|' in the string
        size_t pos2 = line.find('|', pos1 + 1); // Returns the next '|' after the '\' at index pos1
        size_t pos3 = line.find('|', pos2 + 1);
        // Splits the sting into parts

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos)
        {                                                                  // Check if all three '|' were found, only then create the event
            Event event;                                                   // Create new object called Event
            event.description = line.substr(0, pos1);                      // Sets and stores event description
            event.pathType = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)); // Store path type as an int
            event.advisorProtection = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            event.pridePointsEffect = stoi(line.substr(pos3 + 1));

            events.push_back(event); // Adds the new Event object to the events vector
        }
    }

    file.close();
    return !events.empty(); // Returns true if the vector is not empty
}

// Load riddle data from file
bool Game::loadRiddles(string filename) // "riddles.txt" stored as filename passed as argument
{
    ifstream file(filename);
    if (!file.is_open()) // Verify that the file opened successfully
    {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    // Skip header line
    getline(file, line);

    while (getline(file, line)) // Keeps looping when there are lines left to read from
    {
        size_t pos = line.find('|'); // Find the first '|' in the line
        // Splits the string into question and answer
        if (pos != string::npos) // If the string is NOT not found
        {
            Riddle riddle;
            riddle.question = line.substr(0, pos); // Set riddle question
            riddle.answer = line.substr(pos + 1);  // Set riddle answer

            riddles.push_back(riddle); // Adds the new Riddle object to the riddles
        }
    }

    file.close();
    return !riddles.empty();
}

// Display available characters
void Game::displayCharacters()
{
    cout << "\nAvailable Characters:" << endl;
    cout << "---------------------" << endl;

    for (size_t i = 0; i < characters.size(); i++)
    {
        if (!characters[i].getIsSelected()) // Only displays characters that have not been chosen yet

        {
            cout << i + 1 << ". " << characters[i].getName() << " (Age: " << characters[i].getAge() << ")" << endl;
            cout << "   Strength: " << characters[i].getStrength();
            cout << "   Stamina: " << characters[i].getStamina();
            cout << "   Wisdom: " << characters[i].getWisdom();
            cout << "   Pride Points: " << characters[i].getPridePoints() << endl;
            cout << endl;
        }
    }
}

// Display available advisors
void Game::displayAdvisors()
{
    cout << "\nAvailable Advisors:" << endl;
    cout << "------------------" << endl;

    for (size_t i = 0; i < advisors.size(); i++)
    {
        if (!advisors[i].getIsSelected()) // Same logic as above
        {
            cout << i + 1 << ". " << advisors[i].getName() << " - " << advisors[i].getAbility() << endl;
        }
    }
}

// Roll spinner (1-6)
int Game::rollSpinner()
{
    return (rand() % 6) + 1; // (rand() % 6) gives possibilities 0-5, +1 gives 1-6
}

// Handle tile effects
void Game::handleTileEffect(int playerIndex, char tileColor)
{
    int roll;
    bool correct;

    switch (tileColor)
    {
    case 'G': // Green (Regular)
        cout << "You landed on a Green (Regular) tile." << endl;
        // 50% chance for a random event
        if (rand() % 2 == 0)
        {
            handleRandomEvent(playerIndex);
        }
        else
        {
            cout << "Nothing happens on this tile." << endl;
        }
        break;

    case 'B': // Blue (Oasis)
        cout << "You landed on a Blue (Oasis) tile!" << endl;
        cout << "You've found a peaceful oasis! This grants you an extra turn and +200 to all traits." << endl;
        players[playerIndex].applyTileEffect(tileColor);

        // Extra turn
        cout << "Press Enter for your extra turn...";
        cin.ignore();
        cin.get();

        // Roll spinner for extra turn
        roll = rollSpinner();
        cout << "You rolled a " << roll << "!" << endl;

        // Move player
        players[playerIndex].moveForward(roll);
        players[playerIndex].incrementMoves();

        // Handle the new tile
        handleTileEffect(playerIndex, gameBoard.getTileColor(players[playerIndex].getPathType(), players[playerIndex].getPosition()));
        ;
        break;

    case 'P': // Pink (Counseling)
        cout << "You landed on a Pink (Counseling) tile!" << endl;
        cout << "Welcome to the land of enrichment! Your traits increase by 300 each." << endl;
        players[playerIndex].applyTileEffect(tileColor);

        // Select or change advisor
        if (players[playerIndex].getHasAdvisor())
        {
            cout << "You currently have " << players[playerIndex].getAdvisor().getName() << " as your advisor." << endl;
            cout << "Would you like to change your advisor? (y/n): ";

            char choice;
            cin >> choice;

            if (tolower(choice) == 'y')
            {
                Advisor newAdvisor = selectAdvisor();
                players[playerIndex].setAdvisor(newAdvisor);
                cout << "You have chosen " << newAdvisor.getName() << " as your new advisor!" << endl;
            }
        }
        else
        {
            cout << "You don't have an advisor yet. Choose one now:" << endl;
            Advisor newAdvisor = selectAdvisor();
            players[playerIndex].setAdvisor(newAdvisor);
            cout << "You have chosen " << newAdvisor.getName() << " as your advisor!" << endl;
        }
        break;

    case 'R': // Red (Graveyard)
        cout << "You landed on a Red (Graveyard) tile!" << endl;
        cout << "Uh-oh, you've stumbled into the Graveyard! Move back 10 tiles and lose 100 from all traits." << endl;
        players[playerIndex].applyTileEffect(tileColor);
        players[playerIndex].moveBackward(10);
        cout << "You've been moved back to position " << players[playerIndex].getPosition() << "." << endl;
        break;

    case 'N': // Brown (Hyenas)
        cout << "You landed on a Brown (Hyenas) tile!" << endl;
        cout << "The Hyenas are on the prowl! They drag you back to where you were last, and you lose 300 Stamina." << endl;
        players[playerIndex].applyTileEffect(tileColor);
        players[playerIndex].setPosition(players[playerIndex].getPreviousPosition());
        cout << "You've been moved back to position " << players[playerIndex].getPosition() << "." << endl;
        break;

    case 'U': // Purple (Challenge)
        cout << "You landed on a Purple (Challenge) tile!" << endl;
        cout << "Time for a test of wits! Answer a riddle correctly to earn 500 Wisdom." << endl;

        // Handle riddle
        correct = handleRiddle(playerIndex);

        if (correct)
        {
            cout << "Congratulations! Your wisdom increases by 500 points." << endl;
            Character character = players[playerIndex].getCharacter();
            character.setWisdom(character.getWisdom() + 500);
            players[playerIndex].setCharacter(character);
        }
        else
        {
            cout << "Better luck next time!" << endl;
        }
        break;

    case 'O': // Orange (Pride Rock)
        cout << "You reached Pride Rock!" << endl;
        break;

    case 'Y': // Grey (Starting)
        cout << "You're at the starting position." << endl;
        break;
    }
}

void Game::handleRandomEvent(int playerIndex)
{
    int pathType = players[playerIndex].getPathType();

    // Filter events based on player's path type
    vector<Event> applicableEvents;
    for (const Event event : events)
    {
        if (event.pathType == pathType || event.pathType == 2)
        {
            applicableEvents.push_back(event);
        }
    }

    if (applicableEvents.empty())
    {
        cout << "No applicable events found." << endl;
        return;
    }

    // Select a random event
    int eventIndex = rand() % applicableEvents.size();
    Event selectedEvent = applicableEvents[eventIndex];

    cout << "Random Event: " << selectedEvent.description << endl;

    // Check if player is protected by advisor
    if (selectedEvent.pridePointsEffect < 0 &&
        players[playerIndex].isProtectedFromEvent(selectedEvent.advisorProtection))
    {
        cout << "Your advisor " << players[playerIndex].getAdvisor().getName()
             << " protected you from this negative event!" << endl;
    }
    else
    {
        // Apply effect
        Character character = players[playerIndex].getCharacter();
        int newPridePoints = character.getPridePoints() + selectedEvent.pridePointsEffect;
        character.setPridePoints(newPridePoints);
        players[playerIndex].setCharacter(character);

        if (selectedEvent.pridePointsEffect > 0)
        {
            cout << "You gained " << selectedEvent.pridePointsEffect << " Pride Points!" << endl;
        }
        else
        {
            cout << "You lost " << -selectedEvent.pridePointsEffect << " Pride Points!" << endl;
        }
    }
}

// Handle riddle challenge
bool Game::handleRiddle(int playerIndex)
{
    if (riddles.empty())
    {
        cout << "No riddles available." << endl;
        return false;
    }

    // Select a random riddle
    int riddleIndex = rand() % riddles.size();
    Riddle selectedRiddle = riddles[riddleIndex];

    cout << "Riddle: " << selectedRiddle.question << endl;
    cout << "Your answer: ";

    string playerAnswer;
    cin.ignore();
    getline(cin, playerAnswer);

    // Convert to lowercase for case-insensitive comparison
    string correctAnswer = selectedRiddle.answer;
    transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), ::tolower);
    transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), ::tolower);

    return (playerAnswer == correctAnswer);
}

// Handle main menu
void Game::handleMainMenu(int playerIndex)
{

    int choice = 0;
    while (choice != 5)
    {
        cout << "\nMain Menu: Select an option to continue" << endl;
        cout << "1. Check Player Progress" << endl;
        cout << "2. Review Character" << endl;
        cout << "3. Check Position" << endl;
        cout << "4. Review your Advisor" << endl;
        cout << "5. Move Forward" << endl;
        cout << "\nPlease choose an option: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 5)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please choose a valid option (1-5): ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            checkPlayerProgress(playerIndex);
            break;
        case 2:
            reviewCharacter(playerIndex);
            break;
        case 3:
            checkPosition(playerIndex);
            break;
        case 4:
            reviewAdvisor(playerIndex);
            break;
        case 5:
            // Will exit the loop and continue with the turn
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
}

// Check player progress
void Game::checkPlayerProgress(int playerIndex)
{

    cout << "\nPlayer Progress:" << endl;
    cout << "---------------" << endl;
    players[playerIndex].displayStats();

    cout << "\nWould you like to convert Leadership Traits to Pride Points? (y/n): ";
    char choice;
    cin >> choice;

    if (tolower(choice) == 'y')
    {
        convertTraitsToPoints(playerIndex);
    }
}

// Review character
void Game::reviewCharacter(int playerIndex)
{

    cout << "\nCharacter Information:" << endl;
    cout << "---------------------" << endl;
    cout << "Name: " << players[playerIndex].getCharacter().getName() << endl;
    cout << "Age: " << players[playerIndex].getCharacter().getAge() << endl;
}

// Check position
void Game::checkPosition(int playerIndex)
{
    Player player = players[playerIndex];

    cout << "\nBoard Position:" << endl;
    cout << "--------------" << endl;
    cout << "Current position: " << player.getPosition() << " / 51" << endl;
    cout << "Path: " << (players[playerIndex].getPathType() == 0 ? "Cub Training" : "Straight to Pride Lands") << endl;
}

// Review advisor
void Game::reviewAdvisor(int playerIndex)
{

    cout << "\nAdvisor Information:" << endl;
    cout << "-------------------" << endl;

    if (players[playerIndex].getHasAdvisor())
    {
        cout << "Name: " << players[playerIndex].getAdvisor().getName() << endl;
        cout << "Ability: " << players[playerIndex].getAdvisor().getAbility() << endl;

        cout << "\nWould you like to use your advisor's ability? (y/n): ";
        char choice;
        cin >> choice;

        if (tolower(choice) == 'y')
        {
            cout << "Using " << players[playerIndex].getAdvisor().getName() << "'s ability..." << endl;
            cout << "Your advisor's ability will protect you from certain negative random events." << endl;
        }
    }
    else
    {
        cout << "You don't have an advisor yet. You can get one by landing on a Pink (Counseling) tile." << endl;
    }
}

// Convert Leadership Traits to Pride Points
void Game::convertTraitsToPoints(int playerIndex)
{

    Character character = players[playerIndex].getCharacter();

    int staminaToConvert, strengthToConvert, wisdomToConvert;

    // Stamina input
    cout << "Enter the amount of Stamina to convert (must leave at least 100): ";
    cin >> staminaToConvert;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid number for Stamina: ";
        cin >> staminaToConvert;
    }

    // Strength input
    cout << "Enter the amount of Strength to convert (must leave at least 100): ";
    cin >> strengthToConvert;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid number for Strength: ";
        cin >> strengthToConvert;
    }

    // Wisdom input
    cout << "Enter the amount of Wisdom to convert (must leave at least 100): ";
    cin >> wisdomToConvert;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid number for Wisdom: ";
        cin >> wisdomToConvert;
    }

    // Make sure traits stay above 100
    if (character.getStamina() - staminaToConvert < 100 ||
        character.getStrength() - strengthToConvert < 100 ||
        character.getWisdom() - wisdomToConvert < 100)
    {
        cout << "Error: You must leave at least 100 points in each trait." << endl;
        return;
    }

    // Calculate how many Pride Points to add
    int pridePointsToAdd = 0;
    pridePointsToAdd += (staminaToConvert / 100) * 1000;
    pridePointsToAdd += (strengthToConvert / 100) * 1000;
    pridePointsToAdd += (wisdomToConvert / 100) * 1000;

    // Update the character's traits
    character.setStamina(character.getStamina() - staminaToConvert);
    character.setStrength(character.getStrength() - strengthToConvert);
    character.setWisdom(character.getWisdom() - wisdomToConvert);
    character.setPridePoints(character.getPridePoints() + pridePointsToAdd);

    // Save the updated character back into the player
    players[playerIndex].setCharacter(character);

    cout << "Converted " << staminaToConvert << " Stamina, "
         << strengthToConvert << " Strength, and "
         << wisdomToConvert << " Wisdom into "
         << pridePointsToAdd << " Pride Points!" << endl;
}

// Select an advisor
Advisor Game::selectAdvisor()
{
    displayAdvisors();

    int choice;
    cout << "Select an advisor (1-" << advisors.size() << "): ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > static_cast<int>(advisors.size()) || advisors[choice - 1].getIsSelected())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice. Please select an available advisor: ";
        cin >> choice;
    }

    advisors[choice - 1].setIsSelected(true);

    return advisors[choice - 1];
}

// Set up players
void Game::setupPlayers()
{
    for (int i = 0; i < 2; i++)
    {
        cout << "\n=== Player " << i + 1 << " Setup ===" << endl;

        // Get player name
        string playerName;
        cout << "Enter your name: ";
        cin >> playerName;

        Player player(playerName);

        // Character selection
        displayCharacters();

        int characterChoice;
        cout << "Select a character (1-" << characters.size() << "): ";
        cin >> characterChoice;

        while (cin.fail() || characterChoice < 1 || characterChoice > static_cast<int>(characters.size()) ||
               characters[characterChoice - 1].getIsSelected())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please select an available character: ";
            cin >> characterChoice;
        }

        // Mark character as selected
        characters[characterChoice - 1].setIsSelected(true);
        player.setCharacter(characters[characterChoice - 1]);

        // Path selection
        cout << "\nSelect your path:" << endl;
        cout << "1. Cub Training (-5000 Pride Points, +500 Stamina, +500 Strength, +1000 Wisdom, includes Advisor)" << endl;
        cout << "2. Straight to Pride Lands (+5000 Pride Points, +200 to all traits, no initial Advisor)" << endl;

        int pathChoice;
        cout << "Select a path (1-2): ";
        cin >> pathChoice;

        while (cin.fail() || pathChoice < 1 || pathChoice > 2)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please select a valid path (1 or 2): ";
            cin >> pathChoice;
        }

        // Set path and adjust traits
        player.setPathType(pathChoice - 1);
        gameBoard.setPlayerPath(i, pathChoice - 1);
        player.adjustTraits();

        // If Cub Training, select an advisor
        if (pathChoice == 1)
        {
            cout << "\nAs a Cub Training participant, you get to choose an advisor:" << endl;
            Advisor selectedAdvisor = selectAdvisor();
            player.setAdvisor(selectedAdvisor);
            cout << "You have chosen " << selectedAdvisor.getName() << " as your advisor!" << endl;
        }

        // Add player to vector
        players.push_back(player);
    }
}

// Play the game
void Game::playGame()
{
    cout << "\n=== Let the Lion King Game Begin! ===" << endl;

    // Game loop
    while (!gameOver)
    {
        Player currentPlayer = players[currentPlayerIndex];

        cout << "\n=== " << currentPlayer.getPlayerName() << "'s Turn ===" << endl;

        // Display current state
        gameBoard.displayBoard();

        // Show main menu
        handleMainMenu(currentPlayerIndex);

        // Roll spinner
        cout << "\nRolling the spinner..." << endl;
        int roll = rollSpinner();
        cout << "You rolled a " << roll << "!" << endl;

        // Move player
        currentPlayer.incrementMoves();
        bool reachedEnd = gameBoard.movePlayer(currentPlayerIndex, roll);

        // Get new position
        int newPosition = gameBoard.getPlayerPosition(currentPlayerIndex);
        currentPlayer.setPosition(newPosition);

        // Handle tile effect
        char tileColor = gameBoard.getTileColor(currentPlayer.getPathType(), newPosition);
        handleTileEffect(currentPlayerIndex, tileColor);

        // Save back changes to vector
        players[currentPlayerIndex] = currentPlayer;

        // Check if player reached Pride Rock
        if (reachedEnd)
        {
            cout << "\n"
                 << currentPlayer.getPlayerName() << " has reached Pride Rock!" << endl;

            // Check if all players reached Pride Rock
            bool allPlayersFinished = true;
            for (size_t i = 0; i < players.size(); i++)
            {
                if (gameBoard.getPlayerPosition(i) < 51)
                {
                    allPlayersFinished = false;
                    break;
                }
            }

            if (allPlayersFinished)
            {
                gameOver = true;
                determineWinner();
            }
        }

        // Switch to next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        cout << "\nPress Enter to continue to the next turn...";
        cin.ignore();
        cin.get();
    }
}

// Determine winner
void Game::determineWinner()
{
    int highestScore = -1;

    for (size_t i = 0; i < players.size(); i++)
    {
        int finalScore = players[i].calculateFinalScore();

        cout << "\n"
             << players[i].getPlayerName() << "'s Final Score: " << finalScore << endl;

        if (finalScore > highestScore)
        {
            highestScore = finalScore;
            winner = i;
        }
    }

    cout << "\n=== GAME OVER ===" << endl;
    cout << "The winner is " << players[winner].getPlayerName()
         << " playing as " << players[winner].getCharacter().getName()
         << " with " << highestScore << " Pride Points!" << endl;

    // Write game stats to file
    writeGameStats("game_stats.txt");
}

// Write game stats to file
bool Game::writeGameStats(string filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Could not open " << filename << " for writing." << endl;
        return false;
    }

    file << "=== Lion King Game Statistics ===" << endl
         << endl;

    file << "Winner: " << players[winner].getPlayerName()
         << " (" << players[winner].getCharacter().getName() << ")" << endl;
    file << "Final Score: " << players[winner].calculateFinalScore() << endl
         << endl;

    for (size_t i = 0; i < players.size(); i++)
    {
        file << "Player: " << players[i].getPlayerName() << endl;
        file << "Character: " << players[i].getCharacter().getName()
             << " (Age: " << players[i].getCharacter().getAge() << ")" << endl;
        file << "Path: " << (players[i].getPathType() == 0 ? "Cub Training" : "Straight to Pride Lands") << endl;
        file << "Moves Taken: " << players[i].getMovesTaken() << endl;

        if (players[i].getHasAdvisor())
        {
            file << "Advisor: " << players[i].getAdvisor().getName() << endl;
        }
        else
        {
            file << "Advisor: None" << endl;
        }

        file << "Final Stats:" << endl;
        file << "  Pride Points: " << players[i].getCharacter().getPridePoints() << endl;
        file << "  Stamina: " << players[i].getCharacter().getStamina() << endl;
        file << "  Strength: " << players[i].getCharacter().getStrength() << endl;
        file << "  Wisdom: " << players[i].getCharacter().getWisdom() << endl;
        file << "  Final Score: " << players[i].calculateFinalScore() << endl;
        file << endl;
    }

    file.close();
    cout << "Game statistics written to " << filename << endl;
    return true;
}