#include "Fichin.h"

Fichin::Fichin(const Mapa &m) {
    _tablero = inicializarTablero(m);
    _mapa = &m;
    _partida = nullptr;
    _hayAlguien = false;
    _jugador = "";
    _ranking = string_map();
}

Fichin::~Fichin() {}

void Fichin::nuevaPartida(const jugador& j) {
    repoblarChocolates(_tablero, _mapa);
    _partida = new Partida(*_mapa, _tablero);
    _hayAlguien = true;
    _jugador = j;
};
void repoblarChocolates(vector<vector<tuple<bool, bool, bool>>> &tablero, const Mapa* m)
{

}
void Fichin::mover(const direccion d) {
    _partida->mover(d);
    if (_partida->gano() || _partida->perdio()) {
        _hayAlguien = false;
    }
    if (_partida->gano() &&
    (_ranking.count(_jugador) && cantMov(_partida) < _ranking.at(_jugador) || !_ranking.count(_jugador))) {
        _ranking.insert(make_pair(_jugador, cantMov(_partida)));
    }
}

const Mapa Fichin::mapa() const {
    return _mapa
}

bool Fichin::alguienJugando() const {
    return _hayAlguien;
}

const jugador& Fichin::jugadorActual() const {}

const Partida& Fichin::partidaActual() const {
    return *_partida;
}

const string_map<unsigned int>& Fichin::ranking() const {}

tuple<jugador, unsigned int> Fichin::objetivo() const {

}