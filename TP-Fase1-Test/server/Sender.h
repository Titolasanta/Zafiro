//
// Created by tito on 10/10/18.
//

#ifndef TP_FASE1_TEST_SENDER_H
#define TP_FASE1_TEST_SENDER_H


#include "../common/Thread.h"
#include "ModelProtocol.h"
#include "Model.h"

class Sender : public Thread {
public:
    virtual void run();
    explicit Sender(std::list<ModelProtocol>& l,Scene& scene,Model& model);
    void end();
private:
    std::list<ModelProtocol>& pList;
    bool quit = false;
    Model& model;
    Scene &scene;
};


#endif //TP_FASE1_TEST_SENDER_H
