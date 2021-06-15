#include "aed2_Fichin.h"

aed2_Fichin::aed2_Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
set<Coordenada> fantasmas, set<Coordenada> chocolates) :
    _mapa(Mapa(largo, alto, inicio, llegada, paredes, fantasmas, chocolates)),
    _fichin(Fichin(_mapa)){}

void aed2_Fichin::nuevaPartida(Jugador j){
    _fichin.nuevaPartida(j);
}

ResultadoMovimiento aed2_Fichin::mover(Direccion d){
    _fichin.mover(d);
    if (_fichin.partidaActual().gano()) {
        return GANO;
    }
    else if (_fichin.partidaActual().perdio()) {
        return PERDIO;
    }
    else {
        return SIGUE;
    }
}

bool aed2_Fichin::alguienJugando() const {
    return _fichin.alguienJugando();
}

Jugador aed2_Fichin::jugadorActual() const {
    return _fichin.jugadorActual();
}

map<Jugador, Puntaje> aed2_Fichin::ranking() const{
    return _fichin.ranking();
}

pair<Jugador, Puntaje> aed2_Fichin::objetivo() const{
    return _fichin.objetivo();
}

Coordenada aed2_Fichin::jugador() const {
    return _fichin.partidaActual().jugador(); //quizas deberia preguntar si hay alguien jugando
}

Nat aed2_Fichin::cantidadMovimientos() const {
    return _fichin.partidaActual().cantMov();
}

Nat aed2_Fichin::inmunidad() const {
    return _fichin.partidaActual().inmunidad();
}

Nat aed2_Fichin::largo() const {
    return _mapa.largo();
}

Nat aed2_Fichin::alto() const {
    return _mapa.alto();
}

Coordenada aed2_Fichin::inicio() const {
    return _mapa.inicio();
}

Coordenada aed2_Fichin::llegada() const {
    return _mapa.llegada();
}

set<Coordenada> aed2_Fichin::paredes() const {
    return _mapa.paredes();
}

set<Coordenada> aed2_Fichin::fantasmas() const {
    return _mapa.fantasmas();
}

set<Coordenada> aed2_Fichin::chocolatesIniciales() const {
    return _mapa.chocolates();
}

set<Coordenada> aed2_Fichin::chocolatesActuales() const {
    return _fichin.partidaActual().chocolatesActuales();
}