//
// Created by tito on 13/09/18.
//

#include "Controller.h"
#include "../common/Logger.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../server/Model.h"

#include "../server/Model.h"
#include "../client/View.h"
extern Logger *gplogger;
extern pugi::xml_document*gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;


Controller::Controller(View &view, Socket& skt) : view(view),protocol(skt), scene(get_cantidad_jugadores(*gXML_doc[0], *gXML_doc[1], *gXML_parse_result)){
    int lh = get_level_height( *gXML_doc[0], *gXML_doc[1], 1, *gXML_parse_result);
    int lw = get_level_width( *gXML_doc[0], *gXML_doc[1], 1, *gXML_parse_result);
    if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene, 1, lh, lw);
    else cargar_plataformas(*gXML_doc[1],scene, 1, lh, lw);

    gplogger->log(3, "Se crea el controlador");
}

void Controller::startGame(){
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = true; }
            processEvent(e);
        }
        show();
    }
}

void Controller::processEvent(SDL_Event e) {

    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) protocol.jump();
        if (e.key.keysym.sym == SDLK_RIGHT) protocol.moveRight();
        if (e.key.keysym.sym == SDLK_LEFT) protocol.moveLeft();
        if (e.key.keysym.sym == SDLK_DOWN) protocol.aimDown();
        if (e.key.keysym.sym == SDLK_UP) protocol.aimUp();
        if (e.key.keysym.sym == SDLK_LCTRL) protocol.crouch();
        if (e.key.keysym.sym == SDLK_x) protocol.shoot();
        //if (e.key.keysym.sym == SDLK_l){ protocol.changeLevel(protocol.getLevel().next(),scene); }
    }

    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) protocol.stop();
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) protocol.aimStraight();
        if (e.key.keysym.sym == SDLK_LCTRL) protocol.stand();
        if (e.key.keysym.sym == SDLK_x) protocol.stopShooting();
    }
}

void Controller::show() {
    protocol.update(scene);
    //lobby, espera del resto de los jugadores
/*    bool ready_to_play = scene.readyToPlay();
    while(!ready_to_play){
        view.waiting_for_players();
        ready_to_play = scene.readyToPlay();
    }*/
    view.render(scene);
}

