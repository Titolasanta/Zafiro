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
#include "Sprite.h"
#include "SpriteHandler.h"
#include "View.h"
#include "Controller.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../common/Logger.h"
#include "../common/Exception.h"
#include "FullHouse.h"
#include "Verifier.h"
#include "InvalidLogin.h"
#include "Quit.h"
#include "lifeSupport.h"
#include "Sound.h"

#define PATH_XML_ORIGINAL "../Archivos/configuracion.xml"
#define PATH_XML_DEFAULT "../Archivos/default.xml"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

pugi::xml_document* gXML_doc[2];
Logger *gplogger;
pugi::xml_parse_result *gXML_parse_result;

int main( int argc, char* argv[] )
{
    pugi::xml_document doc;
    pugi::xml_document doc_default;
    pugi::xml_parse_result result = doc.load_file(PATH_XML_ORIGINAL);
    pugi::xml_parse_result result_default = doc_default.load_file(PATH_XML_DEFAULT);

    const char* modo;
    if (argc > 1 ) {
        modo = argv[1];
    }
    else if (!(result || result_default)) modo = "DEBUG";
    else modo = get_log_level(doc, result);
    Logger logger(modo,get_log_level(doc_default, result_default));

    if (!(result)) {
        std::string mensaje = get_error_message("Error al cargar el archivo XML: ", PATH_XML_ORIGINAL, (int) result.offset, result.description());
        logger.log(1, mensaje.c_str());
        if (!result_default) {
            mensaje = get_error_message("Error al cargar el archivo XML por defecto: ", PATH_XML_DEFAULT, (int) result_default.offset, result_default.description());
            logger.log(1, mensaje.c_str());
            return 0;
        }
        logger.log(1, "Se cargó un archivo por defecto");
    }

    
    gplogger = &logger;

    gXML_doc[0] = &doc;
    gXML_doc[1] = &doc_default;
    gXML_parse_result = &result;


    char id = 0;
    const char* port = get_port(doc, doc_default, result);
    View view(SCREEN_WIDTH, SCREEN_HEIGHT);

    Mix_PlayMusic(view.getSound().getMenuMusic(), -1);

    bool cutedConnection = false;
    lifeSupport ls(cutedConnection);
    try {
        bool quit = false;
        Socket skt(port, get_ip(doc, doc_default, result));
        Socket sktLatido(port, get_ip(doc, doc_default, result));

        ls.controlSocket(&skt);

        view.waiting();
        
        skt.receive_all(&id, 1); //verifica que el server le de bola
        
        Verifier verifier(view,skt,ls);
        SDL_Event e;
        ls.start();
        //limpio eventos de mientras esperaba q me d bola el server
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) { throw Quit(); }
        }

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                quit = verifier.processEvent(e);
                if (e.type == SDL_QUIT) { throw Quit(); }
            }
            sktLatido.send_all("1",1);
            verifier.show();
        }


        skt.receive_all(&id, 1);
        view.setId(id);
        Controller controller(view, skt,ls,sktLatido);
        controller.startGame();

    }catch(Finalizo_conexion &fc) {
        if (!cutedConnection){
            if(view.getLevel() == 4) ;//view.endOfGameScreen();
            else view.conexionFail();
            logger.log(2, "Se cayo la coneccion");
            return 0;
        }else {
            view.conexionFail2();
            logger.log(2, "Se cayo la coneccion");
            return 0;
        }
    }catch(FullHouse &fh){
        view.fullHouseMesage();
        logger.log(2, "Cliente leyo que esta lleno el server");
    }catch(InvalidLogin &il){
        view.invalidLoginMesage();
        logger.log(2, "Error al loggear al juego");
    }catch(Quit &q){
        logger.log(2, "Usuario cerro el juego");
    }catch(OSError &e){
        if(strcmp(e.what(),"problema inesperado al enviar mensage:\nerrno: Broken pipe") != 0) {
            view.conexionDown();
            logger.log(2, "Server no encontrado.");
        }else;
    }
    ls.end();
    ls.join();
    logger.log(2, "Se cerró el juego");
    logger.cerrar_archivo();

    return 0;
}
