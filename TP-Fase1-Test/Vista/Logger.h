//
// Created by fede on 18/09/18.
//

#ifndef TP_FASE1_TEST_LOGGER_H
#define TP_FASE1_TEST_LOGGER_H

#include <fstream>

class Logger {

private:
    int nivel;
    std::ofstream archivo;

public:
    Logger(const char* log_level);
    void set_level(const char* level);
    void log(int level, const char* mensaje);
    void cerrar_archivo();

};


#endif //TP_FASE1_TEST_LOGGER_H
