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
            block[0].x = 6;
            block[1].x = 7;
            block[2].x = 8;
            block[3].x = 9;
            block[0].y = 0;
            block[1].y = block[0].y;
            block[2].y = block[0].y;
            block[3].y = block[0].y;
            break;
        case O:
            block[0].x = 7;
            block[1].x = 8;
            block[2].x = 7;
            block[3].x = 8;
            block[0].y = 0;
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case T:
            block[0].x = 7;
            block[0].y = 0;
			
            block[1].x = 6;
            block[1].y = block[0].y+1;
			
            block[2].x = 7;
            block[2].y = block[0].y+1;
			
            block[3].x = 8;
            block[3].y = block[0].y+1;
        case S:
            block[0].x = 7;
            block[1].x = 8;
            block[2].x = 6;
            block[3].x = 7;
            block[0].y = 0;
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case Z:
            block[0].x = 6;
            block[1].x = 7;
            block[2].x = 7;
            block[3].x = 8;
            block[0].y = 0;
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case J:
            block[0].x = 6;
            block[1].x = 6;
            block[2].x = 7;
            block[3].x = 8;
            block[0].y = 0;
            block[1].y = block[0].y+1;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case L:
            block[0].x = 8;
            block[1].x = 6;
            block[2].x = 7;
            block[3].x = 8;
            block[0].y = 0;
            block[1].y = block[0].y+1;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        default:
            break;
    }
}

void Model::build(Tetrominoe shape) {
    switch (shape) {
        case I:
            block[1].y = block[0].y;
            block[2].y = block[0].y;
            block[3].y = block[0].y;
            break;
        case O:
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case T:
            block[1].y = block[0].y+1;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case S:
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case Z:
            block[1].y = block[0].y;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case J:
            block[1].y = block[0].y+1;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        case L:
            block[1].y = block[0].y+1;
            block[2].y = block[0].y+1;
            block[3].y = block[0].y+1;
        default:
            break;
    }
}

void Model::fall() {
    block[0].y++;
    block[1].y++;
    block[2].y++;
    block[3].y++;
    if (block[0].y >= 22) {
        block[0].y = 22;
        build(piece);
    }
}

void Model::go(Direction d) {
    if (d == LEFT) {
        if (block[0].x == 0 || block[1].x == 0 || block[2].x == 0 || block[3].x == 0) {
        } else {
            block[0].x--;
            block[1].x--;
            block[2].x--;
            block[3].x--;
        }
    }
    if (d == RIGHT) {
        if (block[0].x == 15 || block[1].x == 15 || block[2].x == 15 || block[3].x == 15) {
        } else {
            block[0].x++;
            block[1].x++;
            block[2].x++;
            block[3].x++;
        }
    }
	if (d == UP)	{
			
		}
}