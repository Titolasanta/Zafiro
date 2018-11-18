//
// Created by tito on 14/11/18.
//

#include "Boss.h"

Boss::Boss(int level) {
    if(level == 1){
        posX = 8400;
        posY = 90;
    }
    if(level == 2){
        posX = 19;
        posY = -3680;
    }
    if(level == 3){
        posX = 8200;
        posY = -50;
    }
}