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
extern pugi::xml_document *gXML_doc[2];

View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT)
: window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),
personajes(&window),piedra(&window),plataformaDura(&window),hielo(&window),pasto(&window),bullet(&window),background(window,1)
{
   // window.setRenderDrawColor(0x10  ,0x10,0xFF,0x120);
    std::string windowName("juego");

    gplogger->log(3,"Se crea un View");

}

void View::render(Scene& scene) {

    camera = scene.getCamera();

    window.redererClear();

    //background.render(scene);




    background.render(scene,*camera, background.getScrollingOffset());


    hielo.render(scene,camera);
//    piedra.render(scene,camera);
    pasto.render(scene,camera);
    plataformaDura.render(scene,camera);
    bullet.render(scene,camera);
    personajes.render(scene,camera->x, camera->y);
    window.updateRenderer();

    //Center the camera over the player



}

void View::moveBackgroundRight(){
    int newOffset= background.getScrollingOffset();
    --newOffset;
    if (newOffset < -background.getImg1().getWidth() ) {
        newOffset = 0;
    }
    background.setScrollingOffset(newOffset);
}
