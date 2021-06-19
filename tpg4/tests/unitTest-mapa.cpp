#include "gtest-1.8.1/gtest.h"
#include "../src/Mapa.h"

Nat largo = 5;
Nat alto = 5;
Coordenada inicio(1,1);
Coordenada llegada(3,2);
Coordenada chocolate(1,0);
Coordenada pared(0,1);
Coordenada fantasma(4,4);
set<Coordenada> chocolates = {chocolate};
set<Coordenada> paredes = {pared};
set<Coordenada> fantasmas = {fantasma};

TEST(mapa, crearMapa){

    Mapa m(largo, alto, inicio, llegada, paredes, fantasmas, chocolates);

    std::cout << "largo: " << largo << " alto: " << alto << std::endl;
    std::cout << "inicio: (" << inicio.first << ", " << inicio.second << ") ";
    std::cout << "llegada: (" << llegada.first << ", " << llegada.second << ")" << std::endl;
    std::cout << "chocolates: {(" << chocolates.begin()->first << ", " << chocolates.begin()->second << ")}" << std::endl;
    std::cout << "paredes: {(" << paredes.begin()->first << ", " << paredes.begin()->second << ")}" <<  std::endl;
    std::cout << "fantasmas: {(" << fantasmas.begin()->first << ", " << fantasmas.begin()->second << ")}" << std::endl;

    std::cout << "largo: " << m.largo() << " alto: " << m.alto() << std::endl;
    std::cout << "inicio: (" << m.inicio().first << ", " << m.inicio().second << ") ";
    std::cout << "llegada: (" << m.llegada().first << ", " << m.llegada().second << ")" << std::endl;
    std::cout << "chocolates: {(" << m.chocolates().begin()->first << ", " << m.chocolates().begin()->second << ")}" << std::endl;
    std::cout << "paredes: {(" << m.paredes().begin()->first << ", " << m.paredes().begin()->second << ")}" <<  std::endl;
    std::cout << "fantasmas: {(" << m.fantasmas().begin()->first << ", " << m.fantasmas().begin()->second << ")}" << std::endl;

    EXPECT_EQ(m.largo(), largo);
    EXPECT_EQ(m.alto(), alto);
    EXPECT_EQ(m.inicio(), inicio);
    EXPECT_EQ(m.llegada(), llegada);
    EXPECT_EQ(m.chocolates(), chocolates);
    EXPECT_EQ(m.paredes(), paredes);
    EXPECT_EQ(m.fantasmas(), fantasmas);
}

TEST(mapa, crearPorOperadorAsignar){
    Mapa m = Mapa(largo, alto, inicio, llegada, paredes, fantasmas, chocolates);
    Mapa test = m;

    std::cout << "largo: " << largo << " alto: " << alto << std::endl;
    std::cout << "inicio: (" << inicio.first << ", " << inicio.second << ") ";
    std::cout << "llegada: (" << llegada.first << ", " << llegada.second << ")" << std::endl;
    std::cout << "chocolates: {(" << chocolates.begin()->first << ", " << chocolates.begin()->second << ")}" << std::endl;
    std::cout << "paredes: {(" << paredes.begin()->first << ", " << paredes.begin()->second << ")}" <<  std::endl;
    std::cout << "fantasmas: {(" << fantasmas.begin()->first << ", " << fantasmas.begin()->second << ")}" << std::endl;

    std::cout << "largo: " << test.largo() << " alto: " << test.alto() << std::endl;
    std::cout << "inicio: (" << test.inicio().first << ", " << test.inicio().second << ") ";
    std::cout << "llegada: (" << test.llegada().first << ", " << test.llegada().second << ")" << std::endl;
    std::cout << "chocolates: {(" << test.chocolates().begin()->first << ", " << test.chocolates().begin()->second << ")}" << std::endl;
    std::cout << "paredes: {(" << test.paredes().begin()->first << ", " << test.paredes().begin()->second << ")}" <<  std::endl;
    std::cout << "fantasmas: {(" << test.fantasmas().begin()->first << ", " << test.fantasmas().begin()->second << ")}" << std::endl;

    EXPECT_EQ(test.largo(), largo);
    EXPECT_EQ(test.alto(), alto);
    EXPECT_EQ(test.inicio(), inicio);
    EXPECT_EQ(test.llegada(), llegada);
    EXPECT_EQ(test.chocolates(), chocolates);
    EXPECT_EQ(test.paredes(), paredes);
    EXPECT_EQ(test.fantasmas(), fantasmas);
}
