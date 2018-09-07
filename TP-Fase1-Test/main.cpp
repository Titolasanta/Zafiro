#include <iostream>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
//#include "Texture.h"
#include <string>
#include <sstream>
#include <zconf.h>
#include "Window.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "SpriteRojo.h"
#include "Personajes.h"
#include "View.h"
#include "Model.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 800;

//Starts up SDL and creates window
bool init();




int main( int argc, char* args[] )
{

    //Xmler xml();



    Scene scene(1);

    View view(SCREEN_WIDTH,SCREEN_HEIGHT,scene);

    Model model(scene);

    //Event handler
    SDL_Event e;
    bool quit = false;


    while(!quit) {

        //Handle events queue
        while (SDL_PollEvent(&e) != 0) {

            //User wants to quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
                model.update(e);
        }

        view.render();

    }

    return 0;
}