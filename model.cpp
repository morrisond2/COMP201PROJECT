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

// Create a new piece
    shape = (Tetrominoe)(time(0)%7);
	orientation = DOWN;
	location.x = 7;
	location.y = 0;
}

Coordinate * Model::block() {
	// All blocks by orientation and shape
	// block[orientation][shape]
	// Treat as a constant
	static Coordinate blocks[4][7][4] = {
	{ // UP
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 1}, {2, 1}, {1, 0} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {0, 0}, {1, 0}, {2, 0} }, // J
		{ {0, 0}, {1, 0}, {2, 0}, {2, 1} },
	},
	{ // DOWN
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 1}, {2, 1}, {1, 0} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {0, 0}, {1, 0}, {2, 0} }, // J
		{ {0, 0}, {1, 0}, {2, 0}, {2, 1} },
	},
	{ // LEFT
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 1}, {2, 1}, {1, 0} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {0, 0}, {1, 0}, {2, 0} }, // J
		{ {0, 0}, {1, 0}, {2, 0}, {2, 1} },
	},
	{ // RIGHT
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 1}, {2, 1}, {1, 0} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {0, 0}, {1, 0}, {2, 0} }, // J
		{ {0, 0}, {1, 0}, {2, 0}, {2, 1} },
	},
};

    // Building blocks for Tetrominoes
	return blocks[orientation][shape];
            break;
            break;
            break;
}

// This should build up the pile structure (and do collision detection)
void Model::build() {
	/*
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
	*/
}

void Model::fall() {
	if (location.y < 22) {
	location.y++;
	cout << location.y << endl;
	} else {
        build();
	}
}

void Model::go(Direction d) {
    if (d == LEFT) {
        if (location.x > 0) {
            location.x--;
        }
    }
    if (d == RIGHT) {
        if (location.x < 10) {
            location.x++;
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
	if (d == UP) {
		orientation = (Direction)((((int)orientation) + 1) % 4);
	}
}