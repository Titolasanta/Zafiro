//
// Created by fede on 18/09/18.
//


#include "Logger.h"
#include <ctime>
#include <string.h>
#include <fstream>
#include <iostream>

#define LOG_PATH "../Archivos/log.txt"

Logger::Logger(const char* log_level, const char* level_default) : archivo(std::ofstream()){
    std::ofstream archivo_nuevo;
    archivo_nuevo.open(LOG_PATH, std::ofstream::app);
    archivo = std::move(archivo_nuevo);
    time_t now = time(nullptr);
    char temporal[255];
    char* fecha = temporal;
    strcpy(fecha, ctime(&now));
    fecha[strlen(fecha)-1] = '\0';
    archivo << "_________________________________________________________________________________________" << std::endl;
    archivo << "[" << fecha << "]\n\n>NUEVO JUEGO INICIADO" << std::endl;
    this->set_level(log_level, level_default);
    std::string level_string;
    if (nivel == 1) level_string = "ERROR";
    else if (nivel == 2) level_string = "INFO";
    else level_string = "DEBUG";
    archivo << "MODO " << level_string << "\n" << std::endl;
}

void Logger::set_level(const char *level, const char* ldefault) {
    if (strcmp(level, "DEBUG") == 0 || strcmp(level,"debug") == 0 || strcmp(level, "Debug") == 0) nivel = 3;
    else if (strcmp(level, "INFO") == 0 || strcmp(level,"info") == 0 || strcmp(level, "Info") == 0) nivel = 2;
    else if (strcmp(level, "ERROR") == 0 || strcmp(level,"error") == 0 || strcmp(level, "Error") == 0) nivel = 1;
    else{
        if (strcmp(ldefault, "DEBUG") == 0 || strcmp(ldefault,"debug") == 0 || strcmp(ldefault, "Debug") == 0) nivel = 3;
        else if (strcmp(ldefault, "INFO") == 0 || strcmp(ldefault,"info") == 0 || strcmp(ldefault, "Info") == 0) nivel = 2;
        else if (strcmp(ldefault, "ERROR") == 0 || strcmp(ldefault,"error") == 0 || strcmp(ldefault, "Error") == 0) nivel = 1;
    }
}

void Logger::cerrar_archivo(){
    archivo.close();
}

void Logger::log(int level, const char* mensaje) {
    std::string nivel_log;
    if (level == 1) nivel_log =  "<ERROR> ";
    if (level == 2) nivel_log = "<INFO> ";
    else nivel_log = "<DEBUG>";
    if (level <= nivel){
        time_t now = time(nullptr);
        struct tm* info;
        info = localtime(&now);
        archivo << "[" << info->tm_hour << ":" << info->tm_min << ":" << info->tm_sec << "] ";
        archivo << nivel_log << mensaje << std::endl    ;
    }
}

