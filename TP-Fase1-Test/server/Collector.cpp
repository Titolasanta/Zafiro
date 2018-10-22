
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
    char nextId = 0;
    char id = 0;
    try {
        while(must_continue) {
            Socket skt2 = socket.accept_connection();

            char c;
            skt2.receive_all(&c,1);
            std::string msg;
            skt2.receive_all(msg,c);

            auto it = hash.find(msg);
            if(it != hash.end()){ //check esta?
                id = it->second;
                if(!model.getJugadorLiseado()[id-1]){ //esta conectado?
                    c = 1;
                    skt2.send_all(&c, 1);
                    usleep(60000);
                } else{ //reconectar
                    c = 2;
                    skt2.send_all(&c, 1);
                    skt2.send_all(&id, 1);
                    ModelProtocol protocol(skt2, queue, id, mutex);
                    model.rejoinCharacter(id);
                    list.push_back(std::move(protocol));
                    list.back().start();
                }
            }else { // -> no esta
                if (model.getCurrentPlayers() < model.getMaxPlayers()) {
                    nextId++;
                    hash.emplace(msg, nextId);
                    id = nextId;
                    c = 2;
                    skt2.send_all(&c, 1);

                    skt2.send_all(&id, 1);
                    ModelProtocol protocol(skt2, queue, id, mutex);
                    model.createCharacter(id);
                    list.push_back(std::move(protocol));
                    list.back().start();
                } else {
                    c = 0;
                    skt2.send_all(&c, 1);
                    usleep(60000);
                }
            }
        }
    }catch (accept_fail& e){}
}

void Collector::end() {
    socket.manual_close();
    must_continue = false;
}

Collector::~Collector(){}

