//
// Created by tito on 27/09/18.
//

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include "HelloSocket/common/Socket.h"

int main(int argc, char *argv[]){

    //Socket skt(argv[1], 0);
    char port[5] = "8081";
    Socket skt(port, 0);
    skt.start_to_listen();
    Socket skt2 = skt.accept_connection(); //const con mov
    //de aca en adelante da igual quien es el server y el cliente

    char msg1[10];
    strcpy(msg1,"123456789\n");
    skt2.send_all(msg1,10);


    const std::string msg2("987654321\n");
    skt2.send_all(msg2.c_str(),10);
    std::cout << msg2;


    skt2.receive_all(msg1,10);
    std::cout << msg1;

    //mandar/recibir un int, por little/big endian incopatiblidad lleva el paso intermedio

    unsigned int numeroRecibido;
    char recibido[4];

    skt2.receive_all(recibido,4);

    unsigned int temp = *(unsigned int*)recibido;
    numeroRecibido = ntohl(temp);
    std::cout << numeroRecibido << "\n";

    return 1;


}