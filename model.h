#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>

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
    // Methods:
    // Is the game over?
    bool gameOver();
    // Let blocks fall
    void fall();
    // Go left or right
    void go(Direction d);
    // make Tetrominoe
    void spawn();
    // Build up the pile
    void build();
	// Get the current block
	Coordinate * block(Tetrominoe inputShape);
    // get the most right block of the falling Tetrominoe
	Coordinate right();
    // get the most left block of the falling Tetrominoe
    Coordinate left();
    // checks if any row is complete
    void checkRows();
    // if so, delete it and move everything down
    void deleteRow(int row);
    // Variables:
    // the current shape
	Tetrominoe shape;
    // Where is the falling shape?
    Coordinate location;
    // where is a particular block
    Coordinate blockLocation;
    // the grid of true/false (for collision detection)
    bool grid[21][10];
    // visible grid
    Tetrominoe colorGrid[20][10];
    // how many rows completed
    int rowCount;
    // actual score
    int score;
    // bonusss for more rows at once
    int multiplier;
    // use multiplier to
    void calculateScore();
    // where would it land?
    Coordinate shadeLocation();
    // space bar
    void instantFall();
    // next block
    Tetrominoe nextShape;
private:
    // size of the model
    int height, width;
    // gameover
    bool ended;
    // up down left or right
    Direction orientation;
    // left right issue
    bool dontmove;
};

#endif