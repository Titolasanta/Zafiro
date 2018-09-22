//
// Created by tito on 07/09/18.
//

#include <string>
#include <zconf.h>
#include "View.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "Personajes.h"
#include "pugixml.hpp"
#include "xml.h"
#include "Logger.h"
#include <iostream>

extern Logger* gplogger;

View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT)
: window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),
personajes(&window),piedra(&window),pasto(&window),background(window,1)
{
   // window.setRenderDrawColor(0x10  ,0x10,0xFF,0x120);
    std::string windowName("juego");

    gplogger->log(1,"se crea un View\n");

}


void View::render(Scene& scene) {

    gplogger->log(1,"comienza renderear view\n");

    window.redererClear();

   //background.render(scene);
    piedra.render(scene);
    pasto.render(scene);

    SDL_Rect* camera = background.getCamera();

    //Center the camera over the player
    camera->x = ( scene.getP1PositionX() ) - 800 / 2;
    camera->y = ( scene.getP1PositionY() ) - 600 / 2;


    std::cout << "pos player" << scene.getP1PositionX() << ".\n";
    std::cout << camera->x << ".\n";
    std::cout << camera->y << ".\n";

    //Keep the camera in bounds
    if( camera->x < 0 )
    {
        camera->x = 0;
    }
    if( camera->y < 0 )
    {
        camera->y = 0;
    }
    if( camera->x > LEVEL_WIDTH - camera->w )
    {
        camera->x = LEVEL_WIDTH - camera->w;
    }
    if( camera->y > LEVEL_HEIGHT - camera->h )
    {
        camera->y = LEVEL_HEIGHT - camera->h;
    }

    background.render(scene);
    personajes.render(scene,camera->x, camera->y);

    window.updateRenderer();

    gplogger->log(1,"finaliza renderear view\n");
}