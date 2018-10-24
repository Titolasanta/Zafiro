//
// Created by tito on 24/10/18.
//

#include <zconf.h>
#include "lifeSupport.h"

lifeSupport::lifeSupport(Socket &skt) : skt(std::move(skt)) {}

void lifeSupport::run(){
    //usleep(1000000);
    skt.send_all("1",1);
}