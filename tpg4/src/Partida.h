#ifndef TP4_PACALGO2_PARTIDA_H
#define TP4_PACALGO2_PARTIDA_H

#include "Mapa.h"
#include <vector>
#include <tuple>

using namespace std;

typedef vector<vector<tuple<bool,bool,bool>>> Tablero;

class Partida {
    public:
        // constructor
        Partida(const Mapa m, Tablero t);

        // destructor
        ~Partida();

        // Mueve el jugador, si es posible, hacia la dirección indicada
        void mover(const Direccion dir);

        const Mapa& mapa() const;
        const Coordenada jugador() const;
        const Nat cantMov() const;
        const Nat inmunidad() const;
        const bool gano() const;
        const bool perdio() const;

        set<Coordenada> chocolatesActuales() const;

    private:
        Mapa* _mapa;
        Tablero* _tablero;
        Coordenada _posActual;
        int _cantMovimientos;
        int _inmunidad;
        bool _perdio;
        bool _gano;
        // metodos auxiliares/privados
        Coordenada moverCoordenada(Coordenada c, const Direccion dir);
        bool esMovimientoValido(const Coordenada c, const Direccion d);
        bool esPosicionValida(const Coordenada c) const;
        bool seAsusta(const Coordenada c) const;
        vector<Coordenada> posicionesACheckear(const Coordenada c) const;
        bool esPared(Coordenada c) const;
        bool esFantasma(Coordenada c) const;
        bool esChocolate(Coordenada c) const;
};

bool enRango(int c0, int c1, int limite0, int limite1);

#endif //TP4_PACALGO2_PARTIDA_H
