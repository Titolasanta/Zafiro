

#include "HelloSocket/common/Socket.h"
#include <stdio.h>
#include "HelloThread/common/Exception.h"
#include "Comandos.h"
#include <string>
#include "CommandFactory.h"
#include <list>
#include "Thread.h"
#include <iostream>
#include "Colector.h"
#include "Monitor.h"

using std::string;
using std::cout;
using std::list;

int main(int argc, char *argv[]) {
	try {
	    char port[5] = "8081";
		Socket skt(port, 0);
		skt.start_to_listen();

	list<command*> l;
	Monitor monitor;
	Colector colector(skt,l,monitor);
	colector.start();

	while(true) {
		if('q' == getchar())
			break;
	}
	colector.end();
	colector.join();


        std::cout << "cantidad de clientes atendidos: "<< monitor.getI() << std::endl;

	} catch (OSError e) {
		cout << "what: " << e.what() << "\n";
	}catch (Finalizo_conexion e) {
		//todo ok
	}catch(...) {
		cout << "Excepcion desconocida\n.";
	}

	return 0;
}
