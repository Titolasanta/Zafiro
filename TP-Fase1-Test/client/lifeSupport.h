//
// Created by tito on 24/10/18.
//

#ifndef TP_FASE1_TEST_LIFESUPPORT_H
#define TP_FASE1_TEST_LIFESUPPORT_H


#include "../common/Thread.h"
#include "../common/Socket.h"

class lifeSupport : public Thread{
public:
    lifeSupport(bool&);
    virtual void run();
    void controlSocket(Socket*);
    void end();
    void report();
    ~lifeSupport(){
        join();
    }
    
private:
    bool& cutedConnection;
    Socket* skt;
    std::mutex mutex;
    bool quit = false;
    bool onCheck = true;
};


#endif //TP_FASE1_TEST_LIFESUPPORT_H
