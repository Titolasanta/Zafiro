//
// Created by tito on 27/10/18.
//

#include "SignalReceiver.h"
#include "../common/Exception.h"

SignalReceiver::SignalReceiver(std::list<ModelProtocol> &protocolList) : protocolList(protocolList) {}

void SignalReceiver::addSocket(Socket& skt){
    socketList.push_back(std::move(skt));
}

void SignalReceiver::run(){
    while(!quit){
        for (auto it = protocolList.begin(); it != protocolList.end(); it++) {
            mutex.lock();
            running = true;
            current_id = it->getId();
            mutex.unlock();
            try{
                it->receiveLatency();
            }catch(Finalizo_conexion){
                it = protocolList.begin();
            }
        }
    }
}

void SignalReceiver::closeCurrent() {
    for (auto it = protocolList.begin(); it != protocolList.end(); it++){
        if ( current_id == it->getId()) {
            it->end();
            protocolList.erase(it);
            break;
        }
    }
}

void SignalReceiver::end(){
    quit = true;
}