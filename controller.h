#include "model.h"
#include "view.h"
#include <fstream>
#include <iostream>

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

// Handle input
class Controller {
public:
    Controller();
    ~Controller();
    // Event loop
    void loop();
private:
    Model * model;
    View * view;
    // file for highscores
    ofstream scoresfile;
    bool fileFailedOpen;
    int milliSeconds;
    bool paused;
    bool started;
};
#endif