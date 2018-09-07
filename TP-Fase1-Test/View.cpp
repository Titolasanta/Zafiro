//
// Created by tito on 07/09/18.
//

#include <string>
#include <zconf.h>
#include "View.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "Personajes.h"


View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT,Scene scene) : window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),personajes(&window),scene(scene)
{

    std::string windowName("juego");

}

void View::render() {

    window.redererClear();
    personajes.render(scene);
    window.updateRenderer();

}