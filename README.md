# gerador-de-um-mapa

 ETAPA 0
 Conceitos utilizados:
 
 Templates (template <typename T>) tornando a classse genérica, armazenando qualquer tipo de dado
 
 Classes e Encapsulamento: Organização dos dados e métodos, protegendo variáveis críticas como o ponteiro do array.
 
 Alocação Dinâmica de Memória: Uso de new e delete[] para gerenciar a memória manualmente no Heap.
    
Ponteiros: Uso de ponteiros (T *dados) para manipular o array dinâmico.
    
Sobrecarga de Operadores (operator[]): Para permitir acessar os elementos da classe usando a sintaxe de colchetes, igual a um array comum.
    
Testes Unitários: Uso da biblioteca doctest para validar o comportamento.


principais identificadores.
classe: sequencia.

variaveis:
capacidade.
tamanho.
*dados.

oque faz: retorna os valores armazenados e retorna a quantidade de dados.

Etapa 1

Conceitos utilizados: (Struct Cor)  rgb
biblioteca std::vector (armazena as cores dinamicamente).
uso de <fstream> para abrir e ler o arquivo cores.hex.
uso do <<sstream>> para convertes hexadecimal em numeros.

Classe: Paleta

aleta(string nomeArquivo)` Construtor que carrega o arquivo.
obterCor(int indice): Recupera uma cor segura (retorna preto se o índice for inválido).

oque o código faz?
constructor com arquivo, leitura e limpeza, converte HEX para int e "extrai" o RGB

ETAPA 2

manipulação de images no formato PPM

matriz (Pixel* dados) para apresentar a imagem do mapa em 2D
Ponteiros (índice = y * largura + x) para encontrar as coordenadas a partir de x, y

operator para acessar os pixel usando imagem(x, y)
uso de ofstream e ifstream para leitura e escrita para carregar e salvar as imagens
PPM

Struct: Pixel (rgb)
Classe: Imagem
ponteiro para o array de pixels: *dados

lerPPM(nomeArquivo): Lê o arquivo do disco para a memória RAM.    
salvarPPM(nomeArquivo): Escreve da memória RAM para o disco.    
operator()(x, y): Acessa ou modifica um pixel específico

oque o codigo faz?
gerencia a memória
le o PPM e depois escreve o PPM
"organiza as cores em uma matriz"

ETAPA 3 Terreno
oque foi utilizado:
algoritmo Diamond Square para geraçao de superficies
gerador de numeros aleatorios <Random>, uso de std::mt19937 (Mersenne Twister)
Potência de 2

Classe: Terreno
std::vector<double> dados simula uma matriz 2D de floats

o código faz um algoritmo que divide o mapa em 2 até chegar em 1 pixel.
Diamond: pega 4 cantos do mapa (quadrado) calculando o centro
Square: pega 4 cantos formando um (losango) e calcula o centro

entrada: tamanho N e rugosidade
sai um vetor com valores double (alturas)
e sai um arquivo de texto contendo dimensões e valores de altura

ETAPA 4

normaliza os dados
mapeia as cores e shading

uso de classes terreno, paleta, imagem
gerarImagem Varre todo o terreno para descobrir qual a altura mais baixa e a mais alta. 
varredura de pixels e calculo da cor

entrada:
paleta e terreno
saida: imagem PPM

o codigo main.cpp le as cores.hex e gera um terreno na memoria, converte em pixels e salva um mapa no disco



COMO COMPILAR?
clone o repositorio: git clone https://github.com/socaiopia/gerador-de-um-mapa
no terminal rode cd proj-itp/src (ou entre na pasta "src")
compile o projeto g++ mapa/main.cpp paleta/paleta.cpp -o projeto_final -Iterreno -Ipaleta -Iimagem  no terminal e rode o comando "cp paleta/cores.hex .
./projeto_final" e verifique a pasta "proj-itp/src/mapa" :)
