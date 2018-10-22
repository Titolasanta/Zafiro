
#include "Thread.h"
#include <list>
#include <zconf.h>
#include "Collector.h"
#include "Joiner.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "../common/Exception.h"
#include "Model.h"


Collector::Collector(Socket &skt,std::list<ModelProtocol>& list,std::queue<char> &queue,std::mutex &mutex, Model &model) : socket(std::move(skt)),list(list),queue(queue),mutex(mutex),model(model){}

void Collector::run() {
    std::string aux;
    int id = 0;
    try {
        while(must_continue) {
            Socket skt2 = socket.accept_connection();
            if (model.getCurrentPlayers() < model.getMaxPlayers()) {
                id = model.getCurrentPlayers() + 1; // causa errores, al desconectarse, reconectarse se hace model.move(2), pero solo hay 1 jg
                aux = std::to_string(id);
                const char* clientId = aux.c_str();
                skt2.send_all(clientId, 1);
                ModelProtocol protocol(skt2, queue, id, mutex);
                model.createCharacter();
                list.push_back(std::move(protocol));
                list.back().start();
                //sockets.push_back(std::move(skt2));
            } else {
                Socket skt2 = socket.accept_connection();
                char c = -1;
                skt2.send_all(&c,1);
                usleep(100000);
            }
        }
    }catch( accept_fail& e){}

}

void Collector::end() {
    socket.manual_close();
    must_continue = false;
}

Collector::~Collector(){}

