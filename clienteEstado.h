#ifndef ESTADO_H
#define ESTADO_H

enum DIBUJADORES
{
    DIBUJAR_LOBBY_HOST = 0,
    DIBUJAR_LOBBY_NOHOST = 1,
    DIBUJAR_MAPA_IN_TURNO = 2,
    DIBUJAR_MAPA_NOIN_TURNO = 3,
    DIBUJAR_FINAL = 4
};

class Estado {
private:	
	int i;
public:
	Estado(int num) : i(num){}
	
	void set(int num){
		i = num;
	}
	
	int get(){
		return i;
	}

};

#endif