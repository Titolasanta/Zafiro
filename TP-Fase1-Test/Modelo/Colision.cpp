//
// Created by tito on 19/09/18.
//

#include "Colision.h"

#define largoPlataforma 70
#define altoPJ 30
Colision::Colision(Character &char1, std::list<std::tuple<int, int>>& lPlataforms) {
    if (char1.getVelocityY() > 0) {
        for (std::list<std::tuple<int, int>>::iterator it = lPlataforms.begin(); it != lPlataforms.end(); it++) {
            printf("pj: %d,%d, plat: %d,%d\n",char1.getPositionX(),char1.getPositionY(),std::get<0>(*it),std::get<1>(*it));
            if (std::get<0>(*it) < char1.getPositionX() + char1.getVelocityX()
                && std::get<0>(*it) + largoPlataforma > char1.getPositionX() + char1.getVelocityX() ) {
                if (std::get<1>(*it) > char1.getPositionY() - char1.getVelocityY() - altoPJ
                    && std::get<1>(*it) < char1.getPositionY() + altoPJ ) {
                    printf("entre");
                    char1.land();
                    char1.setPositionX(char1.getPositionX() + char1.getVelocityX());
                    char1.setPositionY(std::get<1>(*it) - altoPJ);
                    break;
                }
            }
        }
    }
}