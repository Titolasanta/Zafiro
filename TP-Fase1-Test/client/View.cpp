//
// Created by tito on 07/09/18.
//

#include <string>
#include <zconf.h>
#include "View.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "Personajes.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../common/Logger.h"
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

    if(level != scene.getLevel())
        changeLevel();
    if(level == 2) {
        moveBackground(scene.getP1VelocityY());
        if (scene.getP1PositionY() == 200 && scene.getP1PositionX() == 200) background.setScrollingOffset(-200);
    }else {
        moveBackground(scene.getP1VelocityX());
        if (scene.getP1PositionY() == 200 && scene.getP1PositionX() == 200) background.setScrollingOffset(0);
    }
    camera = scene.getCamera();

    window.redererClear();

    //background.render(scene);



    background.render(scene,*camera, background.getScrollingOffset(),level);


    if(level == 1)
        piedra.render(scene,camera);

    hielo.render(scene,camera);

    pasto.render(scene,camera);
    plataformaDura.render(scene,camera);
    bullet.render(scene,camera);
    personajes.render(scene,camera->x, camera->y);
    window.updateRenderer();

    //Center the camera over the player



}

void View::changeLevel() {
    ++level;
    background.changeLevel(level);
}

void View::moveBackground(int dir) {
    int newOffset= background.getScrollingOffset();
    if(dir > 0) --newOffset;
    if(dir < 0) ++newOffset;

    if (newOffset > 0) newOffset = 0;
    //if (newOffset < -3000) newOffset = -100;


    background.setScrollingOffset(newOffset);
}
