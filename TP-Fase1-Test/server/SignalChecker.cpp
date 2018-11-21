//
// Created by tito on 27/10/18.
//

#include <zconf.h>
#include "SignalChecker.h"

SignalChecker::SignalChecker(SignalReceiver& sr) : signalReceiver(sr){}
void SignalChecker::run(){
    while(!quit){
        signalReceiver.mutex.lock();
        if(signalReceiver.running){
            signalReceiver.running = false;
            signalReceiver.mutex.unlock();
            usleep(400000);
        }else{
            signalReceiver.closeCurrent();
            signalReceiver.mutex.unlock();
        }
    }
}

void SignalChecker::end(){
    quit = true;
}