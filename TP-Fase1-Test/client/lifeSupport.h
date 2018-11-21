//
// Created by tito on 24/10/18.
//

#ifndef TP_FASE1_TEST_LIFESUPPORT_H
#define TP_FASE1_TEST_LIFESUPPORT_H

#include "../common/Thread.h"
#include "../common/Socket.h"

class lifeSupport : public Thread{
    
private:
    bool& cutedConnection;
    Socket* skt;
    std::mutex mutex;
    bool quit = false;
    bool onCheck = true;

public:
    explicit lifeSupport(bool&);
    void run() override;
    void controlSocket(Socket*);
    void end();
    void report();
    ~lifeSupport() override{ join(); }

};

#endif //TP_FASE1_TEST_LIFESUPPORT_H
