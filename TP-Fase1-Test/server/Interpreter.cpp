//
// Created by tito on 10/10/18.
//

#include "Interpreter.h"

Interpreter::Interpreter(std::list<ModelProtocol> &protocolList, std::queue<char> &queue, std::mutex &mutex, Model &model)
    : protocolList(protocolList),queue(queue),mutex(mutex),model(model){

}
void Interpreter::run(){
    while(!quit) {
       if(!queue.empty()) {
           char msg[4];
           mutex.lock();
           msg[0] = queue.front();
           queue.pop();
           msg[1] = queue.front();
           queue.pop();
           msg[2] = queue.front();
           queue.pop();
           msg[3] = '\0';

           if (!strcmp(&msg[1], "jp")) model.jump();
           else if (!strcmp(&msg[1], "mr")) model.moveRight();
           else if (!strcmp(&msg[1], "ml")) model.moveLeft();
           else if (!strcmp(&msg[1], "ad")) model.aimDown();
           else if (!strcmp(&msg[1], "au")) model.aimUp();
           else if (!strcmp(&msg[1], "ch")) model.crouch();
           else if (!strcmp(&msg[1], "st")) model.shoot();
           else if (!strcmp(&msg[1], "st")) model.stop();
           else if (!strcmp(&msg[1], "as")) model.aimStraight();
           else if (!strcmp(&msg[1], "sd")) model.stand();
           else if (!strcmp(&msg[1], "ss")) model.stopShooting();
           model.update(scene);
       }
    }
}

void Interpreter::end(){
    quit = true;
}


