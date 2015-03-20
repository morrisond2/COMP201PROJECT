#ifndef _MODEL_H
#define _MODEL_H

enum Direction { UP, DOWN, LEFT, RIGHT };

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
    
    // A block
    Coordinate block;
    
    // Let blocks fall
    void fall();
    
private:
    int height, width;
    bool ended;
};

#endif