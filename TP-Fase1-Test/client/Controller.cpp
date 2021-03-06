//
// Created by tito on 13/09/18.
//
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Controller.h"
#include "../common/Logger.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../server/Model.h"
#include "../client/View.h"

extern Logger *gplogger;
extern pugi::xml_document*gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;


Controller::Controller(View &view, Socket& skt,lifeSupport& ls,Socket& sktAux) : sktLatido(sktAux),ls(ls),view(view),protocol(skt), scene(get_cantidad_jugadores(*gXML_doc[0], *gXML_doc[1], *gXML_parse_result)){
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
            if(scene.isAllPlayersConnected()) processEvent(e);
        }
        show();
        if (timeTillNextShoot > 0) timeTillNextShoot -= 12;
    }
}

void Controller::processEvent(SDL_Event e) {
    if(!view.isInLevelSummary()) {
        if (e.type == SDL_KEYDOWN && scene.getLevel() != 4) {
            if (e.key.keysym.sym == SDLK_SPACE) protocol.jump();
            else if (e.key.keysym.sym == SDLK_RIGHT) protocol.moveRight();
            else if (e.key.keysym.sym == SDLK_LEFT) protocol.moveLeft();
            else if (e.key.keysym.sym == SDLK_DOWN) protocol.aimDown();
            else if (e.key.keysym.sym == SDLK_UP) protocol.aimUp();
            else if (e.key.keysym.sym == SDLK_LCTRL) protocol.crouch();
            else if (e.key.keysym.sym == SDLK_x) protocol.shoot();
            else if (e.key.keysym.sym == SDLK_i) protocol.immortal();

            //if (e.key.keysym.sym == SDLK_l){ protocol.changeLevel(protocol.getLevel().next(),scene); }
        }

        if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) protocol.stop();
            else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) protocol.aimStraight();
            else if (e.key.keysym.sym == SDLK_LCTRL) protocol.stand();
            else if (e.key.keysym.sym == SDLK_x) protocol.stopShooting();
        }
    }else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_n) {
        if (scene.getLevel() != 4)
            view.setInLevelSummary(0);
        else view.endOfGameScreen();
    }
}

void Controller::show() {
    sktLatido.send_all("1",1);
    if(scene.getLevel() != 4 )
        //if(!view.isInLevelSummary())
           protocol.update(scene);
    ls.report();
    //lobby, espera del resto de los jugadores
    if (!scene.isAllPlayersConnected()) {
        view.waiting_for_players();
    } else {
        if (endOfMainMenu == 0){
            endOfMainMenu++;
            Mix_HaltMusic();
            Mix_PlayMusic(view.getSound().getLevelOneMusic(), -1);
        }
        view.render(scene);
    }
}

