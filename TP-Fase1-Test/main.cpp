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

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 800;

//Starts up SDL and creates window
bool init();




int main( int argc, char* args[] )
{
    SdlInit uno;
    SdlImgInit dos;
    bool quit = false;
    std::string windowName("juego");
    Window window(windowName,SCREEN_WIDTH,SCREEN_HEIGHT);

//    usleep(100000000);

    //meter en clase
    Personajes personajes(&window);




    //Escenario escensario(window);

    //Xmler xml();


    //meter en clase MAP


    Scene scene(1);


    //Event handler
    SDL_Event e;

    int frame = 0;



    while(!quit) {

        //Handle events queue
        while (SDL_PollEvent(&e) != 0) {

            //User wants to quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if(e.type){
                usleep(100000);
            }

        }
        window.redererClear();

        //SDL_Rect *currentClip = rojo.mover( DER, frame%ROJO_DER_FRAMES);
        //personaje.render(posx, posy, currentClip);
        personajes.render(scene);
        //escenario.render(scene);

        window.updateRenderer();
        frame++;

    }

    return 0;
}