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
    shape = (Tetrominoe)(time(0)%7);
	orientation = DOWN;
	location.x = 5;
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
}

// This should build up the pile structure (and do collision detection)
void Model::build() {
    
    Coordinate * blck = block();
    for (int i =  0; i < 4; i++) {
        grid[blck[i].y+location.y][blck[i].x+location.x] = true;
        // also make a pile structure on the screen here of course
        
    }
    
    /*
    for (int i=0; i<=height; i++) {
        for (int j=0; j<width; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
    
    spawn();
}

void Model::fall() {
    Coordinate * blck = block();
    
    for (int i = 0; i < 4; i++) {
        if (grid[blck[i].y+location.y + 1][blck[i].x+location.x]) {
            // yay collision
            build();
            return;
        }
    }
    location.y++;
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