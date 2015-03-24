#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }
    // Load assets
//    snake = load("assets/snake.png");
//    music = Mix_LoadMUS("assets/2Inventions_-_Johaness_Gilther_-_Don_t_leave_me.mp3");
//    if (music != NULL) {
//       Mix_PlayMusic( music, -1 );
//    }
//    food = Mix_LoadWAV("assets/yummy.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 28 );

}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    // Probably call SDL_FillRect or SDL_BlitSurface a bunch here :-)
    
    // making four 32 by 32 pixel blocks
    SDL_Rect dest1, dest2, dest3, dest4;
    dest1.w = 32;
    dest1.h = 32;
    dest2.w = 32;
    dest2.h = 32;
    dest3.w = 32;
    dest3.h = 32;
    dest4.w = 32;
    dest4.h = 32;
    // block locations
    dest1.x = 352 + model->block1.x * 32;
    dest1.y = model->block1.y * 32;
    dest2.x = 352 + model->block2.x * 32;
    dest2.y = model->block2.y * 32;
    dest3.x = 352 + model->block3.x * 32;
    dest3.y = model->block3.y * 32;
    dest4.x = 352 + model->block4.x * 32;
    dest4.y = model->block4.y * 32;
    // block color
    SDL_FillRect(screen, &dest1, SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
    SDL_FillRect(screen, &dest2, SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
    SDL_FillRect(screen, &dest3, SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
    SDL_FillRect(screen, &dest4, SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
    
    // making a line for the play space
    SDL_Rect line1, line2, line3;
    line1.w = 8;
    line1.h = 32*20;
    line2.w = 8;
    line2.h = 32*20;
    line3.w = 32*10+16;
    line3.h = 8;
    line1.x = 352-8;
    line1.y = 0;
    line2.x = 352+32*10;
    line2.y = 0;
    line3.x = 352-8;
    line3.y = 32*20;
    SDL_FillRect(screen, &line1, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));
    SDL_FillRect(screen, &line2, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));
    SDL_FillRect(screen, &line3, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));
    

    SDL_UpdateWindowSurface(window);
}
