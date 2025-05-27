// Hannah Davisson
#ifndef TILE_H
#define TILE_H

// Tile struct to represent each tile on the board
struct Tile {
    char color; // Color code representing tile type:
    // 'Y' - Grey (Starting Tile)
    // 'G' - Green (Regular/Random Event Tile)
    // 'B' - Blue (Oasis Tile)
    // 'P' - Pink (Counseling Tile)
    // 'R' - Red (Graveyard Tile)
    // 'N' - Brown (Hyenas Tile)
    // 'U' - Purple (Challenge Tile)
    // 'O' - Orange (Pride Rock/Finish Tile)
};

#endif