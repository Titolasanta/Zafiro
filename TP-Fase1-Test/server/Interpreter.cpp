//
// Created by tito on 10/10/18.
//

#include "Interpreter.h"

extern std::mutex mutexG;
Interpreter::Interpreter(std::list<ModelProtocol> &protocolList, std::queue<char> &queue, std::mutex &mutex, Model &model, Scene &scene)
    : protocolList(protocolList),queue(queue),mutex(mutex),model(model),scene(scene){

}
void Interpreter::run(){
    while(!quit) {
        std::lock_guard<std::mutex> x(mutexG);
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
           mutex.unlock();

           if (!strcmp(&msg[1], "jp")) model.jump(msg[0]);
           else if (!strcmp(&msg[1], "mr")) model.moveRight(msg[0]);
           else if (!strcmp(&msg[1], "ml")) model.moveLeft(msg[0]);
           else if (!strcmp(&msg[1], "ad")) model.aimDown(msg[0]);
           else if (!strcmp(&msg[1], "au")) model.aimUp(msg[0]);
           else if (!strcmp(&msg[1], "cr")) model.crouch(msg[0]);
           else if (!strcmp(&msg[1], "sh")) model.shoot(msg[0]);
           else if (!strcmp(&msg[1], "st")) model.stop(msg[0]);
           else if (!strcmp(&msg[1], "as")) model.aimStraight(msg[0]);
           else if (!strcmp(&msg[1], "sd")) model.stand(msg[0]);
           else if (!strcmp(&msg[1], "ss")) model.stopShooting(msg[0]);
           else if (!strcmp(&msg[1], "mi")) model.immortalize(msg[0]);
           else if (!strcmp(&msg[1], "fc")){
               model.bajaJugador(msg[0]);
               for (auto it = protocolList.begin(); it != protocolList.end(); it++) {
                   if (msg[0] == it->getId()-1)
                       it = protocolList.erase(it); //falta un mutex, pero meh
               }
           } 
       }
  /*  mutex.lock();
    model.update(scene);
    mutex.unlock();
    */}
}

void Interpreter::end(){
    quit = true;
}


