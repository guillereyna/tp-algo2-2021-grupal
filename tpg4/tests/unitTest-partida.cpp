#include "gtest-1.8.1/gtest.h"
#include "../src/Partida.h"

 Tablero inicializarTablero(const Mapa &_mapa){
    Tablero t(_mapa.largo(), vector<tuple<bool, bool, bool> >(_mapa.alto(), make_tuple(false, false, false)));

    for(auto i : _mapa.paredes())
    {
        get<0>(t[i.first][i.second]) = true;
    }

    for(auto i : _mapa.fantasmas())
    {
        get<1>(t[i.first][i.second]) = true;
    }
    for(auto i : _mapa.chocolates())
    {
        get<2>(t[i.first][i.second]) = true;
    }
    return t;
}

set<Coordenada> chocolates = { make_pair(4,2), make_pair(1,3), make_pair(6,4), make_pair(9,6), make_pair(3,7) };
set<Coordenada> paredes = { make_pair(2,0), make_pair(2,1), make_pair(2,2),
                            make_pair(2,8), make_pair(3,8), make_pair(4,8),
                            make_pair(6,6), make_pair(6,7), make_pair(6,8) };
set<Coordenada> fantasmas = { make_pair(0, 7), make_pair(4,9), make_pair(7,0), make_pair(8,3) };

const Mapa mapa = Mapa(10, 10, make_pair(0, 0), make_pair(9, 9), paredes, fantasmas, chocolates);

Tablero tablero = inicializarTablero(mapa);

/* REPRESENTACION DEL MAPA CREADO PARA LA PARTIDA: i = inicio, f = fin, c = chocolate, | = pared, x = fantasma
   i - | - - - - x - -
   - - | - - - - - - -
   - - | - c - - - - -
   - c - - - - - - x -
   - - - - - - c - - - (f, c) / (c, f)
   - - - - - - - - - -
   - - - - - - | - - c
   x - - c - - | - - -
   - - | | | - | - - -
   - - - - x - - - - f
*/

TEST(Partida, nueva_partida) {
    Partida p(mapa, tablero);

    EXPECT_FALSE(p.gano());
    EXPECT_FALSE(p.perdio());
    EXPECT_EQ(p.mapa(), mapa);
    EXPECT_EQ(p.cantMov(), 0);
    EXPECT_EQ(p.inmunidad(), 0);
    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);

    for (Coordenada chocolate : p.chocolatesActuales()){
        EXPECT_EQ(chocolates.count(chocolate), 1);
    }
}

TEST(Partida, mover_partida) {
    Partida p(mapa, tablero);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);

    p.mover(ABAJO);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 1);
    EXPECT_EQ(p.cantMov(), 1);
}

TEST(Partida, mover_hacia_pared) {
    Partida p(mapa, tablero);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);

    p.mover(DERECHA);

    EXPECT_EQ(p.jugador().second, 1);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 1);

    p.mover(DERECHA);

    EXPECT_EQ(p.jugador().second, 1);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 1);
}

TEST(Partida, mover_fuera_del_mapa) {
    Partida p(mapa, tablero);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);

    p.mover(ARRIBA);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);

    p.mover(IZQUIERDA);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);
}

TEST(Partida, comer_chocolate) {
    Partida p(mapa, tablero);

    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(DERECHA);

    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 1);
    EXPECT_EQ(p.cantMov(), 4);
    EXPECT_EQ(p.inmunidad(), 10);
    EXPECT_EQ(p.chocolatesActuales().size(), chocolates.size()-1);
    EXPECT_EQ(p.chocolatesActuales().count(p.jugador()), 0);

    p.mover(DERECHA);
    p.mover(IZQUIERDA);
    p.mover(DERECHA);
    p.mover(IZQUIERDA);
    p.mover(DERECHA);
    p.mover(IZQUIERDA);
    p.mover(DERECHA);
    p.mover(IZQUIERDA);
    p.mover(DERECHA);
    p.mover(IZQUIERDA);

    EXPECT_EQ(p.inmunidad(), 0);
}

TEST(Partida, comer_chocolate_y_luego_otro) {
    Partida p(mapa, tablero);

    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(DERECHA);

    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 1);
    EXPECT_EQ(p.cantMov(), 4);
    EXPECT_EQ(p.inmunidad(), 10);
    EXPECT_EQ(p.chocolatesActuales().size(), chocolates.size()-1);
    EXPECT_EQ(p.chocolatesActuales().count(p.jugador()), 0);

    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(ARRIBA);

    EXPECT_EQ(p.jugador().second, 2);
    EXPECT_EQ(p.jugador().first, 4);
    EXPECT_EQ(p.cantMov(), 8);
    EXPECT_EQ(p.inmunidad(), 16);
    EXPECT_EQ(p.chocolatesActuales().size(), chocolates.size()-2);
    EXPECT_EQ(p.chocolatesActuales().count(p.jugador()), 0);
}

TEST(Partida, asustarse) {
    Partida p(mapa, tablero);

    EXPECT_EQ(p.jugador().second, 0);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 0);

    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);

    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 4);
    EXPECT_FALSE(p.gano());
    EXPECT_TRUE(p.perdio());

    p.mover(ABAJO);
    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 4);
}

TEST(Partida, acercarse_a_fantasma_con_inmunidad) {
    Partida p(mapa, tablero);

    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(DERECHA);

    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 1);
    EXPECT_EQ(p.cantMov(), 4);
    EXPECT_EQ(p.inmunidad(), 10);
    EXPECT_EQ(p.chocolatesActuales().size(), chocolates.size()-1);
    EXPECT_EQ(p.chocolatesActuales().count(p.jugador()), 0);

    p.mover(IZQUIERDA);
    p.mover(ABAJO);

    EXPECT_EQ(p.jugador().second, 3);
    EXPECT_EQ(p.jugador().first, 0);
    EXPECT_EQ(p.cantMov(), 4);
    EXPECT_EQ(p.inmunidad(), 8);
    EXPECT_FALSE(p.gano());
    EXPECT_FALSE(p.perdio());
}

TEST(Partida, gano_xD) {
    Partida p(mapa, tablero);

    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(DERECHA);
    p.mover(ABAJO);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(ABAJO);
    p.mover(DERECHA);
    p.mover(DERECHA);
    p.mover(ABAJO);
    p.mover(ABAJO);

    EXPECT_EQ(p.jugador().second, 9);
    EXPECT_EQ(p.jugador().first, 9);
    EXPECT_TRUE(p.gano());
    EXPECT_FALSE(p.perdio());
    EXPECT_EQ(p.cantMov(), 18);
    EXPECT_EQ(p.inmunidad(), 7);
    EXPECT_EQ(p.chocolatesActuales().size(), chocolates.size()-2);
}
