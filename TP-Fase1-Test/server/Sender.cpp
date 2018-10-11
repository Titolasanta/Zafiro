//
// Created by tito on 10/10/18.
//

#include <zconf.h>
#include "Sender.h"

Sender::Sender(std::list<ModelProtocol> &l,Scene &scene) : pList(l),scene(scene){}

void Sender::run(){
    while(!quit){
        usleep(50000);
        for (auto it = pList.begin(); it != pList.end(); it++) {
            it->send(scene);
        }
    }
}

void Sender::end(){
    quit = true;
}