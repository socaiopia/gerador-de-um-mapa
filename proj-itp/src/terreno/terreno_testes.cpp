#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"
#include <fstream>

TEST_CASE("Testa a criação de um terreno de uma única célula") {
  Terreno terreno(0); // 2^0 + 1 = 1
  CHECK(terreno.obterLargura() == 1);
  CHECK(terreno.obterProfundidade() == 1);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  Terreno terreno(2);
  CHECK(terreno.obterLargura() == 5);
  CHECK(terreno.obterProfundidade() == 5);
}


// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".

TEST_CASE("Terreno 1x1 (N=0)") {
    Terreno t(0, 0.0, 1234);
    CHECK(t.obterLargura() == 1);
    CHECK(t.obterProfundidade() == 1);
    // único ponto deve ser default
    CHECK(t.obterAltura(0,0) == 0.0);
}

TEST_CASE("Terreno 5x5 gera com rugosidade 0 (cantoss iguais)") {
    // N=2 -> size = 2^2 +1 = 5
    Terreno t(2, 0.0, 42);
    // define todos os 4 cantos para 10.0
    t.definirAltura(0,0,10.0);
    t.definirAltura(0,4,10.0);
    t.definirAltura(4,0,10.0);
    t.definirAltura(4,4,10.0);

    // gera com deslocamento inicial arbitrario mas rugosidade 0 -> deslocMax será reduzido a 0 após primeira iteração,
    // se deslocMax inicial = 0 também teremos todas as alturas = 10 no final.
    t.gerar(0.0, 0.5, 1); // desloc inicial zero -> todas as médias serão 10.0
    for (int r = 0; r < t.obterProfundidade(); ++r)
        for (int c = 0; c < t.obterLargura(); ++c)
            CHECK(t.obterAltura(r,c) == doctest::Approx(10.0));
}

TEST_CASE("Salvar e ler arquivo") {
    Terreno t(2, 1.2345, 1); // 5x5 com default 1.2345
    bool ok = t.salvar("temp_terreno.txt");
    CHECK(ok);
    // agora ler em outro objeto
    Terreno u(1); // cria 3x3 por enquanto
    bool ok2 = u.ler("temp_terreno.txt");
    CHECK(ok2);
    CHECK(u.obterLargura() == 5);
    CHECK(u.obterAltura(0,0) == doctest::Approx(1.2345));
    // remove arquivo se quiser (não obrigatório)
    std::remove("temp_terreno.txt");
}