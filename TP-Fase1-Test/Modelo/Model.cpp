//
// Created by tito on 07/09/18.
//

#include "Model.h"
#include "Collision.h"

Model::Model(Nivel &initialLevel) : player1(100,0), level(initialLevel) {}

void Model::time(){

    player1.time();

    Collision(player1,lPlataforms);
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

void Model::addPlataform(int xi, int xf, int y) {
    lPlataforms.push_back(std::move(std::make_tuple(xi,xf,y)));
}

void Model::moveRight() {
    if (player1.getPositionX() > 700) this->stop();
    else player1.move(10);
}

void Model::moveLeft() {
    if (player1.getPositionX() < 10) this->stop();
    else player1.move(-10);
}

void Model::stop() { player1.standStill(); }

void Model::jump() { player1.jump(-36); }

void Model::aimDown() { player1.aim(1); }

void Model::aimUp() { player1.aim(-1); }

void Model::aimStraight() { player1.aim(0); }

void Model::crouch() { player1.crouch(); }

void Model::stand() { player1.stand(); }

void Model::changeLevel(Nivel &nivel) {
    level = nivel;
}
