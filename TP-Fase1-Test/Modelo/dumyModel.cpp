//
// Created by tito on 07/09/18.
//

#include "dumyModel.h"
#include "Vista/Scene.h"
void dumyModel::update(Scene &scene) {
    if(moveX)
        scene.rojoMove(10 * moveX);
    else
        scene.rojoNotMove();
}

void dumyModel::proces_event(SDL_Event event) {

    if(event.type == SDL_KEYDOWN) {

        if (event.key.keysym.sym == SDLK_RIGHT) {
            moveX = 1;
        }

        if (event.key.keysym.sym == SDLK_LEFT){
            moveX = -1;
        }
    }

    if(event.type == SDL_KEYUP)
        if( event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT ) {
            moveX = 0;
        }

}

dumyModel::dumyModel() {}