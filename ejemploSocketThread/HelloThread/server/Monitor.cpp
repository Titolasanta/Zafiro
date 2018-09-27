//
// Created by tito on 27/09/18.
//

#include <mutex>
#include "Monitor.h"

void Monitor::clienteAtendido() {
    //toma el mutex hasta que se destruya "mute" aka final de la funcion
    std::lock_guard<std::mutex> mute(mut);
    i++;
}