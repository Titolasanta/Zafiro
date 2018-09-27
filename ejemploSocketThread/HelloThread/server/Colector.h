#ifndef SERVER_COLECTOR
#define SERVER_COLECTOR

#include "Thread.h"
#include "HelloSocket/common/Socket.h"

#include "Comandos.h"
#include "Monitor.h"
#include <list>

class Colector : public Thread {
	public:
	Colector(Socket &skt,std::list<command*>& l,Monitor& monitor);
	virtual void run();
	~Colector();
	void end();	

	private:
	Socket socket;
	std::list<command*>& list;
	Monitor& monitor;
	std::list<Socket> sockets;
	bool must_continue = true;	
};

#endif
