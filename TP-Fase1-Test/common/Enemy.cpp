//
// Created by tito on 07/11/18.
//

#include "Enemy.h"

Enemy::Enemy(int x,int y) {
    posX = x;
    posY = y;
}

int Enemy::getPosX() const {
    return posX;
}

void Enemy::setPosX(int posX) {
    Enemy::posX = posX;
}

int Enemy::getPosY() const {
    return posY;
}

void Enemy::setPosY(int posY) {
    Enemy::posY = posY;
}
