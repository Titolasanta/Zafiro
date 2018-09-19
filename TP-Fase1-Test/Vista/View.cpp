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

    personajes.render(scene);

    window.updateRenderer();

    gplogger->log(1,"finaliza renderear view\n");
}