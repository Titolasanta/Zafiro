//
// Created by tito on 10/10/18.
//

#include <zconf.h>
#include "Sender.h"
#include "../common/Exception.h"

Sender::Sender(std::list<ModelProtocol> &l,Scene &scene,Model& model) : pList(l),scene(scene),model(model){}

void Sender::run(){
    while(!quit){
        usleep(100000);
        for (auto it = pList.begin(); it != pList.end(); it++) {
            model.update(scene);
            try {
                it->send(scene);
            }catch(...){
                it = pList.erase(it);
            }
        }
    }
}

void Sender::end(){
    quit = true;
}