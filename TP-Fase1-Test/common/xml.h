//
// Created by fede on 15/09/18.
//

#ifndef TP_FASE1_TEST_XML_H
#define TP_FASE1_TEST_XML_H

#include "pugixml.hpp"
#include "Scene.h"
#include "../server/Model.h"
const char* get_log_level(pugi::xml_document &doc, pugi::xml_parse_result);
int get_level_width(pugi::xml_document &doc, pugi::xml_document &doc_default, int level, pugi::xml_parse_result result);
int get_level_height(pugi::xml_document &doc, pugi::xml_document &doc_default, int level, pugi::xml_parse_result result);
const char* get_level_background_path(pugi::xml_document& doc, pugi::xml_document& doc_default, int level, int numero_de_fondo, pugi::xml_parse_result result);
std::string get_error_message(const char*, const char* path, int pos, const char* description);
int get_cantidad_jugadores(pugi::xml_document &doc, pugi::xml_document &doc_default, pugi::xml_parse_result result);
void cargar_plataformas(pugi::xml_document &doc,Scene& scene, int level, int limite_vertical, int limite_horizontal);

#endif //TP_FASE1_TEST_XML_H
