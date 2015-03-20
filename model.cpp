#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model(int h, int w) {
    ended = false;
    height = h;
    width = w;
    // Seed random number generator with time
    srand(time(0));
    block.x = 16;       // for random placement: rand()%width;
    block.y = 0;        // for random placement: rand()%height;
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

bool Model::gameOver() {
    return false;
}

void Model::fall() {
    block.y++;
    if (block.y >= 47) {
        block.y = 47;
    }
}
