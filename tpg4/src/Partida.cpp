#include "Partida.h"

// constructor
Partida::Partida(const Mapa& m, Tablero& t): _posActual(m.inicio()), _cantMovimientos(0), _inmunidad(0), _gano(false), _perdio(false),
    _mapa(m), _tablero(t) {
    if (esChocolate(_posActual)){
        _inmunidad = 10;
        get<2>(_tablero[_posActual.first][_posActual.second]) = false;
    }
    if (_inmunidad == 0 && seAsusta(_posActual)) _perdio = true;
}

// destructor
Partida::~Partida(){
}

// mover
void Partida::mover(const Direccion dir) {
    if(_gano || _perdio || !esMovimientoValido(_posActual, dir)) return;

    _posActual = moverCoordenada(_posActual, dir);
    ++_cantMovimientos;
    if (_inmunidad > 0) --_inmunidad;
    if (esChocolate(_posActual)){
        _inmunidad = 10;
        get<2>(_tablero[_posActual.first][_posActual.second]) = false;
    }
    if (_inmunidad == 0 && seAsusta(_posActual)) _perdio = true;
    else if(_posActual == _mapa.llegada()) _gano = true;
}

const Mapa& Partida::mapa() const{
    return _mapa;
}

const Coordenada Partida::jugador() const{
    return _posActual;
}

const Nat Partida::cantMov() const{
    return _cantMovimientos;
}

const Nat Partida::inmunidad() const{
    return _inmunidad;
}

const bool Partida::gano() const{
    return _gano;
}

const bool Partida::perdio() const{
    return _perdio;
}

// métodos auxiliares
Coordenada Partida::moverCoordenada(Coordenada c, const Direccion dir){
    Coordenada res;

    if (dir == DERECHA) res = Coordenada(c.first + 1, c.second);

    if (dir == IZQUIERDA) res = Coordenada(c.first - 1, c.second);

    if (dir == ARRIBA) res = Coordenada(c.first, c.second + 1);

    if (dir == ABAJO) res = Coordenada(c.first, c.second - 1);

    return res;
};

bool Partida::esMovimientoValido(Coordenada  c, const Direccion dir) {
    return esPosicionValida(moverCoordenada(c, dir));
}

bool Partida::esPosicionValida(const Coordenada c) const {
    bool res = false;

    if (enRango(c)){
        res = !esPared(c);
    }

    return res;
}

bool Partida::seAsusta(const Coordenada c) const {
    bool res = false;
    vector<Coordenada> posACheckear = posicionesACheckear(c);

    for (int i = 0; i < posACheckear.size() && !res; ++i) {
        if(esFantasma(posACheckear[i])){
            res = true;
        }
    }

    return res;
}

vector<Coordenada> Partida::posicionesACheckear(const Coordenada c) const {
    vector<Coordenada> res;

    for (int i = -3; i <= 3; i++){
        for (int j = -(3-abs(i)); j <= (3-abs(i)); j++){
           if (enRango(Coordenada(c.first + i, c.second + j)))
               res.push_back(Coordenada(c.first + i, c.second + j));
        }
    }
    return res;
}

bool Partida::enRango(Coordenada c) const {
    return 0 <= c.first && c.first < _mapa.largo() && 0 <= c.second && c.second < _mapa.alto();
}

bool Partida::esPared(Coordenada c) const {
    return get<0>(_tablero[c.first][c.second]);
}

bool Partida::esFantasma(Coordenada c) const {
    return get<1>(_tablero[c.first][c.second]);
}
bool Partida::esChocolate(Coordenada c) const {
    return get<2>(_tablero[c.first][c.second]);
}

set<Coordenada> Partida::chocolatesActuales() const {
    set<Coordenada> res;
    for (auto pos : (_mapa).chocolates()){
        if (esChocolate(pos)){
            res.insert(pos);
        }
    }
    return res;
}
