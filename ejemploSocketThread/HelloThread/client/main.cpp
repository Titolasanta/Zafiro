//
// Created by tito on 27/09/18.
//


#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <zconf.h>
#include "HelloThread/common/Socket.h"

int main(int argc, char *argv[]){


    //Socket skt(port, ip);
    char port[5] = "8081";
    Socket skt(port,"127.0.0.1");
    //de aqui en adelante no importa quien es el server o el cliente

    char msg1[10];
    skt.receive_all(msg1,10);
    std::cout << msg1;

    std::string msg2;
    skt.receive_all(msg2,10);
    std::cout << msg2;

    strcpy(msg1,"123456789\n");
    skt.send_all(msg1,10);

    //mandar/recibir un int, por little/big endian incopatiblidad lleva el paso intermedio
    unsigned int to_send = 100;
    unsigned int temp = htonl(to_send);

    char msgNumero[4];
    memcpy(msgNumero,&temp,4);

    skt.send_all(msgNumero,4);


    return 1;
}