//
// Created by tito on 25/09/18.
//

#ifndef TP_FASE1_TEST_COLLISIONHARD_H
#define TP_FASE1_TEST_COLLISIONHARD_H


#include <tuple>
#include <list>
#include "Character.h"

class CollisionHard {
public:
    CollisionHard(Character &char1, std::list<std::tuple<int, int,int>>& platformList);

};


#endif //TP_FASE1_TEST_COLLISIONHARD_H
