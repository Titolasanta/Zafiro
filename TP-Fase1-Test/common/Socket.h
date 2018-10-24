
#ifndef SOCKET_H
#define SOCKET_H
#include <string>
#include <stdlib.h>
class Socket {
	private:
	explicit Socket(int skt_id);
	bool is_valid = true;

	int skt_id;
	public:
	//ip=0 --> server
	Socket(const char* port,const char* ip);
	~Socket();
	Socket(Socket&& other);	
	Socket(const Socket &other) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket& operator=(Socket&&);
	//send all pero en formato string
	const Socket& operator<<(const std::string& to_send);
	int start_to_listen();	
	void manual_close();
	//accepta conexion, la retorna con movimiento	
	Socket accept_connection();
	ssize_t receive_all(std::string&, size_t);
	ssize_t send_all(const char* msg, int len);
	ssize_t receive_all(char* msg, int len);
	void flush();
};









#endif
