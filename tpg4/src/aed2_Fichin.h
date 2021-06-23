#ifndef AED2_FICHIN_H
#define AED2_FICHIN_H

#include "Tipos.h"
#include "Fichin.h"

// Convierten las coordenadas que usa la cátedra (indexadas desde 1) a coordenadas
// que usa nuestra implementación (indexadas desde 0)
const Coordenada traducirCoordenada(Coordenada c);
const set<Coordenada> traducirConjunto(set<Coordenada> conj);
// y viceversa
const Coordenada devolverCoordenada(Coordenada c);
const set<Coordenada> devolverConjunto(set<Coordenada> conj);

class aed2_Fichin {
public:
    aed2_Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
                set<Coordenada> fantasmas, set<Coordenada> chocolates);

    void nuevaPartida(Jugador j);

    // IMPORTANTE: Debe devolver:
    // - GANO si al mover se gana la partida
    // - PERDIO si al mover se pierde la partida
    // - SIGUE en cualquier otro caso
    ResultadoMovimiento mover(Direccion d);

    bool alguienJugando() const;

    Jugador jugadorActual() const;

    map<Jugador, Puntaje> ranking() const;

    pair<Jugador, Puntaje> objetivo() const;

    Coordenada jugador() const;

    Nat cantidadMovimientos() const;

    Nat inmunidad() const;

    Nat largo() const;

    Nat alto() const;

    Coordenada inicio() const;

    Coordenada llegada() const;

    set<Coordenada> paredes() const;

    set<Coordenada> fantasmas() const;

    set<Coordenada> chocolatesIniciales() const;

    set<Coordenada> chocolatesActuales() const;

private:
    Fichin _fichin;
};

#endif // AED2_FICHIN_H
