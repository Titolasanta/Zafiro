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
#include "Sprite.h"
#include "Personajes.h"
#include "View.h"
#include "Controller.h"
#include "pugixml.hpp"
#include "xml.h"
#include "Logger.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"
#define PATH_XML_ORIGINAL "../Archivos/configuracion.xml"
#define PATH_XML_DEFAULT "../Archivos/default.xml"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window

pugi::xml_document* gXML_doc[2];
Logger *gplogger;

int main( int argc, char* argv[] )
{
    pugi::xml_document doc;
    pugi::xml_document doc_default;
    pugi::xml_parse_result result = doc.load_file(PATH_XML_ORIGINAL);
    pugi::xml_parse_result result_default = doc_default.load_file(PATH_XML_DEFAULT);

    if (!(result || result_default)) {
        std::cout << "Error al cargar el archivo de configuración por defecto: " << result_default.description() << std::endl;
    }
    const char* modo;
    if (argc > 1 ) {
        modo = argv[1];
    } else
        modo = get_log_level(doc);
    Logger logger(modo,get_log_level(doc_default));


    gplogger = &logger;

    gXML_doc[0] = &doc;
    gXML_doc[1] = &doc_default;



    View view(SCREEN_WIDTH,SCREEN_HEIGHT);


    Model model(1);


    Controller controler(view,model);



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