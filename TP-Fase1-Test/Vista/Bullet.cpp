//
// Created by tito on 17/09/18.
//

#include "Bullet.h"
#include "Logger.h"


extern Logger *gplogger;
Bullet::Bullet(Window *window) : Viewable(window,"../spirites/Bullet.png",25,9,6,6) {

    gplogger->log(2,"se crea Bullet de vista");
}

void Bullet::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLBullets(),camera);
}