#include "gtest-1.8.1/gtest.h"
#include "../src/Fichin.h"

void realizarMovimientos(Fichin &f, const string &movs) {
    for (const char &m : movs) {
        if (m == 'A') {
            f.mover(ARRIBA);
        } else if (m == 'B') {
            f.mover(ABAJO);
        } else if (m == 'I') {
            f.mover(IZQUIERDA);
        } else if (m == 'D') {
            f.mover(DERECHA);
        }
    }
}

TEST(fichin, crearFichin) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    
    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichin, nuevaPartida) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";
    
    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);
    
    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ(fichin.jugadorActual(), jugador);
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichin, moverJugador) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);
    fichin.mover(DERECHA);
    fichin.mover(ABAJO);
    fichin.mover(IZQUIERDA);
    fichin.mover(ARRIBA);

    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ(fichin.jugadorActual(), jugador);
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichin, ganarPartida) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);
    for (int i=0; i < 7; i++) {
        fichin.mover(DERECHA);
        fichin.mover(ARRIBA);
    }    

    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_FALSE(fichin.ranking().empty());
    EXPECT_EQ(fichin.ranking().at(jugador), 14);
}

TEST(fichin, perderPartida) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {{0, 7}};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);

    for (int i=0; i < 7; i++) {
        fichin.mover(ARRIBA);
    }

    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichin, inmunidad) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {{0, 1}};
    set<Coordenada> fantasmas = {{0, 7}};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);

    for (int i=0; i < 7; i++) {
        fichin.mover(ARRIBA);
    }

    EXPECT_TRUE(fichin.alguienJugando());
}

TEST(fichin, chocarConPared) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {{6, 7}, {7, 6}};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    fichin.nuevaPartida(jugador);

    for (int i=0; i < 7; i++) {
        fichin.mover(DERECHA);
        fichin.mover(ARRIBA);
    }

    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichin, nuevoRecord) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);

    ///Partida Luli, 28 pasos
    fichin.nuevaPartida(jugador);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_EQ(fichin.ranking().at(jugador), 28);

    ///Partida Luli, 14 pasos
    fichin.nuevaPartida(jugador);
    realizarMovimientos(fichin, "DDDDDDDAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_EQ(fichin.ranking().at(jugador), 14);



}

TEST(fichin, oponenteCorrecto) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli", jugador2 = "Chumi";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);

    ///Partida Luli, 14 pasos
    fichin.nuevaPartida(jugador);
    realizarMovimientos(fichin, "DDDDDDDAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_FALSE(fichin.ranking().empty());

    ///Partida Chumi, 28 pasos
    fichin.nuevaPartida(jugador2);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");
    EXPECT_FALSE(fichin.alguienJugando());

    ///Preguntar si Luli es el objetivo
    fichin.nuevaPartida(jugador2);
    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ("Luli", fichin.objetivo().first);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");//Terminó la partida

}

TEST(fichin, oponenteCorrecto2) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli", jugador2 = "Chumi", jugador3 = "Fulano";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);

    ///Partida Luli, 14 pasos
    fichin.nuevaPartida(jugador);
    realizarMovimientos(fichin, "DDDDDDDAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_FALSE(fichin.ranking().empty());

    ///Partida Chumi, 28 pasos
    fichin.nuevaPartida(jugador2);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");
    EXPECT_FALSE(fichin.alguienJugando());

    ///Partida Fulano, 16 pasos
    fichin.nuevaPartida(jugador3);
    realizarMovimientos(fichin, "DDDDDDDABAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());


    ///Preguntar el objetivo de Fulano
    fichin.nuevaPartida(jugador3);
    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ("Luli", fichin.objetivo().first);
    realizarMovimientos(fichin, "DDDDDDDAAAAAAA");
}

TEST(fichin, nuevoOponente) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    Jugador jugador = "Luli", jugador2 = "Chumi", jugador3 = "Fulano";

    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);

    ///Partida Luli, 14 pasos
    fichin.nuevaPartida(jugador);
    realizarMovimientos(fichin, "DDDDDDDAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_FALSE(fichin.ranking().empty());

    ///Partida Chumi, 28 pasos
    fichin.nuevaPartida(jugador2);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");
    EXPECT_FALSE(fichin.alguienJugando());

    ///Preguntar si Luli es el objetivo
    fichin.nuevaPartida(jugador2);
    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ("Luli", fichin.objetivo().first);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");//Terminó la partida

    ///Partida Fulano, 16 pasos
    fichin.nuevaPartida(jugador3);
    realizarMovimientos(fichin, "DDDDDDDABAAAAAAA");
    EXPECT_FALSE(fichin.alguienJugando());

    ///Preguntar si Fulano es el objetivo
    fichin.nuevaPartida(jugador2);
    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_EQ("Fulano", fichin.objetivo().first);
    realizarMovimientos(fichin, "DDDDDDDAIIIIIIIAAAAAADDDDDDD");//Terminó la partida
}

///Por ahora no se me ocurre nada, sorry

