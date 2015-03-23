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
    // Seed random number generator with time
    srand(time(0));
    randomNum = rand()%7;
    //cout << randomNum << endl;
    piece = Tetrominoe(randomNum);
    //pieces.push_back(piece);
    this->spawn(piece);
    // making a boolean grid to check where blocks are
    grid = new bool*[height+1];
    for (int i=0; i <= height; i++) {
        grid[i] = new bool[width];
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
    for (int i = 0; i < height; i++) {
        delete grid[i];
    }
    delete grid;
}

bool Model::gameOver() {
    return false;
}

void Model::randomPiece() {
    randomNum = rand()%7;
    piece = Tetrominoe(randomNum);
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
        case T:
            block1.x = 7;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case S:
            block1.x = 7;
            block2.x = 8;
            block3.x = 6;
            block4.x = 7;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case Z:
            block1.x = 6;
            block2.x = 7;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case J:
            block1.x = 6;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
        case L:
            block1.x = 8;
            block2.x = 6;
            block3.x = 7;
            block4.x = 8;
            block1.y = 0;
            block2.y = block1.y+1;
            block3.y = block1.y+1;
            block4.y = block1.y+1;
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
    block1.y++;
    block2.y++;
    block3.y++;
    block4.y++;
    if (block1.y >= 22) {
        block1.y = 22;
        build(piece);
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
        if (block1.x == 15 || block2.x == 15 || block3.x == 15 || block4.x == 15) {
        } else {
            block1.x++;
            block2.x++;
            block3.x++;
            block4.x++;
        }
    }
}