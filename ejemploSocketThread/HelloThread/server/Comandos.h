
#ifndef SERVER_COMANDOS_H
#define SERVER_COMANDOS_H
#include "HelloSocket/common/Socket.h"
#include "Thread.h"
#include "Monitor.h"

class command : public Thread{
public :
	virtual void run() = 0;
	virtual ~command() {}
	command(Socket &skt, Monitor& monitor);
	bool ended();

protected:
	Monitor& monitor;
	Socket& skt;
	bool finished = false;
};


class Mensajito : public command{
	public:
	Mensajito(Socket &skt, Monitor& monitor) : command(skt,monitor){}
	virtual ~Mensajito(){}
	virtual void run();
};

#endif
