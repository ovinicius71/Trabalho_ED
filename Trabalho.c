#include <stdio.h>      // Biblioteca padrão de entrada e saída
#include <stdlib.h>     // Biblioteca padrão de funções utilitárias
#include <string.h>     // Biblioteca padrão de manipulação de strings

#define D 2             // Grau mínimo da árvore B
#define MAX_LEN 14      // Comprimento máximo da chave

// Estrutura da árvore B
struct BT {
    char chave[2*D][MAX_LEN];  // Vetor de chaves
    struct BT *Filhos[(2*D)+1];// Vetor de ponteiros para filhos
    int n;                     // Número de chaves no nó
};

// Declarações de funções
void cizao(struct BT* x, int i, struct BT* y);
void busca(char* x, struct BT* pt_raiz, struct BT** pt, int* f, int* g);
struct BT* novo_no();
void insert_nfull(struct BT *x, char* chave);
void insert(struct BT **pag, char* chave);
void remove_key(struct BT **raiz, char* chave);
void remove_node(struct BT *node, char* chave);
void redistribute(struct BT *parent, int idx);
void concatenate(struct BT *parent, int idx);
char* get_predecessor(struct BT *node);
char* get_successor(struct BT *node);
int isLeaf(struct BT* node);
void menu();
void ler_arquivo(struct BT **raiz, char *nome_arquivo);
int ler_opcao();

int main() {
    struct BT* raiz = novo_no();               // Cria a raiz da árvore B
    ler_arquivo(&raiz, "pokemon_names.txt");   // Lê o arquivo de nomes e insere na árvore B
    int opcao = 0;                             // Inicializa a opção do menu

    while (opcao != 9) {                       // Loop do menu principal
        menu();                                // Exibe o menu
        opcao = ler_opcao();                   // Lê a opção do usuário

        switch(opcao) {                        // Executa a ação baseada na opção
            case 1: {                          // Caso 1: Busca
                char x[MAX_LEN];
                int f, g;
                printf("Digite o valor a ser buscado: ");
                scanf("%s", x);
                struct BT* pt;
                busca(x, raiz, &pt, &f, &g);
                if (f == 1) {
                    printf("Elemento %s encontrado na arvore.\n", x);
                } else {
                    printf("Elemento %s nao encontrado na arvore.\n", x);
                }
            }
            break;

            case 2: {                          // Caso 2: Inserir
                char val[MAX_LEN];
                printf("Digite o valor a ser inserido: ");
                scanf("%s", val);
                insert(&raiz, val);
            }
            break;

            case 3: {                          // Caso 3: Remover
                char val[MAX_LEN];
                printf("Digite o valor a ser removido: ");
                scanf("%s", val);
                remove_key(&raiz, val);
            }
            break;

            case 9: {                          // Caso 9: Sair
                puts("Finalizando programa ..");
                return 0;
            }
            break;
        }
    }
    return 0;
}

void menu() {
    puts("\n// ----- // ----- // ARVORE B // ----- // ----- //\n"
         "[1] - Buscar \n"
         "[2] - Inserir \n"
         "[3] - Remover \n"
         "[9] - Finalizar\n"
         "----------------------------------------------------");  // Exibe o menu
}

int ler_opcao() {
    int opcao;
    puts("\nEntre com a sua opcao: ");
    scanf("%d%*c", &opcao);                     // Lê a opção do usuário
    return opcao;
}

struct BT* novo_no() {
    struct BT* novo = (struct BT*)malloc(sizeof(struct BT)); // Aloca memória para um novo nó
    novo->n = 0;                                              // Inicializa o número de chaves como 0
    for (int i = 0; i <= 2*D; i++) {
        novo->Filhos[i] = NULL;                               // Inicializa todos os filhos como NULL
    }
    return novo;                                              // Retorna o novo nó
}

void busca(char* x, struct BT* pt_raiz, struct BT** pt, int* f, int* g) {
    struct BT* p = pt_raiz;     // Inicia a busca a partir da raiz
    *pt = NULL;                 // Inicializa o ponteiro pt como NULL
    *f = 0;                     // Inicializa o indicador de encontrado como 0

    while (p != NULL) {         // Enquanto não chegar a uma folha
        int i = 0;
        while (i < p->n && strcmp(x, p->chave[i]) > 0) {
            i++;                // Encontra a posição correta no nó
        }

        if (i < p->n && strcmp(x, p->chave[i]) == 0) {
            *pt = p;            // Se encontrar a chave, atualiza pt e f
            *f = 1;
            *g = i;
            return;
        } else {
            *pt = p;            // Se não encontrar, move para o filho apropriado
            *g = i;
            p = p->Filhos[i];
        }
    }
}

