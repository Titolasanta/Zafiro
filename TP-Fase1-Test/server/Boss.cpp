//
// Created by tito on 14/11/18.
//

#include "Boss.h"

Boss::Boss(int level) {
    if(level == 1){
        posX = 8300;
        posY = 200;
    }
    if(level == 2){
        posX = 100;
        posY = -3200;
    }
    if(level == 3){
        posX = 8300;
        posY = 200;
    }
}