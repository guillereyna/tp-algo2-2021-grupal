#include "Partida.h"

// constructor
Partida::Partida(const Mapa m, const Tablero t): _cantMovimientos(0), _inmunidad(0), _gano(false), _perdio(false) {
    _mapa = new Mapa(m);
    _tablero = new Tablero(t);
}

// destructor
Partida::~Partida(){
    // Completar alfinal
}

// mover
void Partida::Mover(const Direccion dir) {
    if(_gano || _perdio || !esMovimientoValido(_posActual, dir)) return;
                                                //^ aca agregue el primer parametro

    _posActual = moverCoordenada(_posActual, dir);
    ++_cantMovimientos;
    if (_inmunidad > 0) --_inmunidad;
    if (esChocolate(_posActual)){ //todo: implementar esChocolate
        _inmunidad = _inmunidad + 10;
        // NO ME DEJA ASIGNAR UNA TUPLA A UNA POSICION DEL TABLERO O ACTUALIZAR UN VALOR DE LA TUPLA EN LA POSICION
        (*_tablero)[_posActual.first][_posActual.second] = make_tuple(false, false, false);
        // guille: me parece que es porque no inicializamos el tablero ? (falta definirlo)
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
Coordenada moverCoordenada(Coordenada c, const Direccion dir){
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
        res = esPared(c); //todo: implementar esPared
    }

    return res;
}

bool Partida::seAsusta(const Coordenada c) {
    bool res = false;
    vector<Coordenada> posACheckear = posicionesACheckear(c);

    for (int i = 0; i < posACheckear.size() && !res; ++i) {
        if( enRango(posACheckear[i].first, posACheckear[i].second, _mapa->largo, _mapa->alto) /*&&
             _tablero[posACheckear[i].first][posACheckear[i].second].third*/){
            res = true;
        }
        ++i;
    }

    return res;
}

vector<Coordenada> posicionesACheckear(const Coordenada c){
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

