//
// Created by fede on 15/09/18.
//

#include "xml.h"
#include "pugixml.hpp"
#include <string.h>
#include <iostream>

const char* get_log_level(pugi::xml_document &doc){
    return doc.first_child().child("debug").first_child().child_value();
}
int get_level_width(pugi::xml_document &doc, pugi::xml_document &doc_default, int level){
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    int original = doc.first_child().child("escenarios").child(nivel.c_str()).child("width").first_child().text().as_int();
    if (original) return original;
    else return doc_default.first_child().child("escenarios").child(nivel.c_str()).child("width").first_child().text().as_int();
}
int get_level_height(pugi::xml_document &doc, pugi::xml_document &doc_default, int level){
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    int original = doc.first_child().child("escenarios").child(nivel.c_str()).child("height").first_child().text().as_int();
    if (original) return original;
    else return doc_default.first_child().child("escenarios").child(nivel.c_str()).child("height").first_child().text().as_int();

}
const char* get_level_background_path(pugi::xml_document* doc, pugi::xml_document* doc_default, int level, int numero_de_fondo){
    std::string nivel = "nivel";
    std::string fondo = "fondo";
    nivel.append(std::to_string(level));
    fondo.append(std::to_string(numero_de_fondo));
    const char* original = doc->first_child().child("escenarios").child(nivel.c_str()).child(fondo.c_str()).first_child().text().as_string();
    if (original) return original;
    else return doc_default->first_child().child("escenarios").child(nivel.c_str()).child(fondo.c_str()).first_child().text().as_string();
}
void cargar_plataformas(pugi::xml_document &doc, Model &modelo, int level, int limite_vertical, int limite_horizontal){
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    pugi::xml_node config = doc.first_child().child("escenarios").child(nivel.c_str());
    for (pugi::xml_node plataforma = config.child("plataforma"); plataforma; plataforma = plataforma.next_sibling("plataforma")){
        int xi = plataforma.child("xi").first_child().text().as_int();
        int xf = plataforma.child("xf").first_child().text().as_int();
        int y = plataforma.child("y").first_child().text().as_int();
        if (xi >= 0 && xf >=  0 && y >= 0 && xi < xf && xi < limite_horizontal && xf < limite_horizontal && y < limite_vertical) {
            modelo.addPlataform(xi, xf, y);
        }
    }

}