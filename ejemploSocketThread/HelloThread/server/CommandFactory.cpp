#include "CommandFactory.h"
#include "Comandos.h"


CommandFactory::CommandFactory(){}

command* CommandFactory::return_command(int i, Socket& skt,Monitor& monitor) {
		switch(i) {
	   case 1  :
	      return new Mensajito(skt,monitor);
	      break;
	   default:
		throw 1;
	}
}

