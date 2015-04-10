
// Tetris game

#define SDL_MAIN_HANDLED

#ifdef __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#endif

#ifdef _WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "model.h"
#include <map>
#include <string>

#ifndef _VIEW_H
#define _VIEW_H

// Show (output) the state of the model
class View {
public:
    View(std::string title, int width, int height);
    ~View();
    // Print out the visible stuff in the grid
    void show(Model * model);
    // Print out a pause screen
    void showPause(Model * model);
    // Print out a start screen before the game begins
    void showStartScreen(Model* model);
private:
	Mix_Music* music = NULL;
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* textPaused;
    SDL_Surface* text2;
    string scoreString;
    bool fail;
    SDL_Surface* load(std::string path);
    TTF_Font * font;
    SDL_Surface* BG = NULL;
//    Mix_Chunk * food;
    SDL_Surface* blockIMG = NULL;
    SDL_Surface* nextBlockIMG = NULL;
    SDL_Surface* IblockIMG = NULL;
    SDL_Surface* OblockIMG = NULL;
    SDL_Surface* TblockIMG = NULL;
    SDL_Surface* SblockIMG = NULL;
    SDL_Surface* ZblockIMG = NULL;
    SDL_Surface* JblockIMG = NULL;
    SDL_Surface* LblockIMG = NULL;
};
#endif