void cizao(struct BT* x, int i, struct BT* y) {
    struct BT* z = novo_no();    // Cria um novo nó z
    z->n = D;                    // Inicializa o número de chaves de z

    for (int j = 0; j < D; j++) {
        strcpy(z->chave[j], y->chave[j + D]); // Copia as chaves de y para z
    }
    if (!isLeaf(y)) {
        for (int j = 0; j <= D; j++) {
            z->Filhos[j] = y->Filhos[j + D];  // Copia os filhos de y para z
        }
    }

    y->n = D;                    // Atualiza o número de chaves de y

    for (int j = x->n; j >= i + 1; j--) {
        x->Filhos[j + 1] = x->Filhos[j]; // Ajusta os filhos de x
    }

    x->Filhos[i + 1] = z;        // Define z como filho de x

    for (int j = x->n - 1; j >= i; j--) {
        strcpy(x->chave[j + 1], x->chave[j]); // Ajusta as chaves de x
    }

    strcpy(x->chave[i], y->chave[D]); // Copia a chave do meio de y para x
    x->n++;                            // Incrementa o número de chaves de x
}

void insert_nfull(struct BT *x, char* chave) {
    int i = x->n - 1;                // Inicializa i como o índice da última chave

    if (isLeaf(x)) {                 // Se x é folha
        while (i >= 0 && strcmp(x->chave[i], chave) > 0) {
            strcpy(x->chave[i + 1], x->chave[i]); // Move as chaves para a direita
            i--;
        }
        strcpy(x->chave[i + 1], chave); // Insere a nova chave
        x->n++;                         // Incrementa o número de chaves
    } else {                            // Se x não é folha
        while (i >= 0 && strcmp(x->chave[i], chave) > 0) {
            i--;
        }
        i++;

        if (x->Filhos[i]->n == 2 * D) { // Se o filho está cheio
            cizao(x, i, x->Filhos[i]); // Divide o filho

            if (strcmp(x->chave[i], chave) < 0) {
                i++;                   // Ajusta o índice se necessário
            }
        }
        insert_nfull(x->Filhos[i], chave); // Insere a chave no filho apropriado
    }
}

void insert(struct BT **pag, char* chave) {
    struct BT* r = *pag;               // Raiz da árvore
    int f, g;
    struct BT* pt;

    busca(chave, r, &pt, &f, &g);      // Busca pela chave

    if (f) {                           // Se a chave já existe
        printf("A chave %s ja existe na arvore.\n", chave);
        return;
    }

    if (r->n == 2 * D) {               // Se a raiz está cheia
        struct BT* s = novo_no();      // Cria um novo nó
        *pag = s;                      // Atualiza a raiz
        s->Filhos[0] = r;              // Define o filho da nova raiz
        cizao(s, 0, r);                // Divide a raiz
        insert_nfull(s, chave);        // Insere a chave no nó apropriado
    } else {
        insert_nfull(r, chave);        // Insere a chave na raiz
    }
}

void ler_arquivo(struct BT **raiz, char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");  // Abre o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");  // Verifica erro na abertura
        return;
    }

    char linha[MAX_LEN];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove a quebra de linha
        insert(raiz, linha);                 // Insere a linha na árvore
    }

    fclose(arquivo);                         // Fecha o arquivo
}

void remove_key(struct BT **raiz, char* chave) {
    struct BT *node = *raiz;
    if (!node) {                             // Verifica se a árvore está vazia
        printf("A arvore esta vazia.\n");
        return;
    }

    remove_node(node, chave);                // Remove a chave

    if (node->n == 0) {                      // Se a raiz estiver vazia
        struct BT *temp = node;
        if (isLeaf(node)) {
            *raiz = NULL;                    // Atualiza a raiz
        } else {
            *raiz = node->Filhos[0];
        }
        free(temp);                          // Libera memória
    }
}

