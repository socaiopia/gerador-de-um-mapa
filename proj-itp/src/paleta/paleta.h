#ifndef PALETA_H
#define PALETA_H

#include "cor.h"
#include <vector>
#include <string>

class Paleta {
    std::vector<Cor> cores;

public:
    Paleta();  // Construtor padrão
    Paleta(const std::string& nomeArquivo);  // Construtor com arquivo

    void adicionarCor(const Cor& cor);
    Cor obterCor(int indice) const;
    int obterTamanho() const;
};

#endif