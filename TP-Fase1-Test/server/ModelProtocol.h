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
    ModelProtocol(Socket& ,Socket& ,std::queue<char>& ,char id, std::mutex& mutex);
    void run() override;
    void end();
    void send(Scene& scene);

    ModelProtocol(ModelProtocol&& other);
    
    ModelProtocol& operator=(ModelProtocol&& other) = delete;
    ~ModelProtocol();
private:
    Socket skt;
    Socket sktAux;
    char id;
public:
    char getId() const;

private:
    bool quit = false;
    bool valid = true;
    std::queue<char>& queue;
    std::mutex& mutex;
};


#endif //TP_FASE1_TEST_MODELPROTOCOL_H
