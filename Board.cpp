// Hannah Davisson
#include "Board.h"
#include <cstdlib>
#include <ctime>

// Define color codes for display
#define RED "\033[48;2;230;10;10m"    // Graveyard
#define GREEN "\033[48;2;34;139;34m"  // Regular/Random Event
#define BLUE "\033[48;2;10;10;230m"   // Oasis
#define PINK "\033[48;2;255;105;180m" // Counseling
#define BROWN "\033[48;2;139;69;19m"  // Hyenas
#define PURPLE "\033[48;2;128;0;128m" // Challenge
#define ORANGE "\033[48;2;230;115;0m" // Pride Rock (Finish)
#define GREY "\033[48;2;128;128;128m" // Starting
#define RESET "\033[0m"

// Default constructor
Board::Board()
{
    _player_count = 2;

    // Initialize player positions
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize the board
    initializeBoard();
}

// Parameterized constructor
Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player positions
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize the board
    initializeBoard();
}

// Initialize the entire board
void Board::initializeBoard()
{
    // Seed random number generator
    srand(time(0));

    // Initialize each lane separately
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i);
    }
}

// Initialize tiles for one lane
void Board::initializeTiles(int lane_index)
{
    // Different distribution rules for each path type
    // 0 = Cub Training (more beneficial tiles early on)
    // 1 = Straight to Pride Lands (more challenges early on)

    int specialTileCount = 0;
    int maxSpecialTiles = 20; // Minimum required

    // Set the first and last tile for both lanes
    _tiles[lane_index][0].color = 'Y';               // Grey (Start)
    _tiles[lane_index][_BOARD_SIZE - 1].color = 'O'; // Orange (Finish)

    // Randomize tiles for the rest of the lane
    for (int i = 1; i < _BOARD_SIZE - 1; i++)
    {
        // Determine if this should be a special tile
        bool makeSpecialTile = (specialTileCount < maxSpecialTiles) &&
                               (rand() % (_BOARD_SIZE - i) < (maxSpecialTiles - specialTileCount));

        if (makeSpecialTile)
        {
            // This will be a special tile
            specialTileCount++;

            // Determine which special tile based on the lane and position
            int tileChoice;

            if (lane_index == 0)
            { // Cub Training
                // More beneficial tiles in early positions
                if (i < _BOARD_SIZE / 3)
                {
                    // Early positions: more likely to get Oasis or Counseling
                    tileChoice = rand() % 10;
                    if (tileChoice < 5)
                    {                                      // 50% chance for Oasis
                        _tiles[lane_index][i].color = 'B'; // Blue (Oasis)
                    }
                    else if (tileChoice < 9)
                    {                                      // 40% chance for Counseling
                        _tiles[lane_index][i].color = 'P'; // Pink (Counseling)
                    }
                    else
                    {                                      // 10% chance for Challenge
                        _tiles[lane_index][i].color = 'U'; // Purple (Challenge)
                    }
                }
                else
                {
                    // Later positions: more variety
                    tileChoice = rand() % 5;
                    if (tileChoice == 0)
                    {
                        _tiles[lane_index][i].color = 'B'; // Blue (Oasis)
                    }
                    else if (tileChoice == 1)
                    {
                        _tiles[lane_index][i].color = 'P'; // Pink (Counseling)
                    }
                    else if (tileChoice == 2)
                    {
                        _tiles[lane_index][i].color = 'R'; // Red (Graveyard)
                    }
                    else if (tileChoice == 3)
                    {
                        _tiles[lane_index][i].color = 'N'; // Brown (Hyenas)
                    }
                    else
                    {
                        _tiles[lane_index][i].color = 'U'; // Purple (Challenge)
                    }
                }
            }
            else
            { // Straight to Pride Lands
                // More challenging tiles in early positions
                if (i < _BOARD_SIZE / 3)
                {
                    // Early positions: more likely to get Graveyard or Hyenas
                    tileChoice = rand() % 10;
                    if (tileChoice < 4)
                    {                                      // 40% chance for Graveyard
                        _tiles[lane_index][i].color = 'R'; // Red (Graveyard)
                    }
                    else if (tileChoice < 7)
                    {                                      // 30% chance for Hyenas
                        _tiles[lane_index][i].color = 'N'; // Brown (Hyenas)
                    }
                    else if (tileChoice < 9)
                    {                                      // 20% chance for Challenge
                        _tiles[lane_index][i].color = 'U'; // Purple (Challenge)
                    }
                    else
                    {                                      // 10% chance for Counseling
                        _tiles[lane_index][i].color = 'P'; // Pink (Counseling)
                    }
                }
                else
                {
                    // Later positions: more variety
                    tileChoice = rand() % 5;
                    if (tileChoice == 0)
                    {
                        _tiles[lane_index][i].color = 'B'; // Blue (Oasis)
                    }
                    else if (tileChoice == 1)
                    {
                        _tiles[lane_index][i].color = 'P'; // Pink (Counseling)
                    }
                    else if (tileChoice == 2)
                    {
                        _tiles[lane_index][i].color = 'R'; // Red (Graveyard)
                    }
                    else if (tileChoice == 3)
                    {
                        _tiles[lane_index][i].color = 'N'; // Brown (Hyenas)
                    }
                    else
                    {
                        _tiles[lane_index][i].color = 'U'; // Purple (Challenge)
                    }
                }
            }
        }
        else
        {
            // This will be a regular (green) tile
            _tiles[lane_index][i].color = 'G'; // Green (Regular)
        }
    }

    // If we don't have enough special tiles, replace some regular tiles
    while (specialTileCount < maxSpecialTiles)
    {
        int pos = 1 + rand() % (_BOARD_SIZE - 2); // Random position (excluding start and finish)

        if (_tiles[lane_index][pos].color == 'G')
        {
            // This is a regular tile, convert it to a special tile
            int tileChoice = rand() % 5;
            if (tileChoice == 0)
            {
                _tiles[lane_index][pos].color = 'B'; // Blue (Oasis)
            }
            else if (tileChoice == 1)
            {
                _tiles[lane_index][pos].color = 'P'; // Pink (Counseling)
            }
            else if (tileChoice == 2)
            {
                _tiles[lane_index][pos].color = 'R'; // Red (Graveyard)
            }
            else if (tileChoice == 3)
            {
                _tiles[lane_index][pos].color = 'N'; // Brown (Hyenas)
            }
            else
            {
                _tiles[lane_index][pos].color = 'U'; // Purple (Challenge)
            }

            specialTileCount++;
        }
    }
}

