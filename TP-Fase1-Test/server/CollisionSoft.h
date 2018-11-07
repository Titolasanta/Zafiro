//
// Created by tito on 19/09/18.
//

#ifndef TP_FASE1_TEST_COLLISION_H
#define TP_FASE1_TEST_COLLISION_H


#include <list>
#include <tuple>
#include "Character.h"

class CollisionSoft {
public:
    CollisionSoft(Character&,std::list<std::tuple<int,int,int>>& platformList);
    CollisionSoft(Enemy&,std::list<std::tuple<int,int,int>>& platformList);
};


#endif //TP_FASE1_TEST_COLLISION_H
