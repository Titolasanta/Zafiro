//
// Created by tito on 10/10/18.
//

#ifndef TP_FASE1_TEST_INTERPRETER_H
#define TP_FASE1_TEST_INTERPRETER_H


#include "Thread.h"
#include "../common/Scene.h"
#include "Model.h"
#include "ModelProtocol.h"

class Interpreter : public Thread {

public:
    Interpreter(std::list<ModelProtocol> &protocolList,std::queue<char> &queue,std::mutex &mutex,Model &model);
    virtual void run();
    void end();
private:
    Scene scene;
    std::list<ModelProtocol>& protocolList;
    std::queue<char>& queue;
    std::mutex &mutex;
    Model& model;
    bool quit = false;

};


#endif //TP_FASE1_TEST_INTERPRETER_H
