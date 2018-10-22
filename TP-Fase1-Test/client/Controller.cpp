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

    UvalidationData = "";
    PvalidationData = "";
    gplogger->log(3, "Se crea el controlador");
}
void Controller::unsuccesfullValidation() {
    throw 1;
}

char identifieChar(SDL_Event e){
    if (e.type != SDL_KEYDOWN)
        return 0;
    if (e.key.keysym.sym == SDLK_a) return 'a';
    if (e.key.keysym.sym == SDLK_b) return 'b';
    if (e.key.keysym.sym == SDLK_c) return 'c';
    if (e.key.keysym.sym == SDLK_d) return 'd';
    if (e.key.keysym.sym == SDLK_e) return 'e';
    if (e.key.keysym.sym == SDLK_f) return 'f';
    if (e.key.keysym.sym == SDLK_g) return 'g';
    if (e.key.keysym.sym == SDLK_i) return 'h';
    if (e.key.keysym.sym == SDLK_j) return 'i';
    if (e.key.keysym.sym == SDLK_k) return 'j';
    if (e.key.keysym.sym == SDLK_l) return 'k';
    if (e.key.keysym.sym == SDLK_m) return 'l';
    if (e.key.keysym.sym == SDLK_n) return 'm';
    if (e.key.keysym.sym == SDLK_o) return 'n';
    if (e.key.keysym.sym == SDLK_p) return 'p';
    if (e.key.keysym.sym == SDLK_q) return 'q';
    if (e.key.keysym.sym == SDLK_r) return 'r';
    if (e.key.keysym.sym == SDLK_s) return 's';
    if (e.key.keysym.sym == SDLK_t) return 't';
    if (e.key.keysym.sym == SDLK_u) return 'u';
    if (e.key.keysym.sym == SDLK_v) return 'v';
    if (e.key.keysym.sym == SDLK_w) return 'w';
    if (e.key.keysym.sym == SDLK_x) return 'x';
    if (e.key.keysym.sym == SDLK_y) return 'y';
    if (e.key.keysym.sym == SDLK_z) return 'z';
    if (e.key.keysym.sym == SDLK_RETURN) return '\n';
    return 0;
}

void Controller::nextValidation() {
    if(!onPass)
        onPass = true;
    else
        if(protocol.validate(UvalidationData + '\n' + PvalidationData)){
            validated = true;
        } else
            this->unsuccesfullValidation();
}

void Controller::readChar(SDL_Event e) {
    char c = identifieChar(e);
    if(c != 0){
        if(c == '\n')
            this->nextValidation();
        else{
            if(!onPass){
                UvalidationData += c;
            } else
                PvalidationData += c;
        }
    }
}
void Controller::processEvent(SDL_Event e) {

    if(!validated){
       readChar(e);
    } else{
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
}

void Controller::show() {
    if(validated) {
        protocol.update(scene);
        view.render(scene);
    } else{
        view.renderValidationScreen(UvalidationData,PvalidationData);
    }
}