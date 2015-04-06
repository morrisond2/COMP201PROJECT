#include "controller.h"
#include <map>

using namespace std;

Controller::Controller() {
    model = new Model(20,10);
    view = new View("Tetris", 1024, 768);
    scoresfile.open("highscores.txt", ios::app);
    fileFailedOpen = false;
    paused = false;
    if (scoresfile.fail()) {
        cout << "Outputfile failed to open." << endl;
        fileFailedOpen = true;
    }
    // Decrease the update time interval to make game faster
    milliSeconds = 200;
}

Controller::~Controller() {
    delete model;
    delete view;
    scoresfile.close();
}
/*
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_UP] = UP;
    direction[SDLK_DOWN] = DOWN;
    direction[SDLK_LEFT] = LEFT;
    direction[SDLK_RIGHT] = RIGHT;

    while(!model->gameOver()) {
        if (paused) {
            view->showPause(model);
            if (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        return;
                    case SDL_KEYDOWN:
                        switch(e.key.keysym.sym) {
                            case SDLK_p:
                                paused = false;
                                break;
                        }
                }
            }
        } else {
            currentTime = SDL_GetTicks();
            // Do stuff here to animate as necessary
            view->show(model);
            if (currentTime > lastTime + milliSeconds) {
                model->fall();
                lastTime = currentTime;
            }
            if (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        model->go(direction[e.key.keysym.sym]);
                        break;
                    case SDLK_p:
                        paused = true;
                        break;
                    default:
                        break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    break;
                }
            }
        }
    }
    if (!fileFailedOpen) {
        scoresfile << endl << "Rows completed: " << model->score << "\t"
        << "(milli seconds between Tetrominoes: " << milliSeconds << ")" << endl;
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(1000);
}
