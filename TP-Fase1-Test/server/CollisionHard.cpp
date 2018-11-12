//
// Created by tito on 25/09/18.
//

#define PLATALTO 25
#define CHARACTERWIDTH 0
#include <iostream>
#include "CollisionHard.h"

CollisionHard::CollisionHard(Character &char1, std::list<std::tuple<int, int,int>>& platformList) {
    if (char1.getVelocityY() > 0) {
        for (auto it = platformList.begin(); it != platformList.end(); it++) {
            if (std::get<0>(*it) < char1.getPositionX() + char1.getVelocityX()
                && std::get<0>(*it) + std::get<2>(*it) > char1.getPositionX() + char1.getVelocityX()) {
                if (std::get<1>(*it) > characterHeight + char1.getPositionY()
                    && std::get<1>(*it) < char1.getPositionY() + characterHeight + char1.getVelocityY() + 5) {
                    int height = characterHeight;
                    if(char1.isDead()) height = 15;
                    char1.land(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it), true);
                    char1.setPositionX(char1.getPositionX() + char1.getVelocityX());
                    char1.setPositionY(std::get<1>(*it) - height);
                    break;
                }
            }
        }
    } else
        for (auto it = platformList.begin(); it != platformList.end(); it++) {
            int platX = std::get<0>(*it);
            int platY = std::get<1>(*it);
            int platW = std::get<2>(*it);
            //choque de cabeza
            if (platX < char1.getPositionX() + char1.getVelocityX()
                && platX + platW > char1.getPositionX() + char1.getVelocityX()) {
                if (platY < char1.getPositionY()
                    && platY + PLATALTO > char1.getPositionY() + char1.getVelocityY()) {


                    char1.setPositionY(std::get<1>(*it) + PLATALTO);
                    char1.setVelocityY(0);
                    break;
                }

            }
        }
}
