//
// Created by tito on 08/10/18.
//

#ifndef TP_FASE1_TEST_MODELPROTOCOL_H
#define TP_FASE1_TEST_MODELPROTOCOL_H
#include <queue>
#include "../common/Socket.h"
#include <mutex>
#include "../common/Thread.h"
#include "../common/Scene.h"

class ModelProtocol : public Thread {

private:
    Socket skt;
    Socket sktSignal;
    char id;
    bool quit = false;
    bool valid = true;
    std::queue<char>& queue;
    std::mutex& mutex;

public:
    ModelProtocol(Socket&  ,std::queue<char>& ,char id, std::mutex& mutex,Socket&);
    ModelProtocol(ModelProtocol&& other) noexcept;
    void run() override;
    void end();
    void send(Scene& scene);
    void receiveLatency();
    char getId() const;
    ModelProtocol& operator=(ModelProtocol&& other) = delete;
    ~ModelProtocol() override;

};


#endif //TP_FASE1_TEST_MODELPROTOCOL_H
