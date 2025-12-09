#ifndef TERRENO_H
#define TERRENO_H

#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>


#include "imagem.h"
#include "paleta.h"
#include "cor.h"


class Terreno {
private:
    int exponent;            
    int size_;               
    std::vector<double> dados; 
    std::mt19937 rng; 
    double defaultValue;

    inline int idx(int lin, int col) const {
        return lin * size_ + col;
    } 

    static double media(const std::vector<double>& valores) {
        double soma = 0.0;
        int count = 0;
        for (double v : valores) {
            if (!std::isnan(v)) {
                soma += v;
                count++;
            }
        }
        return (count > 0) ? (soma / count) : 0.0;
    }

    void etapaDiamond(int passo, double deslocMax) {
        int meio = passo / 2;

        for (int y = meio; y < size_; y += passo) {
            for (int x = meio; x < size_; x += passo) {

                double a = dados[idx(y - meio, x - meio)];
                double b = dados[idx(y - meio, x + meio)];
                double c = dados[idx(y + meio, x - meio)];
                double d = dados[idx(y + meio, x + meio)];

                std::vector<double> valores = {a, b, c, d};

                double m = media(valores);
                std::uniform_real_distribution<double> dist(-deslocMax, deslocMax);

                dados[idx(y, x)] = m + dist(rng);
            }
        }
    }

    void etapaSquare(int passo, double deslocMax) {
        int meio = passo / 2;

        for (int y = 0; y < size_; y += meio) {
            int startX = ((y / meio) % 2 == 0 ? meio : 0);

            for (int x = startX; x < size_; x += passo) {

                std::vector<double> valores;

                if (y - meio >= 0)      valores.push_back(dados[idx(y - meio, x)]);
                if (x + meio < size_)   valores.push_back(dados[idx(y, x + meio)]);
                if (y + meio < size_)   valores.push_back(dados[idx(y + meio, x)]);
                if (x - meio >= 0)      valores.push_back(dados[idx(y, x - meio)]);

                double m = media(valores);
                std::uniform_real_distribution<double> dist(-deslocMax, deslocMax);

                dados[idx(y, x)] = m + dist(rng);
            }
        }
    }

public:

    Terreno(int N = 0, double defaultVal = 0.0, unsigned int seed = std::random_device{}())
        : exponent(N),
          size_((N == 0) ? 1 : ((1 << N) + 1)),
          dados(size_ * size_),
          rng(seed),
          defaultValue(defaultVal)
    {
        std::fill(dados.begin(), dados.end(), defaultVal);
    }

    ~Terreno() = default;

    int obterLargura() const { return size_; }
    int obterProfundidade() const { return size_; }

    double obterAltura(int lin, int col) const {
        if (lin < 0 || lin >= size_ || col < 0 || col >= size_) 
            return NAN;
        return dados[idx(lin, col)];
    }

    void definirAltura(int lin, int col, double valor) {
        if (lin < 0 || lin >= size_ || col < 0 || col >= size_) 
            return;
        dados[idx(lin, col)] = valor;
    }

    bool salvar(const std::string& nomeArquivo) const {
        std::ofstream ofs(nomeArquivo);
        if (!ofs.is_open()) return false;

        ofs << size_ << " " << size_ << "\n";
        ofs.setf(std::ios::fixed);
        ofs.precision(6);

        for (int r = 0; r < size_; ++r) {
            for (int c = 0; c < size_; ++c) {
                ofs << dados[idx(r, c)];
                if (c + 1 < size_) ofs << " ";
            }
            ofs << "\n";
        }
        return true;
    }

    bool ler(const std::string& nomeArquivo) {
        std::ifstream ifs(nomeArquivo);
        if (!ifs.is_open()) return false;

        int w, h;
        ifs >> w >> h;
        if (!ifs) return false;

        size_ = w;

        if (size_ == 1) {
            exponent = 0;
        } else {
            exponent = 0;
            int s = size_ - 1;
            while (s % 2 == 0 && s > 1) {
                s /= 2;
                ++exponent;
            }
        }

        dados.assign(size_ * size_, defaultValue);

        for (int r = 0; r < size_; ++r) {
            for (int c = 0; c < size_; ++c) {
                double val;
                ifs >> val;
                if (!ifs) return false;
                dados[idx(r, c)] = val;
            }
        }
        return true;
    }

    void gerar(double inicioDeslocMax = 1.0, double rugosidade = 0.5, unsigned int seed = 0) {

        if (seed != 0)
            rng.seed(seed);

        int passo = size_ - 1;
        double deslocMax = inicioDeslocMax;

        bool cantosTodosDefault = 
            dados[idx(0,0)] == defaultValue &&
            dados[idx(0,size_-1)] == defaultValue &&
            dados[idx(size_-1,0)] == defaultValue &&
            dados[idx(size_-1,size_-1)] == defaultValue;

        if (cantosTodosDefault) {
            std::uniform_real_distribution<double> dist(-inicioDeslocMax, inicioDeslocMax);
            dados[idx(0,0)] = dist(rng);
            dados[idx(0,size_-1)] = dist(rng);
            dados[idx(size_-1,0)] = dist(rng);
            dados[idx(size_-1,size_-1)] = dist(rng);
        }

        while (passo > 1) {
            etapaDiamond(passo, deslocMax);
            etapaSquare(passo, deslocMax);

            passo /= 2;
            deslocMax *= rugosidade;
        }
    }

    // -----------------------------------------------------
    // 🔥 MÉTODO QUE VOCÊ QUERIA ADICIONAR (AGORA FUNCIONA)
    // -----------------------------------------------------
    Imagem* gerarImagem(const Paleta& paleta, bool sombrear = true) const {

        if (paleta.obterTamanho() == 0) {
            std::cerr << "Erro: paleta vazia!\n";
            return nullptr;
        }

        Imagem* img = new Imagem(size_, size_);

        double minH = dados[0], maxH = dados[0];
        for (double h : dados) {
            if (h < minH) minH = h;
            if (h > maxH) maxH = h;
        }

        double baseAlt = dados[idx(0, 0)];

        for (int y = 0; y < size_; y++) {
            for (int x = 0; x < size_; x++) {

                double h = dados[idx(y, x)];
                double t = (h - minH) / (maxH - minH);
                int indice = t * (paleta.obterTamanho() - 1);

                Cor c = paleta.obterCor(indice);
                Pixel p{c.r, c.g, c.b};

                if (sombrear && h < baseAlt) {
                    double fator = 0.5;
                    p.r *= fator;
                    p.g *= fator;
                    p.b *= fator;
                }

                (*img)(x, y) = p;
            }
        }

        return img;
    }

};

#endif // TERRENO_H
