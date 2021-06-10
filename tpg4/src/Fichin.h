#ifndef FICHIN_H
#define FICHIN_H

#include "Mapa.h"
#include "Partida.h"
#include "string_map.h"
#include <vector>

typedef string_map<unsigned int> ranking;
typedef string jugador;
typedef string direccion;

class Fichin {
public:
    // Constructor.
    Fichin(const Mapa&);

    // Destructor.
    ~Fichin();

    // Inicia una nueva partida para el jugador.
    void nuevaPartida(const jugador&);

    // Mueve al jugador en determinada dirección.
    void mover(const direccion);

    // Devuelve una referencia inmutable al mapa.
    const Mapa mapa() const;

    // Devuelve true si hay una partida en curso.
    bool alguienJugando() const;

    // Devuelve una referencia inmutable al jugador actual.
    const jugador jugadorActual() const;

    // Devuelve una referencia inmutable a la partida actual.
    const Partida partidaActual() const;

    // Devuelve una referencia inmutable al ranking.
    const ranking ranking() const;

    // Devuelve una tupla con el nombre y puntaje del jugador que
    // supera inmediatamente al jugador actual, si es qe existe.
    tuple<jugador, unsigned int> objetivo() const;

private:
    vector<vector<tuple<bool, bool, bool>>> _tablero;
    Mapa* _mapa;
    Partida* _partida;
    bool _hayAlguien;
    jugador _jugador;
    // ranking _ranking;
};


#endif
