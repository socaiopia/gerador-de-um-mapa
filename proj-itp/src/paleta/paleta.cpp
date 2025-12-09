#include "paleta.h"
#include <fstream>
#include <sstream>
#include <iostream>

Paleta::Paleta() : cores() {
    // Construtor padrão que cria paleta vazia
}

// construtor que lê um arquivo de cores
Paleta::Paleta(const std::string& nomeArquivo) : cores() {
    std::ifstream arquivo(nomeArquivo);

    std::cout << "[DEBUG] Tentando abrir: " << nomeArquivo
              << " -> " << (arquivo.is_open() ? "ABRIU" : "FALHOU") << "\n";

    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha[0] != '#')
            continue; // ignora linhas vazias ou inválidas

        // remove o caractere '#' e converte o restante para inteiro hex
        std::string hex = linha.substr(1);
        unsigned int valorHex = 0;

        std::stringstream ss;
        ss << std::hex << hex;
        ss >> valorHex;

        // extrai os componentes RGB
        int r = (valorHex >> 16) & 0xFF;
        int g = (valorHex >> 8) & 0xFF;
        int b = valorHex & 0xFF;

        // adiciona a cor à paleta
        cores.push_back(Cor{r, g, b});
    }

    arquivo.close();
}

// adiciona uma cor à paleta
void Paleta::adicionarCor(const Cor& cor) {
    cores.push_back(cor);
}

// retorna o tamanho
int Paleta::obterTamanho() const {
    return cores.size();
}

// retorna a cor no índice especificado ou preto se inválido
Cor Paleta::obterCor(int indice) const {
    if (indice < 0 || indice >= static_cast<int>(cores.size())) {
        return Cor{0, 0, 0}; // preto
    }
    return cores[indice];
}
