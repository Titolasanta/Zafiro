//
// Created by tito on 24/10/18.
//

#include <zconf.h>
#include "lifeSupport.h"

lifeSupport::lifeSupport(Socket &skt,bool& quit) : skt(std::move(skt)),quit(quit) {}

void lifeSupport::run() {
    while(1) {
        usleep(100000);
     //   try {
            skt.send_all("1", 1);
      /*  } catch (...) {
            quit = true;
        }*/
    }
}