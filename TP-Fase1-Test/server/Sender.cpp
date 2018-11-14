//
// Created by tito on 10/10/18.
//

#include <zconf.h>
#include "Sender.h"
#include "../common/Exception.h"

Sender::Sender(std::list<ModelProtocol> &l,Scene &scene,Model& model) : pList(l),scene(scene),model(model){}

void Sender::run(){
    while(!quit){
        usleep(45000);
        if(!pList.empty())
            model.update(scene);
        for (auto it = pList.begin(); it != pList.end(); it++) {

            try {
                it->send(scene);
            } catch (...) {
                int i = it->getId();
                it = pList.erase(it);//falta un mutex, pero meh(seria convertir la lista en una clase con una lista y un mutex)
                model.bajaJugador(i);
            }
        }
    }
}

void Sender::end(){
    quit = true;
}