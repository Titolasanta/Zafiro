//
// Created by tito on 08/10/18.
//

#ifndef TP_FASE1_TEST_MODELPROTOCOL_H
#define TP_FASE1_TEST_MODELPROTOCOL_H
#include <queue>
#include "../common/Socket.h"
#include <mutex>
#include "Thread.h"
#include "../common/Scene.h"

class ModelProtocol : public Thread {
public:
    ModelProtocol(Socket& ,std::queue<char>& ,char id, std::mutex& mutex);
    void run() override;
    void end();
    void send(Scene& scene);

    ModelProtocol(ModelProtocol&& other);

    ModelProtocol& operator=(ModelProtocol&& other) = delete;

private:
    Socket skt;
    char id;
    bool quit = false;
    std::queue<char> queue;
    std::mutex& mutex;
};


#endif //TP_FASE1_TEST_MODELPROTOCOL_H
