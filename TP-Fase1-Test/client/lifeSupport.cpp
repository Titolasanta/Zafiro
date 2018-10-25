//
// Created by tito on 24/10/18.
//

#include <zconf.h>
#include "lifeSupport.h"

lifeSupport::lifeSupport(Socket &skt,bool& quit) : skt(std::move(skt)),quit(quit) {}

void lifeSupport::run() {
    while(!quit) {
        usleep(100000);
        if(!skt.isValid())
            quit = true;
    }
}