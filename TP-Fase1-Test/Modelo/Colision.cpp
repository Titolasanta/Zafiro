//
// Created by tito on 19/09/18.
//

#include "Colision.h"

#define altoPJ 30
Colision::Colision(Character &char1, std::list<std::tuple<int, int,int>>& lPlataforms) {
    if (char1.getVelocityY() > 0) {
        for (std::list<std::tuple<int, int, int>>::iterator it = lPlataforms.begin(); it != lPlataforms.end(); it++) {
            if (std::get<0>(*it) < char1.getPositionX() + char1.getVelocityX()
                && std::get<0>(*it) + std::get<2>(*it) > char1.getPositionX() + char1.getVelocityX() ) {
                if (std::get<1>(*it) > char1.getPositionY() - char1.getVelocityY() - altoPJ
                    && std::get<1>(*it) < char1.getPositionY() + altoPJ ) {
                    char1.land(std::get<0>(*it),std::get<1>(*it));
                    char1.setPositionX(char1.getPositionX() + char1.getVelocityX());
                    char1.setPositionY(std::get<1>(*it) - altoPJ);
                    break;
                }
            }
        }
    }
}