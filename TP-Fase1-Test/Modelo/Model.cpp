//
// Created by tito on 07/09/18.
//


#include "Model.h"

Model::Model() : player1(100,200) {
    //this->scene = scene;
    level = 1;
}

void Model::time(){
    player1.time();
}

void Model::update(Scene &scene) {

    this->time();
    scene.setP1PositionX(player1.getPositionX());

    scene.setP1PositionY(player1.getPositionY());

    scene.setP1Airborne(player1.isAirborne());

    scene.setP1AimDirection(player1.getAimDirection());

    scene.setP1Dead(player1.isDead());

    scene.setP1Crouching(player1.isCrouching());

    scene.setP1LookingRight(player1.isLookingRight());

    scene.setP1Walking(player1.isWalking());


}

void Model::moveRight() {
    player1.move(10);
}

void Model::moveLeft() {
    player1.move(-10);
}

void Model::stop() {
   // if(!player1.isAirborne())
        player1.standStill();
}

void Model::jump() {
    player1.jump(-20);
}

void Model::aimDown() {
    player1.aim(1);
}

void Model::aimUp() {
    player1.aim(-1);
}
void Model::aimStraight() {
    player1.aim(0);
}