#include "gtest-1.8.1/gtest.h"
#include "../src/Fichin.h"

TEST(fichinTest, crearFichin) {
    Coordenada inicio = {0, 0};
    Coordenada llegada = {7, 7};
    set<Coordenada> paredes = {};
    set<Coordenada> fantasmas = {};
    set<Coordenada> chocolates = {};
    
    Fichin fichin = Fichin(8, 8, inicio, llegada, paredes, fantasmas, chocolates);
    
    EXPECT_FALSE(fichin.alguienJugando());
    EXPECT_TRUE(fichin.ranking().empty());
}

TEST(fichinTest, nuevaPartida) {
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

TEST(fichinTest, moverJugador) {
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

TEST(fichinTest, ganarPartida) {
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
        fichin.mover(ABAJO);
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
        fichin.mover(DERECHA);
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
        fichin.mover(DERECHA);
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
        fichin.mover(ABAJO);
    }

    EXPECT_TRUE(fichin.alguienJugando());
    EXPECT_TRUE(fichin.ranking().empty());
}