#ifndef TP4_PACALGO2_MAPA_H
#define TP4_PACALGO2_MAPA_H
#include "Tipos.h"
#include <set>

class Mapa {
public:

    Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes, set<Coordenada> fantasmas,
         set<Coordenada> chocolates);

    const Nat largo() const;
    const Nat alto() const;
    const Coordenada inicio() const;
    const Coordenada llegada() const;
    const set<Coordenada>& chocolates() const;
    const set<Coordenada>& paredes() const;
    const set<Coordenada>& fantasmas() const;

private:
    Nat _largo, _alto;
    Coordenada _inicio, _llegada;
    set<Coordenada> _paredes, _fantasmas, _chocolates;
};


#endif //TP4_PACALGO2_MAPA_H
