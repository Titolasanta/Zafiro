//
// Created by tito on 19/09/18.
//

#include <iostream>
#include "CollisionSoft.h"

#define characterHeight 60
CollisionSoft::CollisionSoft(Character &char1, std::list<std::tuple<int, int,int>>& platformList) {
    if (char1.getVelocityY() > 0) {
        for(auto it = platformList.begin(); it != platformList.end(); it++) {
            if (std::get<0>(*it) < char1.getPositionX() + char1.getVelocityX()
                && std::get<0>(*it) + std::get<2>(*it) > char1.getPositionX() + char1.getVelocityX() ) {
                if (std::get<1>(*it) > characterHeight + char1.getPositionY()
                    && std::get<1>(*it) < char1.getPositionY() + characterHeight + char1.getVelocityY() +5 ) {
                    char1.land(std::get<0>(*it),std::get<1>(*it),std::get<2>(*it),false);
                    char1.setPositionX(char1.getPositionX() + char1.getVelocityX());
                    char1.setPositionY(std::get<1>(*it) - characterHeight);
                    break;
                }
            }
        }
    }
}
CollisionSoft::CollisionSoft(Enemy &enemy, std::list<std::tuple<int, int,int>>& platformList) {
    if (enemy.getVelY() > 0) {
        for(auto it = platformList.begin(); it != platformList.end(); it++) {
            if (std::get<0>(*it) < enemy.getPosX()
                && std::get<0>(*it) + std::get<2>(*it) > enemy.getPosX()) {
                if (std::get<1>(*it) > characterHeight + enemy.getPosY()
                    && std::get<1>(*it) < enemy.getPosY() + characterHeight + enemy.getVelY() +5 ) {
                    enemy.land(std::get<0>(*it),std::get<1>(*it),std::get<2>(*it));
                    enemy.setPosX(enemy.getPosX());
                    enemy.setPosY(std::get<1>(*it) - characterHeight);
                    break;
                }
            }
        }
    }
}