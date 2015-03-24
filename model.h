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

typedef struct {
    Coordinate block1, block2, block3, block4;
} Shape;

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
    
    // Building blocks for Tetrominoes
    Coordinate block[4];
    Shape tetro;
    // Let blocks fall
    void fall();
    // Go left or right
    void go(Direction d);
    // the falling shape
    vector<Shape> pieces;
    // the grid of blocks
    bool ** grid;
    // make Tetrominoe
    void spawn(Tetrominoe shape);
    // keep Tetrominoe in shape
    void build(Tetrominoe shape);
    // chose random Tetrominoe
    void randomPiece();
    
private:
    int height, width;
    int randomNum;
    bool ended;
    Tetrominoe piece;
};

#endif