//
// Created by tito on 10/10/18.
//

#include <zconf.h>
#include "Sender.h"
#include "../common/Exception.h"

extern std::mutex mutexG;

Sender::Sender(std::list<ModelProtocol> &l,Scene &scene,Model& model) : pList(l),scene(scene),model(model){}

void Sender::run() {
    while (!quit) {
        usleep(54000);
        if (!pList.empty())
            model.update(scene);
        else if (scene.getLevel() == 4)
            throw 1;

        std::lock_guard<std::mutex> x(mutexG);
        for (auto it = pList.begin(); it != pList.end(); it++) {
            try {
                it->send(scene);
            } catch (...) {
                int i = it->getId();
                it->end();
                it = pList.erase(it);//falta un mutex, pero meh(seria convertir la lista en una clase con una lista y un mutex)
                model.bajaJugador(i);
            }
        }
    }
}

void Sender::end(){
    quit = true;
}