void remove_node(struct BT *node, char* chave) {
    int idx = 0;
    while (idx < node->n && strcmp(node->chave[idx], chave) < 0) {
        idx++;                               // Encontra o índice da chave
    }

    if (idx < node->n && strcmp(node->chave[idx], chave) == 0) {
        if (isLeaf(node)) {                  // Se o nó é folha
            for (int i = idx + 1; i < node->n; i++) {
                strcpy(node->chave[i - 1], node->chave[i]); // Remove a chave
            }
            node->n--;                       // Decrementa o número de chaves
        } else {                             // Se o nó não é folha
            char* pred = get_predecessor(node->Filhos[idx]);
            strcpy(node->chave[idx], pred);  // Substitui pela chave predecessora
            remove_node(node->Filhos[idx], pred); // Remove a chave predecessora
        }
    } else {
        if (isLeaf(node)) {                  // Se a chave não está presente
            printf("A chave %s nao esta presente na arvore.\n", chave);
            return;
        }

        int flag = ((idx == node->n) ? 1 : 0); // Define flag com base na posição de idx

        if (node->Filhos[idx]->n < D) {     // Se o filho tem menos de D chaves
            if (idx != 0 && node->Filhos[idx - 1]->n >= D) {
                redistribute(node, idx - 1); // Redistribui com o filho esquerdo
            } else if (idx != node->n && node->Filhos[idx + 1]->n >= D) {
                redistribute(node, idx);     // Redistribui com o filho direito
            } else {
                if (idx != node->n) {
                    concatenate(node, idx);  // Concatena os filhos
                } else {
                    concatenate(node, idx - 1);
                }
            }
        }

        if (flag && idx > node->n) {
            remove_node(node->Filhos[idx - 1], chave); // Remove a chave do filho apropriado
        } else {
            remove_node(node->Filhos[idx], chave);
        }
    }
}

void redistribute(struct BT *parent, int idx) {
    struct BT *child = parent->Filhos[idx];
    struct BT *sibling = parent->Filhos[idx + 1];

    if (child->n < sibling->n) {
        strcpy(child->chave[child->n], parent->chave[idx]); // Move a chave do pai para o filho
        if (!isLeaf(child)) {
            child->Filhos[child->n + 1] = sibling->Filhos[0]; // Move o filho do irmão para o filho
        }
        strcpy(parent->chave[idx], sibling->chave[0]); // Move a chave do irmão para o pai
        for (int i = 1; i < sibling->n; i++) {
            strcpy(sibling->chave[i - 1], sibling->chave[i]); // Ajusta as chaves do irmão
        }
        if (!isLeaf(sibling)) {
            for (int i = 1; i <= sibling->n; i++) {
                sibling->Filhos[i - 1] = sibling->Filhos[i]; // Ajusta os filhos do irmão
            }
        }
        child->n++;
        sibling->n--;
    } else {
        for (int i = sibling->n - 1; i >= 0; i--) {
            strcpy(sibling->chave[i + 1], sibling->chave[i]); // Ajusta as chaves do irmão
        }
        if (!isLeaf(sibling)) {
            for (int i = sibling->n; i >= 0; i--) {
                sibling->Filhos[i + 1] = sibling->Filhos[i]; // Ajusta os filhos do irmão
            }
        }
        strcpy(sibling->chave[0], parent->chave[idx]); // Move a chave do pai para o irmão
        if (!isLeaf(sibling)) {
            sibling->Filhos[0] = child->Filhos[child->n]; // Move o filho do filho para o irmão
        }
        strcpy(parent->chave[idx], child->chave[child->n - 1]); // Move a chave do filho para o pai
        child->n--;
        sibling->n++;
    }
}

void concatenate(struct BT *parent, int idx) {
    struct BT *child = parent->Filhos[idx];
    struct BT *sibling = parent->Filhos[idx + 1];

    strcpy(child->chave[child->n], parent->chave[idx]); // Move a chave do pai para o filho
    for (int i = 0; i < sibling->n; i++) {
        strcpy(child->chave[child->n + 1 + i], sibling->chave[i]); // Copia as chaves do irmão
    }
    if (!isLeaf(child)) {
        for (int i = 0; i <= sibling->n; i++) {
            child->Filhos[child->n + 1 + i] = sibling->Filhos[i]; // Copia os filhos do irmão
        }
    }
    for (int i = idx + 1; i < parent->n; i++) {
        strcpy(parent->chave[i - 1], parent->chave[i]); // Ajusta as chaves do pai
    }
    for (int i = idx + 2; i <= parent->n; i++) {
        parent->Filhos[i - 1] = parent->Filhos[i]; // Ajusta os filhos do pai
    }
    child->n += sibling->n + 1;
    parent->n--;
    free(sibling); // Libera memória do irmão
}

char* get_predecessor(struct BT *node) {
    while (!isLeaf(node)) {
        node = node->Filhos[node->n]; // Move para o filho direito mais à direita
    }
    return node->chave[node->n - 1]; // Retorna a chave predecessora
}

char* get_successor(struct BT *node) {
    while (!isLeaf(node)) {
        node = node->Filhos[0]; // Move para o filho esquerdo mais à esquerda
    }
    return node->chave[0]; // Retorna a chave sucessora
}

int isLeaf(struct BT* node) {
    return (node->Filhos[0] == NULL); // Verifica se o nó é folha
}
