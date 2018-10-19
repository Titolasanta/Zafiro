#include <stdio.h>
#include <string>
#include <list>
#include "Thread.h"
#include <iostream>
#include "Collector.h"
#include "../common/Socket.h"
#include "ModelProtocol.h"
#include "Sender.h"
#include "Model.h"
#include "../common/Exception.h"
#include "Interpreter.h"
#include "../common/pugixml.hpp"
#include "../common/Logger.h"
#include "../common/xml.h"
#include "../server/xmlServer.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"
#define PATH_XML_ORIGINAL "../Archivos/configuracion.xml"
#define PATH_XML_DEFAULT "../Archivos/default.xml"

using std::string;
using std::cout;
using std::list;

pugi::xml_document* gXML_doc[2];
Logger *gplogger;
pugi::xml_parse_result *gXML_parse_result;

int main(int argc, char *argv[]) {


	pugi::xml_document doc;
	pugi::xml_document doc_default;
	pugi::xml_parse_result result = doc.load_file(PATH_XML_ORIGINAL);
	pugi::xml_parse_result result_default = doc_default.load_file(PATH_XML_DEFAULT);


	const char* modo;
	if (argc > 1 ) {
		modo = argv[1];
	}
	else if (!(result || result_default)) modo = "DEBUG";
	else modo = get_log_level(doc, result);
	Logger logger(modo,get_log_level(doc_default, result_default));

	if (!(result)) {
		std::string mensaje = get_error_message("Error al cargar el archivo XML: ", PATH_XML_ORIGINAL, result.offset, result.description());
		logger.log(1, mensaje.c_str());
		if (!result_default) {
			mensaje = get_error_message("Error al cargar el archivo XML por defecto: ", PATH_XML_DEFAULT, result_default.offset, result_default.description());
			logger.log(1, mensaje.c_str());
			return 0;
		}
		logger.log(1, "Se cargó un archivo por defecto");
	}


	gplogger = &logger;

	gXML_doc[0] = &doc;
	gXML_doc[1] = &doc_default;
	gXML_parse_result = &result;



	try {
	    char port[5] = "8081";
		Socket skt(port, 0);
		skt.start_to_listen();

		Scene scene(get_cantidad_jugadores(doc, doc_default, result));
        Model model(1);

		if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene,model, 1, model.getLevelHeight(), model.getLevelWidth());     //No tenia idea de como hacer este
		else cargar_plataformas(*gXML_doc[1],scene, model, 1, model.getLevelHeight(), model.getLevelWidth()); //chequeo de otra manera

        std::queue<char> queue;
        std::mutex mutex;

	    list<ModelProtocol> pList;

    	Collector colector(skt,pList,queue,mutex,model);
    	Interpreter interpreter(pList,queue,mutex,model,scene);
    	Sender sender(pList,scene,model);

    	colector.start();
    	interpreter.start();
    	sender.start();

    	while(true) {
	    	if('q' == getchar())
		    	break;
	    }
	    colector.end();
        interpreter.end();
        sender.end();
	    colector.join();
        interpreter.join();
        sender.join();       
        for (auto it = pList.begin(); it != pList.end(); it++) {
            it->end();
            it->join();
        }


	} catch (OSError e) {
		cout << "what: " << e.what() << "\n";
	}catch (Finalizo_conexion e) {
		//todo ok
	}catch(...) {
		cout << "Excepcion desconocida\n.";
	}

	return 0;
}
