#ifndef _MODEL_H
#define _MODEL_H

#include <vector>

using namespace std;

enum Direction { UP, LEFT, DOWN, RIGHT };

enum Tetrominoe {
    // see http://tetris.wikia.com/wiki/Tetromino for the names
    I, O, T, S, Z, J, L, D
    // the D is not a Tetrominoe shape,
    // it's used for a default in the colorGrid
};

typedef struct {
    int x;
    int y;
} Coordinate;



// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model(int h, int w);
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
    
    // TODO: Put your stuff here

	// Where is the falling block?
	Coordinate location;
    // Let blocks fall
    void fall();
    // Go left or right
    void go(Direction d);
    // the grid of true/false (for collision detection)
    bool grid[21][10];
    // visible grid
    Tetrominoe colorGrid[20][10];
    // make Tetrominoe
    void spawn();
    // Build up the pile
    void build();
	// Get the current block
	Coordinate * block();
	int right();
	Tetrominoe shape;
private:
    int height, width;
    bool ended;
    Direction orientation;
};

#endif