//
// Created by tito on 07/11/18.
//

#include "StaticEnemyImg.h"

StaticEnemyImg::StaticEnemyImg(Window *window) : Viewable(window,"../spirites/NES_contra_enemies2.png",2*2,2*213,2*32,2*32)  {

}

void StaticEnemyImg::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getEnemies(),camera);
}