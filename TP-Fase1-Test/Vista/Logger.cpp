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
    time_t now = time(NULL);
    char temporal[255];
    char* fecha = temporal;
    strcpy(fecha, ctime(&now));
    fecha[strlen(fecha)-1] = '\0';
    archivo << "_________________________________________________________________________________________" << std::endl;
    archivo << "[" << fecha << "]\n\n>NUEVO JUEGO INICIADO" << std::endl;
    archivo << "MODO " << log_level << "\n" << std::endl;
    if (strcmp(log_level, "DEBUG") == 0 || strcmp(log_level,"debug") == 0 || strcmp(log_level, "Debug") == 0) nivel = 3;
    if (strcmp(log_level, "INFO") == 0 || strcmp(log_level,"info") == 0 || strcmp(log_level, "Info") == 0) nivel = 2;
    if (strcmp(log_level, "ERROR") == 0 || strcmp(log_level,"error") == 0 || strcmp(log_level, "Error") == 0) nivel = 1;
}

void Logger::log(int level, const char* mensaje){
    char* nivel_log;
    if (level == 1) nivel_log =  "<ERROR> ";
    if (level == 2) nivel_log = "<INFO> ";
    if (level == 3) nivel_log = "<DEBUG> ";
    if (level <= nivel){
        time_t now = time(NULL);
        struct tm* info;
        info = localtime(&now);
        archivo << "[" << info->tm_hour << ":" << info->tm_min << ":" << info->tm_sec << "] ";
        archivo << nivel_log << mensaje << std::endl;
    }
}

void Logger::cerrar_archivo(){
    archivo.close();
}