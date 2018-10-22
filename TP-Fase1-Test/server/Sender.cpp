//
// Created by tito on 10/10/18.
//

#include <zconf.h>
#include "Sender.h"
#include "../common/Exception.h"

Sender::Sender(std::list<ModelProtocol> &l,Scene &scene,Model& model) : pList(l),scene(scene),model(model){}

void Sender::run(){
    while(!quit){
        usleep(70000);
        int i = 0;
        for (auto it = pList.begin(); it != pList.end(); it++) {
            i++;
            model.update(scene);
            try {
                it->send(scene);
            }catch(...){
                it = pList.erase(it);
                model.bajaJugador(i);
            }
        }
    }
}

void Sender::end(){
    quit = true;
}