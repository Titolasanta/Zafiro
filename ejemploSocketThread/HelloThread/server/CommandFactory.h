#ifndef SERVER_COMAND_FACTORY
#define SERVER_COMAND_FACTORY
#include "Comandos.h"
#include "HelloSocket/common/Socket.h"
#include "Monitor.h"

class CommandFactory {
public:
	CommandFactory();
	command* return_command(int, Socket&, Monitor& monitor);
};

#endif




