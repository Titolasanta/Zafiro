//
// Created by tito on 27/10/18.
//

#ifndef TP_FASE1_TEST_SIGNALCHECKER_H
#define TP_FASE1_TEST_SIGNALCHECKER_H


#include "../common/Thread.h"
#include "SignalReceiver.h"

class SignalChecker : public Thread {
public:
    SignalChecker(SignalReceiver&);
    virtual void run();
    void end();
private:
    SignalReceiver& signalReceiver;
    bool quit = false;
};


#endif //TP_FASE1_TEST_SIGNALCHECKER_H
