//
// Created by tito on 07/11/18.
//

#include "MovingEnemyImg.h"

MovingEnemyImg::MovingEnemyImg(Window *window) : texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ))
, mobileRect{{0,2,32,62}, //Corriendo hacia adelante
             {38,0,32,64}, //(segunda linea sprite sheet)
             {74,0,30,64},
             {108,2,32,64},
             {144,0,32,64},
             {180,0,32,64}}
{
    texture.loadFromFile("../spirites/enemies.png");
}

void MovingEnemyImg::render(Scene &scene,SDL_Rect* camera) {
    auto lista = scene.getEnemies();
    for (auto it = lista->begin(); it != lista->end(); it++) {
        texture.render(it->getPosX() - camera->x, it->getPosY() - camera->y, &mobileRect[it->getCurrentFrame()],180 * it->isLookingRight());
    }
}
