#include <iostream>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Texture.h"
#include <string>
#include <sstream>


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 800;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The windows we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES];
Texture gSpriteSheetTexture;

bool init(){
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO) < 0 ){
        printf("SDL could not initilize! SDL Error> %s \n", SDL_GetError() );
        success = false;
    }else{
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            printf("Warning: Linear texture filtering not enabled");
        }
        //Create window
        gWindow = SDL_CreateWindow( "SDL TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL){
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError()) ;
            success = false;
        }else{
            //Render for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL){
                printf("Renderer could not be created, SDL error: %s\n", SDL_GetError());
                success = false;
            }else{
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (! (IMG_Init( imgFlags) & imgFlags)){
                        printf("SDL_image could not initialize, DSL_image error: %s\n", IMG_GetError());
                        success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(){
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "sprites/NES - Contra - Bill Rizer & Lance Bean.png" ,gRenderer) )
    {
        printf( "Failed to load walking animation texture!\n" );
        return false;
    }
    else {

        //Set sprite clips
        gSpriteClips[ 0 ].x = 1;
        gSpriteClips[ 0 ].y = 43;
        gSpriteClips[ 0 ].w = 26;
        gSpriteClips[ 0 ].h = 35;

        gSpriteClips[ 1 ].x = 18;
        gSpriteClips[ 1 ].y = 43;
        gSpriteClips[ 1 ].w = 19;
        gSpriteClips[ 1 ].h = 35;

        gSpriteClips[ 2 ].x = 38;
        gSpriteClips[ 2 ].y = 47;
        gSpriteClips[ 2 ].w = 20;
        gSpriteClips[ 2 ].h = 31;

        gSpriteClips[ 0 ].x = 59;
        gSpriteClips[ 0 ].y = 44;
        gSpriteClips[ 0 ].w = 19;
        gSpriteClips[ 0 ].h = 35;

        gSpriteClips[ 1 ].x = 76;
        gSpriteClips[ 1 ].y = 44;
        gSpriteClips[ 1 ].w = 18;
        gSpriteClips[ 1 ].h = 34;

        gSpriteClips[ 2 ].x = 95;
        gSpriteClips[ 2 ].y = 47;
        gSpriteClips[ 2 ].w = 20;
        gSpriteClips[ 2 ].h = 31;
    }
    return true;
}

void close(){
    //Free loaded image
    gSpriteSheetTexture.free();

    //Destroy window
    SDL_DestroyWindow( gWindow);
    SDL_DestroyRenderer( gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    //QUit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if(!init()){
        printf("Failed to initialize\n");
    }else{
        if(!loadMedia()){
            printf("Failed to load media\n");
        }else{
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Current animation frame
            int frame = 0;

            //While app is running
            while(!quit){

                //Handle events queue
                while( SDL_PollEvent( &e) != 0){

                    //User wants to quit
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }

                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear( gRenderer);

                //Render current frame
                SDL_Rect* currentClip = &gSpriteClips[ frame / 6];
                gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, gRenderer,currentClip );

                //Update screen
                SDL_RenderPresent( gRenderer);

                //Go to next frame
                ++frame;

                //Cycle animation
                if( frame / 6 >= WALKING_ANIMATION_FRAMES )
                {
                    frame = 0;
                }

            }
        }
    }

    //Free resources and close SDL
    close();
    return 0;
}