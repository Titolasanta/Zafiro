//
// Created by tito on 22/10/18.
//

#ifndef TP_FASE1_TEST_QUIT_H
#define TP_FASE1_TEST_QUIT_H


#include <exception>

class Quit : public std::exception {
public:
    Quit() = default;
};


#endif //TP_FASE1_TEST_QUIT_H
