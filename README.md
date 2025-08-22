# Lista de Registros de Tamanho Fixo

Este projeto é uma implementação em C++ de uma lista de registros de tamanho fixo, utilizando uma abordagem baseada em array com gerenciamento de cursor. A estrutura simula uma lista duplamente encadeada dentro de um vetor, controlando os espaços livres e os registros ocupados através de um cabeçalho especial.

O programa foi desenvolvido como parte da disciplina de Estrutura de Dados e segue as especificações de uma atividade acadêmica.

## 🚀 Funcionalidades

O programa oferece um menu interativo com as seguintes operações:

* **Inserir:** Adiciona um novo registro no final da lista.
* **Inserir Ordenado:** Adiciona um novo registro mantendo a ordem crescente das chaves, sem mover fisicamente os registros de lugar (apenas manipulando os ponteiros `next` e `prev`).
* **Remover:** Remove um registro da lista com base em sua chave.
* **Pesquisar:** Busca por um registro específico através da sua chave.
* **Imprimir Registros:** Exibe todos os registros armazenados, seguindo a ordem lógica da lista (do primeiro ao último).
* **Imprimir Estrutura:** Mostra o estado completo do array, incluindo o cabeçalho, os registros em suas posições físicas e os espaços que estão livres.

## 🛠️ Estrutura de Dados

A principal estrutura de dados é um array que utiliza uma `union` para representar tanto o cabeçalho da lista quanto as células de dados.

* **Índice 0 (Cabeçalho):** O primeiro elemento do array funciona como um cabeçalho, armazenando metadados essenciais para o gerenciamento da lista:
    * `quant`: Número de registros atualmente na lista.
    * `first`: Índice do primeiro registro da lista lógica.
    * `last`: Índice do último registro da lista lógica.
    * `free`: Índice do primeiro espaço livre na "lista de disponíveis".

* **Índices > 0 (Células da Lista):** Os demais elementos do array armazenam os registros de dados e os ponteiros que formam a lista duplamente encadeada.
    * `reg`: O dado em si (neste caso, uma `chave` inteira).
    * `next`: Índice do próximo registro na lista.
    * `prev`: Índice do registro anterior na lista.

A gestão de espaços livres também é feita como uma lista encadeada, onde o ponteiro `free` do cabeçalho aponta para a primeira célula vaga, e cada célula vaga aponta para a próxima, otimizando as operações de inserção e remoção.

## 📋 Como Compilar e Executar

Para rodar este projeto, você precisará de um compilador C++, como o G++, instalado em sua máquina.

1.  Salve o código em um arquivo chamado `main.cpp`.
2.  Abra o terminal ou prompt de comando e navegue até a pasta onde você salvou o arquivo.
3.  Compile o código com o seguinte comando:
    ```bash
    g++ main.cpp -o programa
    ```
4.  Execute o programa:
    ```bash
    ./programa
    ```

Após a execução, o programa solicitará o tamanho da lista e exibirá o menu de operações.

## 💻 Exemplo de Uso

```console
Tamanho da lista: 5

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Imprimir registros
5 - Imprimir estrutura
6 - Inserir ordenado
0 - Sair
Opcao: 1
Chave: 10

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Imprimir registros
5 - Imprimir estrutura
6 - Inserir ordenado
0 - Sair
Opcao: 6
Chave: 5

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Imprimir registros
5 - Imprimir estrutura
6 - Inserir ordenado
0 - Sair
Opcao: 4

Registros:
Chave: 5
Chave: 10

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Imprimir registros
5 - Imprimir estrutura
6 - Inserir ordenado
0 - Sair
Opcao: 5

Cabecalho:
quant: 2
first: 2
last: 1
free: 3

Estrutura da Lista:
Posicao 1 -> chave: 10, prev: 2, next: -1
Posicao 2 -> chave: 5, prev: -1, next: 1
Posicao 3 -> [LIVRE] next: 4
Posicao 4 -> [LIVRE] next: 5
Posicao 5 -> [LIVRE] next: -1

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Imprimir registros
5 - Imprimir estrutura
6 - Inserir ordenado
0 - Sair
Opcao: 0
