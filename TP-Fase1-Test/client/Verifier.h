//
// Created by tito on 22/10/18.
//

#ifndef TP_FASE1_TEST_VERIFIER_H
#define TP_FASE1_TEST_VERIFIER_H


#include <string>
#include "View.h"
#include "../common/Socket.h"

class Verifier {


public:
    void show();
    bool processEvent(SDL_Event);
    Verifier(View& view, Socket& skt);

    bool readChar(SDL_Event);
    bool nextValidation();
    void unsuccessfulValidation();
    void verify();

private:
    View& view;
    Socket socket;
    bool validated = false;
    bool onPass = false;
    std::string UvalidationData;
    std::string PvalidationData;
};


#endif //TP_FASE1_TEST_VERIFIER_H
