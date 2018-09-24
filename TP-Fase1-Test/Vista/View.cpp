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
#define MARGENX (800/2)
#define MARGENY (600/3)

extern Logger* gplogger;
extern pugi::xml_document *gXML_doc[2];

View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT)
: window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),
personajes(&window),piedra(&window),pasto(&window),background(window,1)
{
   // window.setRenderDrawColor(0x10  ,0x10,0xFF,0x120);
    std::string windowName("juego");

    gplogger->log(1,"se crea un View\n");

}

void View::render(Scene& scene) {

    camera = scene.getCamera();

    gplogger->log(1, "comienza renderear view\n");

    window.redererClear();

    //background.render(scene);


    //Center the camera over the player
    if (scene.getLevel() != 2){
        if (scene.getP1PositionX() > MARGENX + camera->x)
            camera->x = scene.getP1PositionX() - MARGENX;
    }else {
        if (scene.getP1PositionY() < MARGENY + camera->y)
            if(scene.getP1PositionY() - MARGENY < 0)
                camera->y = scene.getP1PositionY() - MARGENY;
    }

    background.render(scene,*camera);



    piedra.render(scene,camera);
    pasto.render(scene,camera);
    personajes.render(scene,camera->x, camera->y);
    window.updateRenderer();

    gplogger->log(1,"finaliza renderear view\n");


}