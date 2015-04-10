
// Tetris game

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
    
    BG = load("assets/TetrisBackground.jpeg");
    IblockIMG = load("assets/I.png");
    OblockIMG = load("assets/O.png");
    TblockIMG = load("assets/T.png");
    SblockIMG = load("assets/S.png");
    ZblockIMG = load("assets/Z.png");
    JblockIMG = load("assets/J.png");
    LblockIMG = load("assets/L.png");

}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_FreeSurface(textPaused);
    SDL_FreeSurface(text2);
    
    SDL_FreeSurface(BG);
    SDL_FreeSurface(IblockIMG);
    SDL_FreeSurface(OblockIMG);
    SDL_FreeSurface(TblockIMG);
    SDL_FreeSurface(SblockIMG);
    SDL_FreeSurface(ZblockIMG);
    SDL_FreeSurface(JblockIMG);
    SDL_FreeSurface(LblockIMG);
}


// Load an image from a file to a SDL_Surface
SDL_Surface* View::load(string path) {
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return optimizedSurface;
}

void View::showPause(Model * model) {
    // the three nice rectangles Mario made:
    SDL_Rect one;
    one.x=74;
    one.y=98;
    one.w=204;
    one.h=154;
    SDL_Rect three;
    three.x=746;
    three.y=98;
    three.w=204;
    three.h=154;
    SDL_Rect onet;
    onet.x=76;
    onet.y=100;
    onet.w=200;
    onet.h=150;
    SDL_Rect threet;
    threet.x=748;
    threet.y=100;
    threet.w=200;
    threet.h=150;
    
    SDL_Rect thinhorizontaltop;
    thinhorizontaltop.x = 350;
    thinhorizontaltop.y = 30;
    thinhorizontaltop.w = 324;
    thinhorizontaltop.h = 2;
    SDL_Rect thinhorizontalbottom;
    thinhorizontalbottom.x = 350;
    thinhorizontalbottom.y = 672;
    thinhorizontalbottom.w = 324;
    thinhorizontalbottom.h = 2;
    SDL_Rect thinvertical1;
    thinvertical1.x = 350;
    thinvertical1.y = 32;
    thinvertical1.h = 640;
    thinvertical1.w = 2;
    SDL_Rect thinvertical2;
    thinvertical2.x = 672;
    thinvertical2.y = 32;
    thinvertical2.h = 640;
    thinvertical2.w = 2;
    
    // can't see anything when paused
    SDL_Rect pauseRectangle;
    pauseRectangle.x = 352;
    pauseRectangle.y = 32;
    pauseRectangle.h = 640;
    pauseRectangle.w = 320;
    
    // the thin vertical lines in the Tetris grid:
    int d=352;
    SDL_Rect bottom[9];
    for (int i=0;i<9;i++)
    {
        bottom[i].x=d+32;
        bottom[i].y=32;
        bottom[i].w=1;
        bottom[i].h=704-64;
        d=d+32;
    }
    // the thin horizontal lines in the Tetris grid:
    int b=32;
    SDL_Rect side[20];
    for(int i = 0; i < 20; i++)
    {
        side[i].x=352;
        side[i].y=b+32;
        side[i].w=320;
        side[i].h=1;
        b=b+32;
    }
    
    // black background screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
    SDL_BlitSurface(BG,NULL,screen, NULL);
    
    // rest of the background rectangle stuff
    SDL_FillRect(screen, &one, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &three, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &onet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &threet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &thinhorizontaltop, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinhorizontalbottom, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinvertical1, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinvertical2, SDL_MapRGB(screen->format, 0,0,255));

    SDL_FillRect(screen, &pauseRectangle, SDL_MapRGB(screen->format, 255,255,255));
    
    SDL_FillRects(screen, bottom, 9, SDL_MapRGB(screen->format, 64,64,64));
    SDL_FillRects(screen, side, 20, SDL_MapRGB(screen->format, 64,64,64));
    
    // Choosing correct image based on block spawned
    switch (model->shape) {
        case I:
            blockIMG = IblockIMG;
            break;
        case O:
            blockIMG = OblockIMG;
            break;
        case T:
            blockIMG = TblockIMG;
            break;
        case S:
            blockIMG = SblockIMG;
            break;
        case Z:
            blockIMG = ZblockIMG;
            break;
        case J:
            blockIMG = JblockIMG;
            break;
        case L:
            blockIMG = LblockIMG;
            break;
        case D:
            break;
        default:
            break;
    }
    // making four 32 by 32 pixel blocks
    SDL_Rect dest[4];
    Coordinate * block = model->block();
    for (int i = 0; i < 4; i++) {
        dest[i].w = 32;
        dest[i].h = 32;
        dest[i].x = 352+ (block[i].x + model->location.x) * 32;
        dest[i].y = 32 + (block[i].y + model->location.y) * 32;
        SDL_FillRect(screen, &dest[i], SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
    }
    //SDL_BlitSurface calls for block images
    for (int x = 0; x < 4; x++) {
        SDL_BlitSurface(blockIMG, NULL, screen, &dest[x]);
    }
    
    SDL_Color textColor = { 0, 0, 0 };
    textPaused = TTF_RenderText_Solid( font, "Paused", textColor );
    SDL_Rect textDest;
    textDest.x = 352+110;
    textDest.y = 32+300;
    SDL_BlitSurface( textPaused, NULL, screen, &textDest );
    
    SDL_Color textColor2 = { 255, 255, 255 };
    text2 = TTF_RenderText_Solid( font, "Press P to continue", textColor2 );
    SDL_Rect textDest2;
    textDest2.x = 750;
    textDest2.y = 400;
    SDL_BlitSurface( text2, NULL, screen, &textDest2 );
    
    scoreString = to_string(model->score);
    SDL_Color textColorScore = { 255, 255, 255 };
    text2 = TTF_RenderText_Solid( font, scoreString.c_str(), textColorScore );
    SDL_Rect textDestScore;
    textDestScore.x = 100;
    textDestScore.y = 150;
    SDL_BlitSurface( text2, NULL, screen, &textDestScore );
   
    SDL_UpdateWindowSurface(window);
}

void View::show(Model * model) {
    
    // the three nice rectangles Mario made:
    SDL_Rect one;
    one.x=74;
    one.y=98;
    one.w=204;
    one.h=154;
    SDL_Rect three;
    three.x=746;
    three.y=98;
    three.w=204;
    three.h=154;
    SDL_Rect onet;
    onet.x=76;
    onet.y=100;
    onet.w=200;
    onet.h=150;
    SDL_Rect threet;
    threet.x=748;
    threet.y=100;
    threet.w=200;
    threet.h=150;
    
    SDL_Rect thinhorizontaltop;
    thinhorizontaltop.x = 350;
    thinhorizontaltop.y = 30;
    thinhorizontaltop.w = 324;
    thinhorizontaltop.h = 2;
    SDL_Rect thinhorizontalbottom;
    thinhorizontalbottom.x = 350;
    thinhorizontalbottom.y = 672;
    thinhorizontalbottom.w = 324;
    thinhorizontalbottom.h = 2;
    SDL_Rect thinvertical1;
    thinvertical1.x = 350;
    thinvertical1.y = 32;
    thinvertical1.h = 640;
    thinvertical1.w = 2;
    SDL_Rect thinvertical2;
    thinvertical2.x = 672;
    thinvertical2.y = 32;
    thinvertical2.h = 640;
    thinvertical2.w = 2;
    
    
    // the thin vertical lines in the Tetris grid:
    int d=352;
    SDL_Rect bottom[9];
    for (int i=0;i<9;i++)
    {
        bottom[i].x=d+32;
        bottom[i].y=32;
        bottom[i].w=1;
        bottom[i].h=704-64;
        d=d+32;
        
    }
    
    // the thin horizontal lines in the Tetris grid:
    int b=32;
    SDL_Rect side[20];
    for(int i = 0; i < 20; i++)
    {
        side[i].x=352;
        side[i].y=b+32;
        side[i].w=320;
        side[i].h=1;
        b=b+32;
    }
    
    // black background screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
    SDL_BlitSurface(BG,NULL,screen, NULL);
    
    // rest of the background rectangle stuff
    SDL_FillRect(screen, &one, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &three, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &onet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &threet, SDL_MapRGB(screen->format, 0,0,0));
    SDL_FillRect(screen, &thinhorizontaltop, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinhorizontalbottom, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinvertical1, SDL_MapRGB(screen->format, 0,0,255));
    SDL_FillRect(screen, &thinvertical2, SDL_MapRGB(screen->format, 0,0,255));
    
    // Gray shape to show where it would land
    SDL_Rect shade[4];
    Coordinate * block = model->block();
    for (int i = 0; i<4; i++) {
        int yco = 19;
        shade[i].w=32;
        shade[i].h=32;
        shade[i].x= 352+ (block[i].x + model->shadeLocation().x)*32;
        shade[i].y= 32 + (block[i].y + model->shadeLocation().y)*32;
        SDL_FillRect(screen, &shade[i], SDL_MapRGB(screen->format, 120,120,120));
    }
    
    SDL_FillRects(screen, bottom, 9, SDL_MapRGB(screen->format, 64,64,64));
    SDL_FillRects(screen, side, 20, SDL_MapRGB(screen->format, 64,64,64));

    
    // Choosing correct image based on block spawned
	switch (model->shape) {
		case I:
            blockIMG = IblockIMG;
			break;
		case O:
            blockIMG = OblockIMG;
			break;
		case T:
            blockIMG = TblockIMG;
			break;
		case S:
            blockIMG = SblockIMG;
			break;
		case Z:
            blockIMG = ZblockIMG;
			break;
		case J:
            blockIMG = JblockIMG;
			break;
		case L:
            blockIMG = LblockIMG;
			break;
        case D:
            break;
        default:
            break;
	}
	
    // making four 32 by 32 pixel blocks
    SDL_Rect dest[4];
	for (int i = 0; i < 4; i++) {
		dest[i].w = 32;
		dest[i].h = 32;
		dest[i].x = 352+ (block[i].x + model->location.x) * 32;
		dest[i].y = 32 + (block[i].y + model->location.y) * 32;
		SDL_FillRect(screen, &dest[i], SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
	}
	//SDL_BlitSurface calls for block images
	for (int x = 0; x < 4; x++) {
		SDL_BlitSurface(blockIMG, NULL, screen, &dest[x]);
	}
    
    for (int i=0; i<20; i++) {
        for (int j=0; j<10; j++) {
            switch (model->colorGrid[i][j]) {
                case I:
                    blockIMG = IblockIMG;
                    break;
                case O:
                    blockIMG = OblockIMG;
                    break;
                case T:
                    blockIMG = TblockIMG;
                    break;
                case S:
                    blockIMG = SblockIMG;
                    break;
                case Z:
                    blockIMG = ZblockIMG;
                    break;
                case J:
                    blockIMG = JblockIMG;
                    break;
                case L:
                    blockIMG = LblockIMG;
                    break;
                case D:
                    break;
                default:
                    break;
            }
            switch (model->colorGrid[i][j]) {
                case I:
                case O:
                case T:
                case S:
                case Z:
                case J:
                case L:
                    SDL_Rect dest;
                    dest.w = 32;
                    dest.h = 32;
                    dest.x = 352 + j*32;
                    dest.y = 32 + i*32;
                    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0x80, 0x00, 0x00));
                    SDL_BlitSurface(blockIMG, NULL, screen, &dest);
                    break;
                case D:
                    break;
                default:
                    break;
            }
            
        }
    }
    
    SDL_Color textColor = { 255, 255, 255 };
    textPaused = TTF_RenderText_Solid( font, "Press P to pause", textColor );
    SDL_Rect textDest;
    textDest.x = 750;
    textDest.y = 400;
    SDL_BlitSurface( textPaused, NULL, screen, &textDest );
    
    scoreString = to_string(model->score);
    SDL_Color textColorScore = { 255, 255, 255 };
    text2 = TTF_RenderText_Solid( font, scoreString.c_str(), textColorScore );
    SDL_Rect textDestScore;
    textDestScore.x = 100;
    textDestScore.y = 150;
    SDL_BlitSurface( text2, NULL, screen, &textDestScore );
    
    SDL_UpdateWindowSurface(window);
}
