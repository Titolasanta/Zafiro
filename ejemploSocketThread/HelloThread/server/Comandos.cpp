#include "HelloSocket/common/Socket.h"
#include <string>
#include "Comandos.h"
#include <list>
#include <set>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#define CONST_ARB 100
using std::string;
using std::list;
using std::set;


bool command::ended() {
	return finished;
}

command::command(Socket &socket, Monitor& monitor) :	monitor(monitor),skt(socket)  {
}
	

void Mensajito::run() {

    //de aca en adelante da igual quien es el server y el cliente

    char msg1[10];
    strcpy(msg1,"123456789\n");
    skt.send_all(msg1,10);


    const std::string msg2("987654321\n");
    skt.send_all(msg2.c_str(),10);
    std::cout << msg2;


    skt.receive_all(msg1,10);
    std::cout << msg1;

    //mandar/recibir un int, por little/big endian incopatiblidad lleva el paso intermedio

    unsigned int numeroRecibido;
    char recibido[4];

    skt.receive_all(recibido,4);

    unsigned int temp = *(unsigned int*)recibido;
    numeroRecibido = ntohl(temp);
    std::cout << numeroRecibido << "\n";

    monitor.clienteAtendido();

    finished = true;
    return;
}
