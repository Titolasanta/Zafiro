//
// Created by fede on 15/09/18.
//

#include "xml.h"
#include "pugixml.hpp"
#include "Logger.h"
#include <string.h>
#include <iostream>

extern Logger *gplogger;

const char* get_log_level(pugi::xml_document &doc, pugi::xml_parse_result result){
    if (result) return doc.first_child().child("debug").first_child().child_value();
    return "FALOPA";
}

int get_level_width(pugi::xml_document &doc, pugi::xml_document &doc_default, int level, pugi::xml_parse_result result){
    gplogger->log(3,"se pregunta ancho del nivel al xml");
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    int original;
    if (result) {
        original = doc.first_child().child("escenarios").child(nivel.c_str()).child(
                "width").first_child().text().as_int();
        if (original) return original;
    }
    return doc_default.first_child().child("escenarios").child(nivel.c_str()).child("width").first_child().text().as_int();
}

int get_level_height(pugi::xml_document &doc, pugi::xml_document &doc_default, int level, pugi::xml_parse_result result){
    gplogger->log(3,"se pregunta altura del nivel al xml");
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    int original;
    if (result) {
        original = doc.first_child().child("escenarios").child(nivel.c_str()).child("height").first_child().text().as_int();
        if (original) return original;
    }
    return doc_default.first_child().child("escenarios").child(nivel.c_str()).child("height").first_child().text().as_int();

}

const char* get_level_background_path(pugi::xml_document& doc, pugi::xml_document& doc_default, int level, int numero_de_fondo, pugi::xml_parse_result result){

    gplogger->log(3,"se accede a un path de background de xml");
    std::string nivel = "nivel";
    std::string fondo = "fondo";

    nivel.append(std::to_string(level));
    fondo.append(std::to_string(numero_de_fondo));
    const char* original;
    if (result) {
        original = doc.first_child().child("escenarios").child(nivel.c_str()).child(fondo.c_str()).first_child().text().as_string();
        if (original) return original;
    }
    return doc_default.first_child().child("escenarios").child(nivel.c_str()).child(fondo.c_str()).first_child().text().as_string();
}

void cargar_plataformas(pugi::xml_document &doc,Scene& scene, Model &modelo, int level, int limite_vertical, int limite_horizontal){
    gplogger->log(3,"se cargan plataformas para un nivel desde el xml");
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    pugi::xml_node config = doc.first_child().child("escenarios").child(nivel.c_str());
    for (pugi::xml_node plataforma = config.child("plataforma"); plataforma; plataforma = plataforma.next_sibling("plataforma")){
        int xi = plataforma.child("xi").first_child().text().as_int();
        int xf = plataforma.child("xf").first_child().text().as_int();
        int y = plataforma.child("y").first_child().text().as_int();
        const char* tipo = plataforma.child("tipo").first_child().text().as_string();
        if (xi >= 0 && xf >=  0 && y >= -(limite_vertical - 600) && xi < xf && xi <= limite_horizontal && xf <= limite_horizontal && y <= 600) {
            if(!strcmp(tipo,"hierro")) {
                modelo.addPlataformHard(xi, y, xf - xi);
                scene.addPlataformHard(xi, y, xf - xi);
            }else {
                if(!strcmp(tipo,"pasto")) {
                    scene.addPlataformSoft(xi, y, xf - xi);
                    modelo.addPlataformSoft(xi, y, xf - xi);
                } else if(!strcmp(tipo,"hielo")){
                    scene.addPlataformHielo(xi,y,xf-xi);
                    modelo.addPlataformSoft(xi, y, xf - xi);
                }
            }
        }
        else gplogger->log(1, "Error al cargar una plataforma, el formato no era válido");

    }
   // modelo.addPlataformHard(0, 550, limite_horizontal);
    //scene.addPlataformHard(0,550,limite_horizontal);

}

std::string get_error_message(const char* message, const char* path, int pos, const char* description){
    std::string mensaje(message);
    mensaje.append(path);
    mensaje.append("[at line:");
    std::ifstream archivo(path);
    int lineNumber = 0;
    char c;
    for (int i = 0; i < pos; ++i){
        c = archivo.get();
        if (c == '\n') lineNumber++;
    }
    archivo.seekg(0);
    char linea[500];
    for (int i = 0; i < lineNumber +1; ++i) {
        archivo.getline(linea, 255);
    }
    mensaje.append(std::to_string(lineNumber));
    mensaje.append("] ");
    mensaje.append(description);
    mensaje.append(": ");
    mensaje.append(linea);
    archivo.close();
    return std::move(mensaje);
}