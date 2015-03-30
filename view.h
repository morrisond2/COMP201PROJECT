
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
private:
	Mix_Music* music = NULL;
    SDL_Window* window;
    SDL_Surface* screen;
    bool fail;
    SDL_Surface* load(std::string path);
//    SDL_Surface* text;
//    Mix_Chunk * food;
    TTF_Font * font;
	SDL_Surface* blockIMG = NULL;
};
#endif