//
// Created by tito on 27/09/18.
//

#ifndef TP_FASE2_TEST_SERVERMONITOR_H
#define TP_FASE2_TEST_SERVERMONITOR_H

#include <mutex>

class Monitor {
private:
    int i=0;
public:
    void clienteAtendido();
    std::mutex mut;
    int getI(){return i;}

};


#endif //TP_FASE2_TEST_SERVERMONITOR_H
