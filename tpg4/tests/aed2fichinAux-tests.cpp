#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Fichin.h"

Coordenada c1(1,1);
Coordenada c0(0,0);

set<Coordenada> chocolates = {  Coordenada(4,2),  Coordenada(1,3),  Coordenada(6,4),  Coordenada(9,6),  Coordenada(3,7) };
set<Coordenada> paredes = {  Coordenada(2,0),  Coordenada(2,1),  Coordenada(2,2),
                             Coordenada(2,8),  Coordenada(3,8),  Coordenada(4,8),
                             Coordenada(6,6),  Coordenada(6,7),  Coordenada(6,8) };
set<Coordenada> fantasmas = {  Coordenada(0, 7),  Coordenada(4,9),  Coordenada(7,0),  Coordenada(8,3) };

set<Coordenada> chocolates2 = {  Coordenada(5,3),  Coordenada(2,4),  Coordenada(7,5),  Coordenada(10,7),  Coordenada(4,8) };
set<Coordenada> paredes2 = {  Coordenada(3,1),  Coordenada(3,2),  Coordenada(3,3),
                             Coordenada(3,9),  Coordenada(4,9),  Coordenada(5,9),
                             Coordenada(7,7),  Coordenada(7,8),  Coordenada(7,9) };
set<Coordenada> fantasmas2 = {  Coordenada(1, 8),  Coordenada(5,10),  Coordenada(8,1),  Coordenada(9,4) };

TEST(fichinAux, traducir_coordenada) {
    EXPECT_EQ(c0, traducirCoordenada(c1));
    EXPECT_EQ(Coordenada(2,0), traducirCoordenada(Coordenada(3,1)));
}

TEST(fichinAux, devolver_coordenada){
    EXPECT_EQ(devolverCoordenada(c0), c1);
    EXPECT_EQ(Coordenada(3,1), devolverCoordenada(Coordenada(2,0)));
}

TEST(fichinAux, traducir_conjunto){
    EXPECT_EQ(paredes, traducirConjunto(paredes2));
}

TEST(fichinAux, devolver_conjunto){
    EXPECT_EQ(devolverConjunto(paredes), paredes2);
}