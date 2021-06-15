#include "Partida.h"

// constructor
Partida::Partida(const Mapa m, const Tablero t): _posActual(m.inicio()), _cantMovimientos(0), _inmunidad(0), _gano(false), _perdio(false) {
    _mapa = new Mapa(m);        // guille: estas me hacen ruido (si estamos copiando las instancias
    _tablero = new Tablero(t);  // se nos va la complejidad de nuevapartida)
}

// destructor
Partida::~Partida(){
    delete(_mapa);
    delete(_tablero);
}

// mover
void Partida::mover(const Direccion dir) {
    if(_gano || _perdio || !esMovimientoValido(_posActual, dir)) return;
                                                //^ aca agregue el primer parametro

    _posActual = moverCoordenada(_posActual, dir);
    ++_cantMovimientos;
    if (_inmunidad > 0) --_inmunidad;
    if (esChocolate(_posActual)){
        _inmunidad = _inmunidad + 10;
        get<2>((*_tablero)[_posActual.first][_posActual.second]) = false;
    }
    if (_inmunidad == 0 && seAsusta(_posActual)) _perdio = true;
    else if(_posActual == _mapa->llegada()) _gano = true;
}

const Mapa& Partida::mapa() const{
    return *_mapa;
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

// metodos auxiliares
Coordenada Partida::moverCoordenada(Coordenada c, const Direccion dir){
    Coordenada res;

    if (dir == DERECHA) res = make_pair(c.first + 1, c.second);

    if (dir == IZQUIERDA) res = make_pair(c.first - 1, c.second);

    if (dir == ARRIBA) res = make_pair(c.first, c.second - 1);

    if (dir == ABAJO) res = make_pair(c.first, c.second + 1);

    return res;
};

bool Partida::esMovimientoValido(Coordenada  c, const Direccion dir) {
    return esPosicionValida(moverCoordenada(c, dir));
}

bool Partida::esPosicionValida(const Coordenada c) {
    bool res = false;

    if (enRango(c.first, c.second, _mapa->largo(), _mapa->alto())){
        res = !esPared(c);
    }

    return res;
}

bool Partida::seAsusta(const Coordenada c) {
    bool res = false;
    vector<Coordenada> posACheckear = posicionesACheckear(c);

    for (int i = 0; i < posACheckear.size() && !res; ++i) {
        if( enRango(posACheckear[i].first, posACheckear[i].second, _mapa->largo(), _mapa->alto())
          && esFantasma(posACheckear[i])){
            res = true;
        }
        ++i;
    }

    return res;
}

vector<Coordenada> Partida::posicionesACheckear(const Coordenada c){
    vector<Coordenada> res;
    int i = 3;
    int j = 0;
    Coordenada c0;
    Coordenada c1;
    Coordenada c2;
    Coordenada c3;

    while (i >= 0 && j <= 3){                            // i=3,j=0 i=2,j=1 i=1,j=2 i=0,j=3 ¡BORRAR!
        c0 = make_pair(c.first + i, c.second + j); // (+3,+0) (+2,+1) (+1,+2) (+0,+3)
        c1 = make_pair(c.first + i, c.second - j); // (+3,-0) (+2,-1) (+1,-2) (+0,-3)
        c2 = make_pair(c.first - i, c.second + j); // (-3,+0) (-2,+1) (-1,+2) (-0,+3)
        c3 = make_pair(c.first - i, c.second - j); // (-3,-0) (-2,-1) (-1,-2) (-0,-3)

        res.push_back(c0);
        if (i > 0 && j > 0) res.push_back(c1);
        if (i > 0 && j > 0) res.push_back(c2);
        res.push_back(c3);

        --i;
        ++j;
    }

    return res;
}

bool enRango(int c0, int c1, int limite0, int limite1){
    return 0<=c0 && c0<limite0 && 0<=c1 && c1<limite1;
}

bool Partida::esPared(Coordenada c){
    return get<0>((*_tablero)[c.first][c.second]);
}

bool Partida::esFantasma(Coordenada c){
    return get<1>((*_tablero)[c.first][c.second]);
}
bool Partida::esChocolate(Coordenada c){
    return get<2>((*_tablero)[c.first][c.second]);
}

set<Coordenada> Partida::chocolatesActuales() const { //es horrible esta funcion ¯\_(ツ)_/¯
    set<Coordenada> res;
    for (auto choco : (*_mapa).chocolates()){
        if (get<2>((*_tablero)[choco.first][choco.second])){
            res.insert(Coordenada(choco.first, choco.second));
        }
    }
    return res;
}
