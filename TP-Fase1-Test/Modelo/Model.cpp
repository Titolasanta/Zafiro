//
// Created by tito on 07/09/18.
//


#include "Model.h"

Model::Model(Scene& scene)
: scene(scene),player1(10,10) // , player2()

{
    //this->scene = scene;
    level = 1;
}

void Model::update(SDL_Event event){

}
