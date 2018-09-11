//
// Created by tito on 07/09/18.
//

#include "Model.h"

Model::Model(Scene& scene) {
    scene = scene;
    level = 1;
    player1 = Character(posX,posY);
    player2 = NULL;
}

void Model::update(SDL_Event event){

}
