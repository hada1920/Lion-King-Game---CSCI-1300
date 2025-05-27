// Hannah Davisson
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
using namespace std;

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE]; // 2 lanes, 52 tiles per lane
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int _player_path[_MAX_PLAYERS];

    // Private helper methods
    void displayTile(int player_index, int pos);
    void initializeTiles(int lane_index);
    bool isPlayerOnTile(int player_index, int pos);

public:
    // Constructors
    Board();
    Board(int player_count);

    // Display methods
    void displayTrack(int player_index);
    void displayBoard();

    // Board initialization
    void initializeBoard();

    // Game mechanics
    char getTileColor(int player_index, int position);

    // Player movement
    bool movePlayer(int player_index, int spaces);
    int getPlayerPosition(int player_index) const;
    void setPlayerPath(int player_index, int path_type);
};

#endif