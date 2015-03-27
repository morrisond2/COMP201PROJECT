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
    shape = (Tetrominoe)(time(0)%7);
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
	spawn();
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

bool Model::gameOver() {
    return false;
}

void Model::spawn() {
// Create a new piece
    shape = (Tetrominoe)(0) /*(time(0)%7)*/;
	orientation = UP;
	location.x = 5;
	location.y = 0;
}

Coordinate * Model::block() {
	// All blocks by orientation and shape
	// block[orientation][shape]
	// Treat as a constant
	static Coordinate blocks[4][7][4] = {
	{ // UP
		{ {0, 0}, {0, 1}, {0, 2}, {0, 3} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 0}, {1, 0}, {1, 1}, {2, 0} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {0, 0}, {1, 0}, {2, 0} }, // J
		{ {0, 0}, {1, 0}, {2, 0}, {2, 1} }, // L
	},
	
	{ // LEFT
		{ {0, 1}, {0, 1}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 0}, {1, 1}, {1, 2} }, // T
		{ {0, 2}, {0, 1}, {1, 1}, {1, 0} }, // S
		{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }, // Z
		{ {0, 0}, {1, 0}, {1, 1}, {1, 2} }, // J
		{ {0, 2}, {0, 1}, {0, 0}, {1, 0} }, // L
	},
	
	{ // DOWN
		{ {0, 0}, {0, 1}, {0, 2}, {0, 3} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 1}, {1, 1}, {1, 0}, {2, 1} }, // T
		{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
		{ {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
		{ {0, 1}, {1, 1}, {2, 1}, {2, 0} }, // J
		{ {0, 0}, {0, 1}, {1, 1}, {2, 1} }, // L
	},
	
	{ // RIGHT
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }, // I
		{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, // O
		{ {0, 2}, {0, 1}, {1, 1}, {0, 0} }, // T
		{ {0, 2}, {0, 1}, {1, 1}, {1, 0} }, // S
		{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }, // Z
		{ {1, 2}, {0, 2}, {0, 1}, {0, 0} }, // J
		{ {0, 2}, {1, 2}, {1, 1}, {1, 0} }, // L
	},	
	
};

    // Building blocks for Tetrominoes
	return blocks[orientation][shape];
}

// This should build up the pile structure (and do collision detection)
void Model::build() {
	spawn();
}

void Model::fall() {
	if (location.y < 20) {
		location.y = 6;
		cout << location.y << ", " <<  orientation << endl;
	} else {
        build();
	}
}

int Model::right() {
	int result = 0;
	Coordinate * blck = block();
	for (int i =  0; i < 4; i++) {
		if (blck[i].x + location.x > result) {
			result = (blck[i].x + location.x);
		}
	}
	return result;
}

void Model::go(Direction d) {
    if (d == LEFT) {
        if (location.x > 0) {
            location.x--;
        }
    }
    if (d == RIGHT) {
        if (right() < 9) {
            location.x++;
        }
    }
    if (d == DOWN) {
		fall();
    }
	if (d == UP) {
		orientation = (Direction)((((int)orientation) + 1) % 4);
	}
}