
#include <list>
#include "Comandos.h"
#include "Joiner.h"

#include <unistd.h>


	Joiner::Joiner(std::list<command*>& l) : list(l) {}
		
	void Joiner::run() {
			for(auto it = list.begin(); it != list.end(); ++it) {
				if((*it)->ended()) {		
					(*it)->join();
					delete(*it);
					list.erase(it);
					it = list.begin();
				}						
			}
	}
	
	Joiner::~Joiner(){}



	void Joiner::end() {
		for(auto it = list.begin(); it != list.end(); ++it) {		
			(*it)->join();
			delete(*it);
			list.erase(it);
			it = list.begin();		
		}	
	}
