#include "Exception.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include "Socket.h"
#include <utility>
#include <iostream>
#include <netinet/tcp.h>
#include <fcntl.h>

#define MAX_LISTEN 10
#define SIZE_ARBITRARIO 255

using std::string;

static int connect_socket(int skt, struct addrinfo* ptr) {
	int error;
	error = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
	if(error == -1) {
		throw OSError("Error al intentar connectarse:");
	}
	return error;
}

static int bind_socket(int skt,struct addrinfo* ptr ) {
	int error;	
	error = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	if(error == -1) {
		throw OSError("Error al intentar connectarse:");
	}
	return error;
}

	
Socket::Socket(int skt_id_r) : skt_id(skt_id_r) { }


Socket::Socket(const char* port, const char* ip) {
	int error,val,s;
	int skt;
	bool in_connection = false;
	struct addrinfo* ptr,*received;
	struct addrinfo hints;

	memset(&hints, 0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if(!ip)
		hints.ai_flags = AI_PASSIVE;
	else
		hints.ai_flags = 0;

	error = getaddrinfo(ip, port, &hints, &received);

	if(error != 0) {
		throw OSError("Error al intentar obtener informacion de la dirrecion:");
	}
   

	
	for(ptr = received; ptr != nullptr && !in_connection; ptr = ptr->ai_next){
		skt = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
		if (skt == -1) {
			throw OSError("Error al intentar crear el socket:");
		} else {
			if (ip) {
			     error = connect_socket(skt, ptr);
				in_connection = (error != -1);
			} else {

                val = 1;
                s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
                if (s == -1) {
					freeaddrinfo(received);
					close(skt);
					throw OSError("Error al intentar setear el socket:");
				}
				error = bind_socket(skt, ptr);
				in_connection = (error != -1);
			}
		}
	}

	freeaddrinfo(received);
	if (in_connection) {
		skt_id = skt;		
	} else {
		throw OSError("no se encontro conexion posible:");
	}
}



void Socket::manual_close() {
	if(is_valid) {
		shutdown(skt_id, SHUT_RDWR);
		close(skt_id);
	}
	is_valid = false;
}

Socket::~Socket() {
	if(is_valid) {
		shutdown(skt_id, SHUT_RDWR);
		close(skt_id);
	}
}

int Socket::start_to_listen() {
	int error = listen(skt_id, MAX_LISTEN);
	if (error == -1) {
		throw OSError("Error al intentar abrirse a conexiones:");		
	}
	return 0;
}	
	
Socket::Socket(Socket&& other) noexcept {
	other.is_valid = false;
	this->skt_id = other.skt_id;
}

Socket& Socket::operator=(Socket&& other) noexcept{
	other.is_valid = false;	
	this->skt_id = other.skt_id;
	return *this;	
}


Socket Socket::accept_connection() {
	int skt_id_nuevo = accept(skt_id, nullptr, nullptr);
	if (skt_id_nuevo == -1) {
		throw accept_fail();
	}	
	Socket skt_a_devolver(skt_id_nuevo);
    return std::move(skt_a_devolver);
}


ssize_t Socket::receive_all(char* msg, int len) {
	bool valid_socket = true;
	ssize_t temp = 1;
	ssize_t amount_received = 0;
	while (valid_socket && amount_received < len) {
	    temp = recv(skt_id, &msg[amount_received], (size_t) len-amount_received, 0);
		if (temp <= 0)
			valid_socket = false;
		else
			amount_received += temp;
	}
	msg[amount_received] = 0;

	if (temp==0)
		throw Finalizo_conexion();
	else if (temp < 0 )
		throw OSError("problema inesperado al recibir mensage:");
	return amount_received;
}

ssize_t Socket::send_all(const char* msg, int len) {
	ssize_t size_sent = 0;
	ssize_t temp = 1;

	bool valid_socket = true;	
	while (size_sent < len && valid_socket && is_valid) {
		temp = send(skt_id, &msg[size_sent], (size_t) (len - size_sent), 0);
		if (temp <= 0)
			valid_socket = false;		
		else
			size_sent += temp; 
	}
	
	if (temp == 0|| !is_valid)
		throw Finalizo_conexion();
	else if (temp < 0 )
		throw OSError("problema inesperado al enviar mensage:");
	return size_sent;
}


const Socket& Socket::operator<<(const string& str) {
	this->send_all(str.c_str(), (int) str.length());
	return *this;
}


ssize_t Socket::receive_all(string& str, size_t len){
	char temp_s[SIZE_ARBITRARIO];
	unsigned int leido;
	unsigned int leidoTotal = 0;
	str.clear();
	while(len > leidoTotal) {
		if( len-leidoTotal > SIZE_ARBITRARIO )
			leido = (unsigned int) this->receive_all(temp_s, SIZE_ARBITRARIO);
		else
			leido = (unsigned int) this->receive_all(temp_s, (int) len-leidoTotal);
		str.append(temp_s);
		leidoTotal += leido;
	}
	return leidoTotal;
}




