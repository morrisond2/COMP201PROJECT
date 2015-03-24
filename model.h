#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

enum Tetrominoe {
    // see http://tetris.wikia.com/wiki/Tetromino for the names
    I=0, O, T, S, Z, J, L
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

	// The way the block is facing
	Direction orientation;
	// Where is the falling block?
	Coordinate location;
    // Let blocks fall
    void fall();
    // Go left or right
    void go(Direction d);
    // the grid of blocks
    bool ** grid;
    // make Tetrominoe
    void spawn();
    // Build up the pile
    void build();
	// Get the current block
	Coordinate * block();
private:
    int height, width;
    int randomNum;
    bool ended;
    Tetrominoe shape;
};

#endif