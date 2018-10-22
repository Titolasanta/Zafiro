//
// Created by tito on 22/10/18.
//

#ifndef TP_FASE1_TEST_INVALIDLOGIN_H
#define TP_FASE1_TEST_INVALIDLOGIN_H


#include <exception>

class InvalidLogin : public std::exception {
public:
    InvalidLogin() = default;
};


#endif //TP_FASE1_TEST_INVALIDLOGIN_H
