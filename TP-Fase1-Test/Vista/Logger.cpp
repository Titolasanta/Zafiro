//
// Created by fede on 18/09/18.
//

#include "Logger.h"
#include <ctime>
#include <string.h>
#include <fstream>
#include <iostream>

Logger::Logger(const char* log_level) : archivo(std::ofstream()){
    std::ofstream archivo_nuevo;
    archivo_nuevo.open("log.txt", std::ofstream::app);
    archivo = std::move(archivo_nuevo);
    time_t now = time(0);
    char* fecha = ctime(&now);
    archivo << "_________________________________________________________________________________________" << std::endl;
    archivo << fecha << "\n>NUEVO JUEGO INICIADO" << std::endl;
    if (strcmp(log_level, "DEBUG") == 0 || strcmp(log_level,"debug") == 0 || strcmp(log_level, "Debug") == 0) nivel = 3;
    if (strcmp(log_level, "INFO") == 0 || strcmp(log_level,"info") == 0 || strcmp(log_level, "Info") == 0) nivel = 2;
    if (strcmp(log_level, "ERROR") == 0 || strcmp(log_level,"error") == 0 || strcmp(log_level, "Error") == 0) nivel = 1;
}

void Logger::log(int level, char* mensaje){
    if (level <= nivel){
        archivo << mensaje <<std::endl;
    }
}

void Logger::cerrar_archivo(){
    archivo.close();
}