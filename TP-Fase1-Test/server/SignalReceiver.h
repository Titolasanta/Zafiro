//
// Created by tito on 27/10/18.
//

#ifndef TP_FASE1_TEST_SERVERLIFESUPPORT_H
#define TP_FASE1_TEST_SERVERLIFESUPPORT_H


#include "../common/Thread.h"
#include "ModelProtocol.h"

class SignalReceiver : public Thread {
public:
    SignalReceiver(std::list<ModelProtocol> &protocolList);
    void addSocket(Socket& skt);
    virtual void run();
    std::mutex mutex;
    void closeCurrent();
    void end();
    
    bool running = true;
private:
    std::list<ModelProtocol> &protocolList;
    std::list<Socket> socketList;
    int current_id = 0;
    bool quit = false;
};


#endif //TP_FASE1_TEST_SERVERLIFESUPPORT_H