// Check if a player is on a specific tile
bool Board::isPlayerOnTile(int player_index, int pos)
{
    return (_player_position[player_index] == pos);
}

// Set the player's path type
void Board::setPlayerPath(int player_index, int path_type)
{
    if (player_index >= 0 && player_index < _MAX_PLAYERS)
    {
        _player_path[player_index] = path_type; // 0 = cub training, 1 = straight to pridelands
    }
}

// Display a single tile
void Board::displayTile(int lane_index, int pos)
{
    string color = "";
    string displayContent = " ";

    // Set tile background color
    switch (_tiles[lane_index][pos].color)
    {
    case 'Y':
        color = GREY;
        break;
    case 'G':
        color = GREEN;
        break;
    case 'B':
        color = BLUE;
        break;
    case 'P':
        color = PINK;
        break;
    case 'R':
        color = RED;
        break;
    case 'N':
        color = BROWN;
        break;
    case 'U':
        color = PURPLE;
        break;
    case 'O':
        color = ORANGE;
        break;
    }

    // Check if players are on this tile
    bool player1Here = (_player_position[0] == pos && _player_path[0] == lane_index);
    bool player2Here = (_player_position[1] == pos && _player_path[1] == lane_index);

    if (player1Here && player2Here)
    {
        displayContent = "1&2";
    }
    else if (player1Here)
    {
        displayContent = " 1 ";
    }
    else if (player2Here)
    {
        displayContent = " 2 ";
    }

    // Format to exactly 3 characters inside the tile
    if (displayContent.length() == 1)
        displayContent = " " + displayContent + " ";
    if (displayContent.length() == 2)
        displayContent += " ";
    if (displayContent.length() > 3)
        displayContent = displayContent.substr(0, 3);

    cout << color << "|" << displayContent << "|" << RESET;
}

void Board::displayTrack(int lane_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(lane_index, i);
    }
    cout << endl;
}

// Display the entire board
void Board::displayBoard()
{
    cout << "\nCub Training Path:" << endl;
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(0, i); // lane 0
    }
    cout << endl
         << endl;

    cout << "Straight to Pride Lands Path:" << endl;
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(1, i); // lane 1
    }
    cout << endl;
}

// Get the color of a tile at a specific position
char Board::getTileColor(int player_index, int position)
{
    if (position >= 0 && position < _BOARD_SIZE)
    {
        return _tiles[player_index][position].color;
    }
    return ' ';
}

// Move a player
bool Board::movePlayer(int player_index, int spaces)
{
    _player_position[player_index] += spaces;

    // Check if player reached the end
    if (_player_position[player_index] >= _BOARD_SIZE - 1)
    {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true; // Reached Pride Rock
    }

    return false; // Game continues
}

// Get a player's position
int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index < _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}