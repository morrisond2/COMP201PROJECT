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
    music = Mix_LoadMUS("assets/TetrisTheme.mp3");
    if (music != NULL) {
       Mix_PlayMusic( music, -1 );
    }
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
    SDL_Rect one;
    one.x=74;
    one.y=98;
    one.w=204;
    one.h=154;
    SDL_Rect two;
    two.x=350;
    two.y=30;
    two.w=324;
    two.h=708;
    SDL_Rect three;
    three.x=746;
    three.y=98;
    three.w=204;
    three.h=404;
    SDL_Rect onet;
    onet.x=76;
    onet.y=100;
    onet.w=200;
    onet.h=150;
    SDL_Rect twot;
    twot.x=352;
    twot.y=32;
    twot.w=320;
    twot.h=704;
    SDL_Rect threet;
    threet.x=748;
    threet.y=100;
    threet.w=200;
    threet.h=400;
    
    int d=352;
    SDL_Rect bottom[10];
    for (int i=0;i<10;i++)
    {
        bottom[i].x=d+32;
        bottom[i].y=32;
        bottom[i].w=1;
        bottom[i].h=704;
        d=d+32;
        
    }
    
    int b=32;
    SDL_Rect side[22];
    for(int i = 0; i < 22; i++)
    {
        side[i].x=352;
        side[i].y=b+32;
        side[i].w=320;
        side[i].h=1;
        b=b+32;
    }
    
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
   
    SDL_FillRect(screen, &one, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &two, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &three, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &onet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &twot, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &threet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRects(screen, bottom, 10, SDL_MapRGB(screen->format, 64,64,64));
    SDL_FillRects(screen, side, 22, SDL_MapRGB(screen->format, 64,64,64));

    // Probably call SDL_FillRect or SDL_BlitSurface a bunch here :-)
    
    // making four 32 by 32 pixel blocks
    SDL_Rect dest[4];
	Coordinate * block = model->block();
	for (int i = 0; i < 4; i++) {
		dest[i].w = 32;
		dest[i].h = 32;
		dest[i].x = (block[i].x + model->location.x) * 32;
		dest[i].y = (block[i].y + model->location.y) * 32;
		SDL_FillRect(screen, &dest[i], SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
	}

    SDL_UpdateWindowSurface(window);
   
}
