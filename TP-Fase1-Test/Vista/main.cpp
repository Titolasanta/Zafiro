#include <iostream>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
//#include "Texture.h"
#include <string>
#include <sstream>
#include <zconf.h>
#include <./Modelo/Model.h>
#include "Window.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "SpriteRojo.h"
#include "Personajes.h"
#include "View.h"
#include "Controler.h"
#include "pugixml.hpp"
#include "xml.h"
#include "Logger.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"
#define PATH_XML_ORIGINAL "/home/fede/CLionProjects/Zafiro/TP-Fase1-Test/Archivos/configuracion.xml"
#define PATH_XML_DEFAULT "/home/fede/CLionProjects/Zafiro/TP-Fase1-Test/Archivos/default.xml"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window

pugi::xml_document* gXML_doc;
Logger *gplogger;

int main( int argc, char* args[] )
{


    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(PATH_XML_ORIGINAL);
    if (!result) {
        // hacer algo con result.description()
        result = doc.load_file(PATH_XML_DEFAULT);
        if (!result) {
            //hacer algo con result.description();
            //    return 1;
        }
    }

    Logger logger(get_log_level(doc));

    gplogger = &logger;

    gXML_doc = &doc;


    View view(SCREEN_WIDTH,SCREEN_HEIGHT);

    Model model;


    Controler controler(view,model);



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
            //recibe evento modifica escena acorde
            controler.processEvent(e);
        }
        usleep(70000);
        //renderiza scene
        controler.show();

    }

    logger.cerrar_archivo();

    return 0;
}