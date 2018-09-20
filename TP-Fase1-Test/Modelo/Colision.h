//
// Created by tito on 19/09/18.
//

#ifndef TP_FASE1_TEST_COLISION_H
#define TP_FASE1_TEST_COLISION_H


#include <list>
#include <tuple>
#include "Character.h"

class Colision {
public:
    Colision(Character&,    std::list<std::tuple<int,int,int>>& lPlataforms);
};


#endif //TP_FASE1_TEST_COLISION_H
