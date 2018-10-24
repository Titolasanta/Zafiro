//
// Created by tito on 24/10/18.
//

#ifndef TP_FASE1_TEST_LIFESUPPORT_H
#define TP_FASE1_TEST_LIFESUPPORT_H


#include "../common/Thread.h"
#include "../common/Socket.h"

class lifeSupport : public Thread{
public:
    lifeSupport(Socket& skt,bool& quit);
    virtual void run();
private:
    Socket skt;
    bool& quit;
};


#endif //TP_FASE1_TEST_LIFESUPPORT_H
