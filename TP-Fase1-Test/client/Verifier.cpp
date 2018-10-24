//
// Created by tito on 22/10/18.
//

#include "Verifier.h"
#include "../common/Logger.h"
#include "FullHouse.h"
#include "InvalidLogin.h"

extern Logger *gplogger;

Verifier::Verifier(View &view, Socket &skt) : view(view),socket(std::move(skt)) {
    UvalidationData = "";
    PvalidationData = "";
    gplogger->log(3, "Se crea el Verificador");
}

void Verifier::unsuccessfulValidation() {
    throw 1;
}

void Verifier::verify() {
    char msg[255];
    char c = 1 + UvalidationData.length() + PvalidationData.length();
    strcpy(msg,UvalidationData.c_str());
    msg[UvalidationData.length()] = '\n';
    strcpy(&(msg[UvalidationData.length() + 1]),PvalidationData.c_str());

    socket.send_all(&c,1);
    socket.send_all(msg,c);
    socket.receive_all(&c,1);
    if(c == 0){
        throw FullHouse();
    } else if(c == 1){
        throw InvalidLogin();
    }
}

char identifyChar(SDL_Event e){
    if (e.type != SDL_KEYDOWN)
        return 0;
    if (e.key.keysym.sym == SDLK_a) return 'a';
    if (e.key.keysym.sym == SDLK_b) return 'b';
    if (e.key.keysym.sym == SDLK_c) return 'c';
    if (e.key.keysym.sym == SDLK_d) return 'd';
    if (e.key.keysym.sym == SDLK_e) return 'e';
    if (e.key.keysym.sym == SDLK_f) return 'f';
    if (e.key.keysym.sym == SDLK_g) return 'g';
    if (e.key.keysym.sym == SDLK_h) return 'h';
    if (e.key.keysym.sym == SDLK_i) return 'i';
    if (e.key.keysym.sym == SDLK_j) return 'j';
    if (e.key.keysym.sym == SDLK_k) return 'k';
    if (e.key.keysym.sym == SDLK_l) return 'l';
    if (e.key.keysym.sym == SDLK_m) return 'm';
    if (e.key.keysym.sym == SDLK_n) return 'n';
    if (e.key.keysym.sym == SDLK_o) return 'o';
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
    if (e.key.keysym.sym == SDLK_ESCAPE) return '?';
    if (e.key.keysym.sym == SDLK_RETURN) return '\n';
    return 0;
}

bool Verifier::nextValidation() {
    if (!onPass) {
        onPass = true;
        return false;
    }
    else {
        this->verify();
        return true;
    }
}

bool Verifier::resetData() {
    UvalidationData.clear();
    PvalidationData.clear();
    onPass = false;
    return false;
}

bool Verifier::readChar(SDL_Event e) {
    char c = identifyChar(e);
    if(c != 0){
        if(c == '?'){
            return this->resetData();
        }
        if(c == '\n') {
            return this->nextValidation();
        }
        else{
            if(!onPass){
                UvalidationData += c;
            } else
                PvalidationData += c;
        }
    }
    return false;
}

bool Verifier::processEvent(SDL_Event e) {
    return readChar(e);
}

void Verifier::show() {
    view.renderValidationScreen(UvalidationData,PvalidationData);
}