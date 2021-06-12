#ifndef TP4_PACALGO2_PARTIDA_H
#define TP4_PACALGO2_PARTIDA_H

using namespace std;

#include "Mapa.h"
#include <vector>
#include <tuple>

typedef string direccion;
typedef vector<vector<tuple<bool,bool,bool>>> Tablero;
typedef pair<int, int> coordenada;

class Partida {
    public:
        // constructor
        Partida(const Mapa m, Tablero t);

        // destructor
        ~Partida();

        // Mueve el jugador, si es posible, hacia la dirección indicada
        void Mover(const direccion dir);

    private:
        Mapa* _mapa;
        Tablero* _tablero;
        coordenada _posActual;
        int _cantMovimientos;
        int _inmunidad;
        bool _perdio;
        bool _gano;
        // metodos auxiliares/privados
        coordenada moverCoordenada(coordenada c, const direccion dir);
        bool esMovimientoValido(const coordenada c, const direccion d);
        bool esPosicionValida(const coordenada c);
        bool seAsusta(const coordenada c);
        vector<coordenada> posicionesACheckear(const coordenada c);
};


#endif //TP4_PACALGO2_PARTIDA_H
