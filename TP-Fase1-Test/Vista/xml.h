//
// Created by fede on 15/09/18.
//

#ifndef TP_FASE1_TEST_XML_H
#define TP_FASE1_TEST_XML_H

#include <Modelo/Model.h>
#include "pugixml.hpp"

const char* get_log_level(pugi::xml_document &doc);
int get_level_width(pugi::xml_document &doc, int level);
int get_level_height(pugi::xml_document &doc, int level);
const char* get_level_background_path(pugi::xml_document* doc, int level, int numero_de_fondo);
void cargar_plataformas(pugi::xml_document &doc, Model modelo, int level);

#endif //TP_FASE1_TEST_XML_H
