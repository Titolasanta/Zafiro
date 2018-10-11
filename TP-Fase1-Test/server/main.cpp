

#include "HelloSocket/common/Socket.h"
#include <stdio.h>
#include "../../../TP-Fase1-Test/common/Exception.h"
#include "Comandos.h"
#include <string>
#include "CommandFactory.h"
#include <list>
#include "Thread.h"
#include <iostream>
#include <SDL_opengles2_gl2ext.h>
#include "Colector.h"
#include "Monitor.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "Sender.h"
#include "Model.h"
#include "../common/Exception.h"
#include "Interpreter.h"

using std::string;
using std::cout;
using std::list;

int main(int argc, char *argv[]) {
	try {
	    char port[5] = "8081";
		Socket skt(port, 0);
		skt.start_to_listen();

		Scene scene;
        Model model(1);

        std::queue<char> queue;
        std::mutex mutex;

	    list<ModelProtocol> pList;

    	Colector colector(skt,pList,queue,mutex);
    	Interpreter interpreter(pList,queue,mutex,model);
    	Sender sender(pList,scene);

    	colector.start();
    	interpreter.start();
    	sender.start();

    	while(true) {
	    	if('q' == getchar())
		    	break;
	    }
	    colector.end();
        interpreter.end();
        sender.end();
	    colector.join();



	} catch (OSError e) {
		cout << "what: " << e.what() << "\n";
	}catch (Finalizo_conexion e) {
		//todo ok
	}catch(...) {
		cout << "Excepcion desconocida\n.";
	}

	return 0;
}
