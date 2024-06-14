#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D 2
#define MAX_LEN 14

struct BT {
    char chave[2*D][MAX_LEN];
    struct BT *Filhos[(2*D)+1];
    int n;
};

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
void ler_arquivo(struct BT **raiz,char *nome_arquivo);
int ler_opcao();

int main() {
    struct BT* raiz = novo_no();
    ler_arquivo(&raiz,"pokemon_names.txt");
    int opcao = 0;

    while (opcao != 9) {
        menu();
        opcao = ler_opcao();

        switch(opcao) {
            case 1: {
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

            case 2: {
                char val[MAX_LEN];
                printf("Digite o valor a ser inserido: ");
                scanf("%s", val);
                insert(&raiz, val);
            }
            break;

            case 3: {
                char val[MAX_LEN];
                printf("Digite o valor a ser removido: ");
                scanf("%s", val);
                remove_key(&raiz, val);
            }
            break;
            case 9: {
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
         "----------------------------------------------------");
}

int ler_opcao() {
    int opcao;
    puts("\nEntre com a sua opcao: ");
    scanf("%d%*c", &opcao);
    return opcao;
}

struct BT* novo_no() {
    struct BT* novo = (struct BT*)malloc(sizeof(struct BT));
    novo->n = 0;
    for (int i = 0; i <= 2*D; i++) {
        novo->Filhos[i] = NULL;
    }
    return novo;
}

void busca(char* x, struct BT* pt_raiz, struct BT** pt, int* f, int* g) {
    struct BT* p = pt_raiz;
    *pt = NULL;
    *f = 0;

    while (p != NULL) {
        int i = 0;
        while (i < p->n && strcmp(x, p->chave[i]) > 0) {
            i++;
        }

        if (i < p->n && strcmp(x, p->chave[i]) == 0) {
            *pt = p;
            *f = 1;
            *g = i;
            return;
        } else {
            *pt = p;
            *g = i;
            p = p->Filhos[i];
        }
    }
}

void cizao(struct BT* x, int i, struct BT* y) {
    struct BT* z = novo_no();
    z->n = D;

    for (int j = 0; j < D ; j++) {
        strcpy(z->chave[j], y->chave[j + D ]);
    }
    if (!isLeaf(y)) {
        for (int j = 0; j <= D; j++) {
            z->Filhos[j] = y->Filhos[j + D];
        }
    }

    y->n = D;

    for (int j = x->n; j >= i + 1; j--) {
        x->Filhos[j + 1] = x->Filhos[j];
    }

    x->Filhos[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        strcpy(x->chave[j + 1], x->chave[j]);
    }

    strcpy(x->chave[i], y->chave[D]);
    x->n++;
}

void insert_nfull(struct BT *x, char* chave) {
    int i = x->n - 1;

    if (isLeaf(x)) {
        while (i >= 0 && strcmp(x->chave[i], chave) > 0) {
            strcpy(x->chave[i + 1], x->chave[i]);
            i--;
        }
        strcpy(x->chave[i + 1], chave);
        x->n++;
    } else {
        while (i >= 0 && strcmp(x->chave[i], chave) > 0) {
            i--;
        }
        i++;

        if (x->Filhos[i]->n == 2 * D) {
            cizao(x, i, x->Filhos[i]);

            if (strcmp(x->chave[i], chave) < 0) {
                i++;
            }
        }
        insert_nfull(x->Filhos[i], chave);
    }
}

void insert(struct BT **pag, char* chave) {
    struct BT* r = *pag;
    int f, g;
    struct BT* pt;

    busca(chave, r, &pt, &f, &g);

    if (f) {
        printf("A chave %s ja existe na arvore.\n", chave);
        return;
    }

    if (r->n == 2 * D) {
        struct BT* s = novo_no();
        *pag = s;
        s->Filhos[0] = r;
        cizao(s, 0, r);
        insert_nfull(s, chave);
    } else {
        insert_nfull(r, chave);
    }
}

void ler_arquivo(struct BT **raiz,char *nome_arquivo) {
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[MAX_LEN];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove a quebra de linha
        insert(raiz, linha);
    }

    fclose(arquivo);
}

void remove_key(struct BT **raiz, char* chave) {
    struct BT *node = *raiz;
    if (!node) {
        printf("A arvore esta vazia.\n");
        return;
    }

    remove_node(node, chave);

    if (node->n == 0) {
        struct BT *temp = node;
        if (isLeaf(node)) {
            *raiz = NULL;
        } else {
            *raiz = node->Filhos[0];
        }
        free(temp);
    }
}

void remove_node(struct BT *node, char* chave) {
    int idx = 0;
    while (idx < node->n && strcmp(node->chave[idx], chave) < 0) {
        idx++;
    }

    if (idx < node->n && strcmp(node->chave[idx], chave) == 0) {
        if (isLeaf(node)) {
            for (int i = idx + 1; i < node->n; i++) {
                strcpy(node->chave[i - 1], node->chave[i]);
            }
            node->n--;
        } else {
            char* pred = get_predecessor(node->Filhos[idx]);
            strcpy(node->chave[idx], pred);
            remove_node(node->Filhos[idx], pred);
        }
    } else {
        if (isLeaf(node)) {
            printf("A chave %s nao esta presente na arvore.\n", chave);
            return;
        }

        int flag = ((idx == node->n) ? 1 : 0);
        if (node->Filhos[idx]->n < D) {
            if (idx != 0 && node->Filhos[idx - 1]->n >= D) {
                redistribute(node, idx - 1);
            } else if (idx != node->n && node->Filhos[idx + 1]->n >= D) {
                redistribute(node, idx);
            } else {
                if (idx != node->n) {
                    concatenate(node, idx);
                } else {
                    concatenate(node, idx - 1);
                }
            }
        }
        if (flag && idx > node->n) {
            remove_node(node->Filhos[idx - 1], chave);
        } else {
            remove_node(node->Filhos[idx], chave);
        }
    }
}

void redistribute(struct BT *parent, int idx) {
    struct BT *child = parent->Filhos[idx];
    struct BT *sibling = parent->Filhos[idx + 1];

    if (child->n < sibling->n) {
        strcpy(child->chave[child->n], parent->chave[idx]);
        if (!isLeaf(child)) {
            child->Filhos[child->n + 1] = sibling->Filhos[0];
        }
        strcpy(parent->chave[idx], sibling->chave[0]);
        for (int i = 1; i < sibling->n; i++) {
            strcpy(sibling->chave[i - 1], sibling->chave[i]);
        }
        if (!isLeaf(sibling)) {
            for (int i = 1; i <= sibling->n; i++) {
                sibling->Filhos[i - 1] = sibling->Filhos[i];
            }
        }
        child->n++;
        sibling->n--;
    } else {
        for (int i = sibling->n - 1; i >= 0; i--) {
            strcpy(sibling->chave[i + 1], sibling->chave[i]);
        }
        if (!isLeaf(sibling)) {
            for (int i = sibling->n; i >= 0; i--) {
                sibling->Filhos[i + 1] = sibling->Filhos[i];
            }
        }
        strcpy(sibling->chave[0], parent->chave[idx]);
        if (!isLeaf(sibling)) {
            sibling->Filhos[0] = child->Filhos[child->n];
        }
        strcpy(parent->chave[idx], child->chave[child->n - 1]);
        child->n--;
        sibling->n++;
    }
}

void concatenate(struct BT *parent, int idx) {
    struct BT *child = parent->Filhos[idx];
    struct BT *sibling = parent->Filhos[idx + 1];

    strcpy(child->chave[child->n], parent->chave[idx]);
    for (int i = 0; i < sibling->n; i++) {
        strcpy(child->chave[child->n + 1 + i], sibling->chave[i]);
    }
    if (!isLeaf(child)) {
        for (int i = 0; i <= sibling->n; i++) {
            child->Filhos[child->n + 1 + i] = sibling->Filhos[i];
        }
    }
    for (int i = idx + 1; i < parent->n; i++) {
        strcpy(parent->chave[i - 1], parent->chave[i]);
    }
    for (int i = idx + 2; i <= parent->n; i++) {
        parent->Filhos[i - 1] = parent->Filhos[i];
    }
    child->n += sibling->n + 1;
    parent->n--;
    free(sibling);
}

char* get_predecessor(struct BT *node) {
    while (!isLeaf(node)) {
        node = node->Filhos[node->n];
    }
    return node->chave[node->n - 1];
}

char* get_successor(struct BT *node) {
    while (!isLeaf(node)) {
        node = node->Filhos[0];
    }
    return node->chave[0];
}

int isLeaf(struct BT* node) {
    return (node->Filhos[0] == NULL);
}