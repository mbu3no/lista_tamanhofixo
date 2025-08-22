#include<iostream>
using namespace std;

// Estrutura do dado armazenado
struct dados {
    int chave;
};

// União com duas interpretações: cabeçalho ou célula da lista
union celula {
    struct { int quant, first, last, free; } cabecalho;
    struct { int next, prev; dados reg; } lista;
};

// Inicializa a lista com n posições
void inicializa(celula *l, int n) {
    l[0].cabecalho.quant = 0;
    l[0].cabecalho.first = -1;
    l[0].cabecalho.last = -1;
    l[0].cabecalho.free = 1;  // primeira posição livre

    // Configura a lista de espaços livres
    for(int i=1; i<n-1; i++) {
        l[i].lista.next = i+1;
        l[i].lista.prev = 0;
    }
    l[n-1].lista.next = -1; // fim da lista livre
}

// Insere um elemento no final da lista
void insere(celula *l, dados d) {
    int p = l[0].cabecalho.free;
    if (p == -1) {
        cout << "Lista cheia!\n";
        return;
    }

    l[0].cabecalho.free = l[p].lista.next;
    l[p].lista.reg = d;
    l[0].cabecalho.quant++;

    if (l[0].cabecalho.first == -1) {
        // Inserção do primeiro elemento
        l[0].cabecalho.first = l[0].cabecalho.last = p;
        l[p].lista.next = l[p].lista.prev = -1;
    } else {
        // Insere ao final
        int last = l[0].cabecalho.last;
        l[last].lista.next = p;
        l[p].lista.prev = last;
        l[p].lista.next = -1;
        l[0].cabecalho.last = p;
    }
}

// Remove um registro com chave específica
dados remove(celula *l, int chave) {
    dados d;
    d.chave = -1;
    int p = l[0].cabecalho.first;

    while (p != -1) {
        if (l[p].lista.reg.chave == chave) {
            d = l[p].lista.reg;
            int ant = l[p].lista.prev;
            int prox = l[p].lista.next;

            // Ajusta ponteiros de vizinhos
            if (ant != -1) l[ant].lista.next = prox;
            else l[0].cabecalho.first = prox;

            if (prox != -1) l[prox].lista.prev = ant;
            else l[0].cabecalho.last = ant;

            // Devolve a posição à lista livre
            l[p].lista.next = l[0].cabecalho.free;
            l[p].lista.prev = 0;
            l[0].cabecalho.free = p;
            l[0].cabecalho.quant--;

            return d;
        }
        p = l[p].lista.next;
    }
    return d; // Não encontrado
}

// Pesquisa um registro por chave
dados pesquisa(celula *l, int chave) {
    dados d;
    d.chave = -1;
    int p = l[0].cabecalho.first;

    while (p != -1) {
        if (l[p].lista.reg.chave == chave) {
            d = l[p].lista.reg;
            return d;
        }
        p = l[p].lista.next;
    }
    return d; // Não encontrado
}

// Imprime os registros armazenados
void imprimeRegistros(celula *l) {
    int p = l[0].cabecalho.first;
    cout << "\nRegistros:\n";
    while (p != -1) {
        cout << "Chave: " << l[p].lista.reg.chave << endl;
        p = l[p].lista.next;
    }
}

// Imprime a estrutura interna (cabecalho + células)
void imprimeEstrutura(celula *l, int n) {
    cout << "\nCabecalho:\n";
    cout << "quant: " << l[0].cabecalho.quant << "\n";
    cout << "first: " << l[0].cabecalho.first << "\n";
    cout << "last: " << l[0].cabecalho.last << "\n";
    cout << "free: " << l[0].cabecalho.free << "\n";

    cout << "\nEstrutura da Lista:\n";
    for (int i = 1; i < n; i++) {
        cout << "Posicao " << i << " -> ";
        if (l[i].lista.prev == 0)
            cout << "[LIVRE] next: " << l[i].lista.next << "\n";
        else
            cout << "chave: " << l[i].lista.reg.chave << ", prev: " << l[i].lista.prev << ", next: " << l[i].lista.next << "\n";
    }
}

// Insere um registro de forma ordenada pela chave
void insereOrdenado(celula *l, dados d) {
    if (l[0].cabecalho.free == -1) {
        cout << "Lista cheia!\n";
        return;
    }

    int p = l[0].cabecalho.free;
    l[0].cabecalho.free = l[p].lista.next;
    l[p].lista.reg = d;
    l[0].cabecalho.quant++;

    int atual = l[0].cabecalho.first, anterior = -1;
    // Busca posição correta
    while (atual != -1 && l[atual].lista.reg.chave < d.chave) {
        anterior = atual;
        atual = l[atual].lista.next;
    }

    if (anterior == -1) {
        // Inserção no início
        l[p].lista.next = l[0].cabecalho.first;
        l[p].lista.prev = -1;
        if (l[0].cabecalho.first != -1)
            l[l[0].cabecalho.first].lista.prev = p;
        else
            l[0].cabecalho.last = p;
        l[0].cabecalho.first = p;
    } else {
        // Inserção entre nós
        l[p].lista.next = l[anterior].lista.next;
        l[p].lista.prev = anterior;
        if (l[anterior].lista.next != -1)
            l[l[anterior].lista.next].lista.prev = p;
        else
            l[0].cabecalho.last = p;
        l[anterior].lista.next = p;
    }
}

// Menu principal
int main() {
    celula *lista;
    dados d;
    int n, op = 1;

    cout << "Tamanho da lista: ";
    cin >> n;
    n++;  // posição 0 usada para cabeçalho

    lista = new celula[n];
    inicializa(lista, n);

    while (op != 0) {
        cout << "\nMenu:\n";
        cout << "1 - Inserir\n2 - Remover\n3 - Pesquisar\n4 - Imprimir registros\n5 - Imprimir estrutura\n6 - Inserir ordenado\n0 - Sair\nOpcao: ";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Chave: ";
                cin >> d.chave;
                insere(lista, d);
                break;
            case 2:
                cout << "Chave: ";
                cin >> d.chave;
                d = remove(lista, d.chave);
                cout << "Removido: " << d.chave << "\n";
                break;
            case 3:
                cout << "Chave: ";
                cin >> d.chave;
                d = pesquisa(lista, d.chave);
                cout << "Resultado: " << d.chave << "\n";
                break;
            case 4:
                imprimeRegistros(lista);
                break;
            case 5:
                imprimeEstrutura(lista, n);
                break;
            case 6:
                cout << "Chave: ";
                cin >> d.chave;
                insereOrdenado(lista, d);
                break;
        }
    }

    delete[] lista;
    return 0;
}
