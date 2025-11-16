#include <iostream>

template <typename T>
class Sequencia {
    int capacidade; // capacidade atual do array
    int tamanho; // quantidade real de elementos armazenados
    T *dados; // ponteiro para o array dinâmico onde os elementos ficam guardados

    void aumentaCapacidade() {
        capacidade *= 2; // dobra a capacidade
        T *novo = new T[capacidade]; // aloca novo array
        // // copia os elementos antigos para o novo array
        for(int i = 0; i < tamanho; i++) {
            novo[i] = dados[i];
        }
        delete[] dados; // libera memória do array antigo
        dados = novo; // faz o ponteiro "dados" apontar para o novo array
    }

public: // construtor
    Sequencia(int cap = 2): capacidade(cap), tamanho(0)  {
        if (capacidade <= 0) capacidade = 2;
        dados = new T[capacidade];
           
    }
    // destrutor
    ~Sequencia() {
        delete[] dados;
    }
    // retorna o tamanho atual da sequência
    int obterTamanho() {
        return tamanho;
    }
    // adiciona um elemento ao final da sequência
    void adicionar(const T& valor) {
        // se tiver cheio, aumenta a capacidade
        if (tamanho >= capacidade) {
            aumentaCapacidade();
        }
        dados[tamanho++] = valor;
    }
    // retorna o elemento no índice especificado
    T obterElememto(int indice) {
        if (indice < 0 || indice >= tamanho) {
            std::cerr << "Erro: indice inválido";
        }
        return dados[indice];
    }
    // remove o último elemento da sequência, reduzindo o tamanho
    void removerUltimo() {
        if (tamanho == 0) {
            std::cerr << "Erro: remoção de sequencia vazia";
        }
        tamanho--;
    }
    // operador de acesso aos elementos
    T& operator[](int indice) {
        if (indice < 0 || indice >= tamanho) {
            std::cerr << "Erro: indice inválido";
        }
        return dados[indice];
    }
// acessa elementos em objetos constantes
const T& operator[](int indice) const {
        if (indice < 0 || indice >= tamanho) {
            std::cerr << "Erro: indice inválido";
        }
        return dados[indice];
    }
};