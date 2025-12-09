#include "terreno.h"
#include "paleta.h"
#include "imagem.h"
#include <iostream>
#include "../terreno/terreno.h"
#include "../paleta/paleta.h"
#include "../imagem/imagem.h"


int main() {
    // 1️⃣ Carrega a paleta
    Paleta paleta("paleta/cores.hex");
    if (paleta.obterTamanho() == 0) {
        std::cerr << "Erro: Paleta vazia!\n";
        return 1;
    }

    // 2️⃣ Cria o terreno
    int N = 8; // tamanho = 2^N + 1 = 257x257
    Terreno terreno(N);
    terreno.gerar(100.0, 0.5); // gerar alturas com deslocamento máximo e rugosidade

    // 3️⃣ Gera a imagem a partir do terreno
    Imagem* img = terreno.gerarImagem(paleta, true);
    if (!img) {
        std::cerr << "Erro: não foi possível gerar a imagem!\n";
        return 1;
    }

    // 4️⃣ Salva a imagem em PPM
    if (!img->salvarPPM("mapa/meu_mapa.ppm")) {
        std::cerr << "Erro: não foi possível salvar o arquivo PPM!\n";
        delete img;
        return 1;
    }

    std::cout << "Mapa gerado com sucesso: mapa/meu_mapa.ppm\n";
    delete img;
    return 0;
}
