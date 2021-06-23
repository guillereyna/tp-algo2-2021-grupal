#ifndef FICHIN_H
#define FICHIN_H

#include "Tipos.h"
#include "Mapa.h"
#include "Partida.h"
#include "string_map.h"
#include <vector>
#include <tuple>

class Fichin {
public:
    // Constructor.
    Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes, set<Coordenada> fantasmas,
           set<Coordenada> chocolates); //aclarar cambios del diseño

    // Destructor.
    ~Fichin();

    // Inicia una nueva partida para el jugador.
    void nuevaPartida(const Jugador&);

    // Mueve al jugador en determinada dirección.
    void mover(const Direccion);

    // Devuelve una referencia inmutable al mapa.
    const Mapa& mapa() const;

    // Devuelve true si hay una partida en curso.
    bool alguienJugando() const;

    // Devuelve una referencia inmutable al jugador actual.
    const Jugador& jugadorActual() const;

    // Devuelve una referencia inmutable a la partida actual.
    const Partida& partidaActual() const;

    // Devuelve una referencia inmutable al ranking.
    const map<Jugador, Puntaje> ranking() const;

    // Devuelve una tupla con el nombre y puntaje del jugador que
    // supera inmediatamente al jugador actual, si es que existe.
    pair<Jugador, Nat> objetivo() const;

private:
    Tablero _tablero;
    const Mapa _mapa;
    Partida* _partida;
    bool _hayAlguien;
    Jugador _jugador;
    string_map<Puntaje> _ranking;
    void repoblarChocolates();
    Tablero inicializarTablero();
};


#endif
