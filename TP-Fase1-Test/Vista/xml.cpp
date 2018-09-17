//
// Created by fede on 15/09/18.
//

#include "xml.h"
#include "pugixml.hpp"
#include <string.h>

const char* get_log_level(pugi::xml_document &doc){
    return doc.first_child().child("debug").first_child().child_value();
}
int get_level_width(pugi::xml_document &doc, int level){
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    return doc.first_child().child("escenarios").child(nivel.c_str()).child("width").first_child().text().as_int();
}
int get_level_height(pugi::xml_document &doc, int level){
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    return doc.first_child().child("escenarios").child(nivel.c_str()).child("height").first_child().text().as_int();

}
const char* get_level_background_path(pugi::xml_document* doc, int level, int numero_de_fondo){
    std::string nivel = "nivel";
    std::string fondo = "fondo";
    nivel.append(std::to_string(level));
    fondo.append(std::to_string(numero_de_fondo));
    return doc->first_child().child("escenarios").child(nivel.c_str()).child(fondo.c_str()).first_child().text().as_string();
}