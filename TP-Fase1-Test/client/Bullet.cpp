//
// Created by tito on 17/09/18.
//

#include "Bullet.h"
#include "../common/Logger.h"


extern Logger *gplogger;
Bullet::Bullet(Window *window) : Viewable(window,"../spirites/Bullet.png",34,18,10,10) {

    gplogger->log(3,"Se crea Bullet de vista");
}

void Bullet::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLBullets(),camera);
}