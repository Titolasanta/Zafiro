
#include "Thread.h"
#include <list>
#include "Colector.h"
#include "Joiner.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "../common/Exception.h"


Colector::Colector(Socket &skt,std::list<ModelProtocol>& list,std::queue<char> &queue,std::mutex &mutex) : socket(std::move(skt)),list(list),queue(queue),mutex(mutex){}

void Colector::run() {
    int id = 0;
    try {
        while(must_continue) {
            id++;
			Socket skt2 = socket.accept_connection(); //const con mov
            ModelProtocol protocol(skt2,queue,id,mutex);
			list.push_back(std::move(protocol));
			protocol.start();
			//sockets.push_back(std::move(skt2));
		}
    }catch( accept_fail& e){}

}

void Colector::end() {
    socket.manual_close();
    must_continue = false;
}

Colector::~Colector(){}

