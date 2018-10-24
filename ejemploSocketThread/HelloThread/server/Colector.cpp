
#include "Thread.h"
#include "HelloSocket/common/Socket.h"
#include <list>
#include "CommandFactory.h"
#include "Colector.h"
#include "../../../TP-Fase1-Test/common/Exception.h"
#include "Joiner.h"
#include "Monitor.h"


Colector::Colector(Socket &skt,std::list<command*>& l,
		Monitor& monitor)
		: socket(std::move(skt)),list(l),monitor(monitor){}

	void Colector::run() {	
		Joiner joiner(list);
		try {
		CommandFactory factory;
		while(must_continue) {
			char ch = 1;
			joiner.run();
			Socket skt2 = socket.accept_connection(); //const con mov

			command *s = factory.return_command(ch, skt2, monitor);
			list.push_back(s);		
			s->start();
			sockets.push_back(std::move(skt2));	
		}
		}catch( accept_fail e){}
			joiner.end();
	}

	void Colector::end() {
		socket.manual_close();
		must_continue = false;
	}

	Colector::~Colector(){}	

