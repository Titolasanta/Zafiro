//
// Created by tito on 13/09/18.
//

#include <Model.h>
#include "Controler.h"

Controler::Controler(View &view, Model& model) : view(view),model(model){}

void Controler::processEvent(SDL_Event e) {

    if(e.type == SDL_KEYDOWN) {

        if (e.key.keysym.sym == SDLK_RIGHT) {
            model.moveRight();
        }

        if (e.key.keysym.sym == SDLK_LEFT){
            model.moveLeft();
        }
    }

    if(e.type == SDL_KEYUP)
        if( e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT ) {
            model.stop();
        }
}

void Controler::show() {
    model.update(scene);
    view.render(scene);
}