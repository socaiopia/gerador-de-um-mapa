#ifndef IMAGEM_H
#define IMAGEM_H

#include <fstream>
#include <sstream>
#include <iostream>

struct Pixel {
    int r, g, b;
};

class Imagem {
private:
    int largura;
    int altura;
    Pixel* dados;

public:
    Imagem() : largura(0), altura(0), dados(nullptr) {}

    Imagem(int largura, int altura)
        : largura(largura), altura(altura)
    {
        dados = new Pixel[largura * altura];
        for (int i = 0; i < largura * altura; ++i) {
            dados[i] = {0, 0, 0};
        }
    }

    ~Imagem() {
        delete[] dados;
    }

    int obterLargura() const { return largura; }
    int obterAltura() const { return altura; }

    Pixel& operator()(int x, int y) {
        return dados[y * largura + x];
    }

    const Pixel& operator()(int x, int y) const {
        return dados[y * largura + x];
    }

    bool lerPPM(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open())
            return false;

        std::string tipo;
        arquivo >> tipo;
        if (tipo != "P3")
            return false;

        int novaLargura, novaAltura, maxVal;
        arquivo >> novaLargura >> novaAltura >> maxVal;

        delete[] dados;
        largura = novaLargura;
        altura = novaAltura;
        dados = new Pixel[largura * altura];

        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                int r, g, b;
                arquivo >> r >> g >> b;
                dados[y * largura + x] = {r, g, b};
            }
        }

        return true;
    }

    bool salvarPPM(const std::string& nomeArquivo) const {
        std::ofstream arquivo(nomeArquivo);
        if (!arquivo.is_open())
            return false;

        arquivo << "P3\n";
        arquivo << largura << " " << altura << "\n";
        arquivo << "255\n";

        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                const Pixel& p = dados[y * largura + x];
                arquivo << p.r << " " << p.g << " " << p.b << "\n";
            }
        }

        return true;
    }
};

#endif

// Fim do arquivo imagem.h