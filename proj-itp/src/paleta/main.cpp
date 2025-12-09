#include "paleta.h"
#include <iostream>

int main() {
    Paleta p("cores.hex");

    std::cout << "Total de cores: " << p.obterTamanho() << "\n";

    for (int i = 0; i < p.obterTamanho(); i++) {
        Cor c = p.obterCor(i);
        std::cout << i << ": (" << c.r << ", " << c.g << ", " << c.b << ")\n";
    }

    return 0;
}