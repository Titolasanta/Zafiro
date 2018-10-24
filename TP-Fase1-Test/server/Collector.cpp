
#include "Thread.h"
#include <list>
#include <zconf.h>
#include <iostream>
#include "Collector.h"
#include "Joiner.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "../common/Exception.h"
#include "Model.h"
#include "../common/pugixml.hpp"
#include "../common/Logger.h"
#include "xmlServer.h"

extern Logger *gplogger;
extern pugi::xml_document*gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;


Collector::Collector(Socket &skt, std::list<ModelProtocol>& list,std::queue<char> &queue,std::mutex &mutex, Model &model) : socket(std::move(skt)),list(list),queue(queue),mutex(mutex),model(model){
    if (*gXML_parse_result)	cargar_users(*gXML_doc[0], UPlist);
    else cargar_users(*gXML_doc[1], UPlist);
}

void Collector::run() {
    std::string aux;
    char nextId = 0;
    char id = 0;
    try {
        while(must_continue) {

            Socket skt2 = socket.accept_connection();
            skt2.send_all(&id,1); //ignorar, solo sirve pa q no empiezen 2 clientes a la vez
            char c;
            bool validUP = false;
            skt2.receive_all(&c,1);
            std::string msg;
            skt2.receive_all(msg,c);
            for(auto it = UPlist.begin(); it != UPlist.end();it++){
                if(*it == msg){
                    validUP = true;
                }
            }
            auto it = hash.find(msg);
            if(it != hash.end() || !validUP){ //check esta?
                id = it->second;
                if(!model.getJugadorLiseado()[id-1] || !validUP){ //esta conectado?
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

