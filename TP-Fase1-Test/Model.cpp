//
// Created by tito on 07/09/18.
//

#include "Model.h"

Model::Model(Scene& scene) : scene(scene) {

}

void Model::update(SDL_Event event){
    if(event.type == SDL_KEYDOWN)
        if( event.key.keysym.sym == SDLK_RIGHT ) {
            scene.rojox(10);
            scene.rojoMove(1);
        }

    if(event.type == SDL_KEYUP)
        if( event.key.keysym.sym == SDLK_RIGHT ) {
            scene.rojoNotMove();
        }
}
