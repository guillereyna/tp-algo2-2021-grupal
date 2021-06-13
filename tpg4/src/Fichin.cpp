#include "Fichin.h"

// Preguntar!!
Fichin::Fichin(const Mapa& m) {
    _tablero = inicializarTablero();
    _mapa = &m;
    _partida = nullptr;
    _hayAlguien = false;
    _jugador = "";
    _ranking = string_map<Nat>();
}

Fichin::~Fichin() {
    if (_partida) delete(_partida);
}

void Fichin::nuevaPartida(const Jugador& j) {
    repoblarChocolates();
    _partida = new Partida(*_mapa, _tablero);
    _hayAlguien = true;
    _jugador = j;
}

void Fichin::mover(const Direccion d) {
    _partida->mover(d);
    if (_partida->gano() || _partida->perdio()) {
        _hayAlguien = false;
    }
    if (_partida->gano() &&
    (_ranking.count(_jugador) && _partida->cantMov() < _ranking.at(_jugador) || !_ranking.count(_jugador))) {
        _ranking.insert(make_pair(_jugador, _partida->cantMov()));
    }
}

const Mapa& Fichin::mapa() const {
    return *_mapa;
}

bool Fichin::alguienJugando() const {
    return _hayAlguien;
}

const Jugador& Fichin::jugadorActual() const {
    return _jugador;
}

const Partida& Fichin::partidaActual() const {
    return *_partida;
}

const string_map<Nat>& Fichin::ranking() const {
    return _ranking;
}

tuple<Jugador, Nat> Fichin::objetivo() const {
    ///Recorrer todo como se hace en borrar_todo() del trie e ir comparando las diferencias
    ///entre el puntaje del jugador actual y los demas, te quedas con la minima
}

void Fichin::repoblarChocolates()
{
    ///Rellenar chocolates
    for(auto i : _mapa->chocolates())
    {
        get<2>(_tablero[i.first][i.second]) = true;
    }
}

Tablero Fichin::inicializarTablero(){
    Tablero t(_mapa->largo(), vector<tuple<bool, bool, bool> >(_mapa->alto(), make_tuple(false, false, false)));

    for(auto i : _mapa->paredes())
    {
        get<0>(t[i.first][i.second]) = true;
    }

    for(auto i : _mapa->fantasmas())
    {
        get<1>(t[i.first][i.second]) = true;
    }
    for(auto i : _mapa->chocolates())
    {
        get<2>(t[i.first][i.second]) = true;
    }

}