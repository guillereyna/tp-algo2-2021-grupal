#include "Fichin.h"

Fichin::Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes, set<Coordenada> fantasmas,
               set<Coordenada> chocolates) :
    _mapa(largo, alto, inicio, llegada, paredes, fantasmas, chocolates),
    _partida(nullptr),
    _hayAlguien(false),
    _jugador(""),
    _ranking(string_map<Nat>()),
    _rankingAux({}){
    _tablero = inicializarTablero();
}

Fichin::~Fichin() {
    if (_partida) delete(_partida);
}

void Fichin::nuevaPartida(const Jugador& j) {
    repoblarChocolates();
    if (_partida) delete(_partida);
    _partida = new Partida(_mapa, _tablero);
    _hayAlguien = true;
    _jugador = j;
}

void Fichin::mover(const Direccion d) {
    _partida->mover(d);
    if (_partida->gano() || _partida->perdio()) {
        _hayAlguien = false;
    }
    if (_partida->gano() &&  //si el jugador gano y esta en el ranking y supero su record, O si gano y no esta en el ranking
    ((_ranking.count(_jugador) && _partida->cantMov() < _ranking.at(_jugador)) || !_ranking.count(_jugador))) {
        _ranking.insert(make_pair(_jugador, _partida->cantMov()));
        _rankingAux[_jugador] = _partida->cantMov();
    }
}

const Mapa& Fichin::mapa() const {
    return _mapa;
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

const map<Jugador, Puntaje>& Fichin::ranking() const {
    return _rankingAux;
}

pair<Jugador, Nat> Fichin::objetivo() const {

    //Damos por hecho que el jugador ya está en el ranking
    Jugador jActual = _jugador;
    Puntaje pActual = _rankingAux.at(jActual);
    //Busco el maximo puntaje
    Jugador jMaximo = jActual;
    Puntaje pMaximo = pActual;
    for (pair<Jugador, Puntaje> p : _rankingAux) {
        if (p.second < pMaximo) {
            jMaximo = p.first;
            pMaximo = p.second;
        }
    }
    if(jMaximo == jActual)
        return make_pair(jActual, pActual);
    else {
        int diferencia = pActual - pMaximo;
        Jugador oponente = jMaximo;
        Puntaje pOponente = pMaximo;
        for (pair<Jugador, Puntaje> p : _rankingAux) {
            if ((pActual - p.second) < diferencia && (pActual - p.second) > 0) {
                oponente = p.first;
                pOponente = p.second;
            }
        }
        return make_pair(oponente, pOponente);
    }
}

void Fichin::repoblarChocolates() {
    for(auto i : _mapa.chocolates()) {
        get<2>(_tablero[i.first][i.second]) = true;
    }
}

Tablero Fichin::inicializarTablero() {
    Tablero t(_mapa.largo(), vector<tuple<bool, bool, bool> >(_mapa.alto(), make_tuple(false, false, false)));

    for(auto i : _mapa.paredes()) {
        get<0>(t[i.first][i.second]) = true;
    }

    for(auto i : _mapa.fantasmas()) {
        get<1>(t[i.first][i.second]) = true;
    }
    for(auto i : _mapa.chocolates()) {
        get<2>(t[i.first][i.second]) = true;
    }
    return t;
}