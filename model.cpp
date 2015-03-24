#include "model.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Constructor initializes the object
Model::Model(int h, int w) {
    ended = false;
    height = h;
    width = w;
    piece = (Tetrominoe)(time(0)%7);
    //pieces.push_back(piece);
    this->spawn(piece);
    // making a boolean grid to check where blocks are
    for (int i=0; i<=height; i++) {
        for (int j=0; j<width; j++) {
            if (i==height) {
                grid[i][j] = true;
            } else {
                grid[i][j] = false;
            }
        }
    }
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

bool Model::gameOver() {
    return false;
}

void Model::randomPiece() {
    piece = (Tetrominoe)(time(0)%7);
    //pieces.push_back(piece);
    this->spawn(piece);
}

void Model::spawn(Tetrominoe shape) {
    switch (shape) {
        case I:
            block1.x = 6;
            block2.x = 7;
            block3.x = 8;
            block4.x = 9;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y;
            block4.y = block1.y;
            break;
        case O:
            block1.x = 7;
            block2.x = 8;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        case T:
            block1.x = 7;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        case S:
            block1.x = 7;
            block2.x = 8;
            block3.x = 6;
            block4.x = 7;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        case Z:
            block1.x = 6;
            block2.x = 7;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        case J:
            block1.x = 6;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        case L:
            block1.x = 8;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
            break;
        default:
            break;
    }
}

void Model::build(Tetrominoe shape) {
    switch (shape) {
        case I:
            block2.y = block1.y;
            block3.y = block1.y;
            block4.y = block1.y;
            break;
        case O:
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case T:
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case S:
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case Z:
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case J:
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case L:
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        default:
            break;
    }
}

void Model::fall() {
    if (grid[block1.x][block1.y]) {
        // adjust boolean grid here
        
    } else {
        block1.y++;
        block2.y++;
        block3.y++;
        block4.y++;
    }
}

void Model::go(Direction d) {
    if (d == LEFT) {
        if (block1.x == 0 || block2.x == 0 || block3.x == 0 || block4.x == 0) {
        } else {
            block1.x--;
            block2.x--;
            block3.x--;
            block4.x--;
        }
    }
    if (d == RIGHT) {
        if (block1.x == width-1 || block2.x == width-1 || block3.x == width-1 || block4.x == width-1) {
        } else {
            block1.x++;
            block2.x++;
            block3.x++;
            block4.x++;
        }
    }
    if (d == DOWN) {
        if (block1.y >= 19 || block2.y >= 19 || block3.y >= 19 || block4.y >= 19) {
        } else {
            block1.y++;
            block2.y++;
            block3.y++;
            block4.y++;
        }
    }
}