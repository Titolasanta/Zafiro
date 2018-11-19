//
// Created by tito on 24/10/18.
//

#include <zconf.h>
#include "lifeSupport.h"

lifeSupport::lifeSupport(bool& cutedConnection) : cutedConnection(cutedConnection){}

void lifeSupport::controlSocket(Socket* sktRec){
    skt = sktRec;
}

void lifeSupport::end(){
    quit = true;
}

void lifeSupport::report() {
    std::lock_guard<std::mutex> lock(mutex);
    this->onCheck = true;
}

void lifeSupport::run() {
    while(!quit){
        usleep(3000000); //3 seg
        std::lock_guard<std::mutex> lock(mutex);
        if(!this->onCheck){
            //skt->manual_close();
            quit = true;
            cutedConnection = true;
        }else{
            this->onCheck = false;
        }
    }
}

