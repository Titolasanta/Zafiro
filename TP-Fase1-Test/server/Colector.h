#ifndef SERVER_COLECTOR
#define SERVER_COLECTOR

#include "Thread.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "Model.h"
#include <list>

class Colector : public Thread {
public:
	Colector(Socket &skt,std::list<ModelProtocol>& list,std::queue<char> &queue,std::mutex &mutex, Model &model);
	virtual void run();
	~Colector();
	void end();	

private:
	Socket socket;
	std::queue<char> &queue;
	std::mutex &mutex;
	std::list<ModelProtocol>& list;
	std::list<Socket> sockets;
	Model &model;
	bool must_continue = true;	
};

#endif
