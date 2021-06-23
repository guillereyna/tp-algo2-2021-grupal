#include "aed2_Fichin.h"

aed2_Fichin::aed2_Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
set<Coordenada> fantasmas, set<Coordenada> chocolates) :
    _fichin(largo, alto, traducirCoordenada(inicio), traducirCoordenada(llegada),
            traducirConjunto(paredes), traducirConjunto(fantasmas),
            traducirConjunto(chocolates)){}

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
    return devolverCoordenada(_fichin.partidaActual().jugador());
}

Nat aed2_Fichin::cantidadMovimientos() const {
    return _fichin.partidaActual().cantMov();
}

Nat aed2_Fichin::inmunidad() const {
    return _fichin.partidaActual().inmunidad();
}

Nat aed2_Fichin::largo() const {
    return _fichin.mapa().largo();
}

Nat aed2_Fichin::alto() const {
    return _fichin.mapa().alto();
}

Coordenada aed2_Fichin::inicio() const {
    return devolverCoordenada(_fichin.mapa().inicio());
}

Coordenada aed2_Fichin::llegada() const {
    return devolverCoordenada(_fichin.mapa().llegada());
}

set<Coordenada> aed2_Fichin::paredes() const {
    return devolverConjunto(_fichin.mapa().paredes());
}

set<Coordenada> aed2_Fichin::fantasmas() const {
    return devolverConjunto(_fichin.mapa().fantasmas());
}

set<Coordenada> aed2_Fichin::chocolatesIniciales() const {
    return devolverConjunto(_fichin.mapa().chocolates());
}

set<Coordenada> aed2_Fichin::chocolatesActuales() const {
    return devolverConjunto(_fichin.partidaActual().chocolatesActuales());
}

const Coordenada traducirCoordenada(Coordenada c){
    return Coordenada(c.first-1,c.second-1);
}

const Coordenada devolverCoordenada(Coordenada c){
    return Coordenada(c.first+1,c.second+1);
}

const set<Coordenada> traducirConjunto(set<Coordenada> conj){
    set<Coordenada> res;
    for (auto elem : conj){
        res.insert(traducirCoordenada(elem));
    }
    return res;
}

const set<Coordenada> devolverConjunto(set<Coordenada> conj){
    set<Coordenada> res;
    for (auto elem : conj){
        res.insert(devolverCoordenada(elem));
    }
    return res;
}