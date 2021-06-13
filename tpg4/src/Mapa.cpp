#include "Mapa.h"

Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada,
           set<Coordenada> paredes, set<Coordenada> fantasmas, set<Coordenada> chocolates):
               _largo(largo), _alto(alto), _inicio(inicio), _llegada(llegada),
               _paredes(paredes), _fantasmas(fantasmas), _chocolates(chocolates){}

const Nat Mapa::largo() const {
    return _largo;
}

const Nat Mapa::alto() const {
    return _alto;
}

const Coordenada Mapa::inicio() const{
    return _inicio;
}

const Coordenada Mapa::llegada() const{
    return _llegada;
}

const set<Coordenada>& Mapa::chocolates() const{
    return _chocolates;
}

const set<Coordenada>& Mapa::fantasmas() const{
    return _fantasmas;
}

const set<Coordenada>& Mapa::paredes() const{
    return _paredes;
}