#ifndef SERVER_COLECTOR
#define SERVER_COLECTOR

#include "Thread.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "Model.h"
#include <list>
#include <map>

class Collector : public Thread {
public:
	Collector(Socket &skt, std::list<ModelProtocol>& list,std::queue<char> &queue,std::mutex &mutex, Model &model);
	virtual void run();
	~Collector();
	void end();	

private:
    std::map<std::string,char> hash;
	Socket socket;
	std::queue<char> &queue;
	std::mutex &mutex;
	std::list<ModelProtocol>& list;
	std::list<Socket> sockets;
	std::list<std::string> UPlist;
	Model &model;
	bool must_continue = true;	
};

#endif
