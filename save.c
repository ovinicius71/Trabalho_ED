#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define D 2

struct BT {
    int chave[2*D];
    struct BT *Filhos[(2*D)+1];
    int n;
};
void remove_s_folha(struct BT *no, int idx);
void remove_n_folha(struct BT *no, int idx);
void removeNo(struct BT *no, int k);
void preencher(struct BT *no, int idx);
void empresta_ant(struct BT *no, int idx);
void empresta_prox(struct BT *no, int idx);
void removeChave(struct BT *no, int idx);
void merge(struct BT *no, int idx);
void cizao(struct BT* x, int i, struct BT* y);
void printKeys(struct BT* pt_raiz);
void busca(int x, struct BT* pt_raiz, struct BT** pt, int* f, int* g);
struct BT* novo_no();
int isLeaf(struct BT* pt_raiz);
void insert_nfull(struct BT *x, int chave);
void insert(struct BT **pag, int chave);
int ler_opcao();
void menu();

int main() {
    struct BT* raiz = novo_no();
    int opcao = 0;

    while (opcao != 9) {
        menu();
        opcao = ler_opcao();

        switch(opcao) {
            case 1: {
                int x;
                int f, g;
                printf("Digite o numero a ser inserido: ");
                scanf("%d", &x);
                struct BT* pt;
                busca(x, raiz, &pt, &f, &g);
                if (f) {
                    printf("Elemento %d encontrado na árvore.\n", x);
                } else {
                    printf("Elemento %d não encontrado na árvore.\n", x);
                }
            }
            break;

            case 2: {
                int val;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &val);
                insert(&raiz, val);
            }
            break;

            case 3: {
                int val;
                scanf("%d", &val);
                removeNo(raiz,val);
                
            }
            break;

            case 4: {
                printf("raiz:");
                printKeys(raiz);
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

int ler_opcao() {
    int opcao;
    puts("\nEntre com a sua opcao: ");
    scanf("%d%*c", &opcao);
    return opcao;
}

void menu() {
    puts("\n// ----- // ----- // ARVORE B // ----- // ----- //\n"
         "[1] - Buscar \n"
         "[2] - Inserir \n"
         "[3] - Remover \n"
         "[4] - Printar \n"
         "[9] - Finalizar");
}

void busca(int x, struct BT* pt_raiz, struct BT** pt, int* f, int* g) {
    struct BT* p = pt_raiz;
    *pt = NULL;
    *f = 0;

    while (p != NULL) {
        int i = 0;
        *g = 0;
        *pt = p;

        while (i < p->n && x > p->chave[i]) {
            i++;
            *g = i;
        }

        if (i < p->n && x == p->chave[i]) {
            *f = 1;
            return;
        } else {
            p = p->Filhos[i];
        }
    }
}

struct BT* novo_no() {
    struct BT* novo = (struct BT*)malloc(sizeof(struct BT));
    novo->n = 0;
    for (int i = 0; i <= 2*D+1; i++) {
        novo->Filhos[i] = NULL;
    }
    return novo;
}

void printKeys(struct BT* pt_raiz) {
    if (pt_raiz != NULL) {
        for (int i = 0; i < pt_raiz->n; i++) {
            printf("%d ", pt_raiz->chave[i]);
        }
        for (int i = 0; i <= pt_raiz->n; i++) {
            printf("\nFilho[%d]:", i);
            printKeys(pt_raiz->Filhos[i]);
        }
    } 
}

int isLeaf(struct BT* pt_raiz) {
    for (int i = 0; i <= pt_raiz->n; i++) {
        if (pt_raiz->Filhos[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

void cizao(struct BT* x, int i, struct BT* y) {
    struct BT* z = novo_no();
    z->n = D-1;

    for (int j = 0; j < D; j++) { // Copia as últimas D chave de y para z
        if (j == 0){
            continue;
        }
        else{
            if (z->chave[j-2] == y->chave[D+1] ){
                continue;
            }
            else{
                z->chave[j-1] = y->chave[D+1];
            }
        
        }
    }

    
    if (!isLeaf(y)) {   // Se y não é uma folha, copia os últimos D+1 Filhos de y para z
        for (int j = 0; j < D; j++) {
            z->Filhos[j] = y->Filhos[j + D ];
        }
    }

    y->n = D;  // Atualiza o número de chave em y
    
    for (int j = x->n; j >= i + 1; j--) { // Move os Filhos de x para a direita para abrir espaço para z
        x->Filhos[j + 1] = x->Filhos[j];
    }

    x->Filhos[i + 1] = z;

   
    for (int j = x->n - 1; j >= i; j--) {    // Move as chave de x para a direita para abrir espaço para a chave do meio
        x->chave[j + 1] = x->chave[j];
    }

    x->chave[i] = y->chave[D]; // Coloca a chave do meio de y em x
    x->n++;
}

void insert(struct BT **pag, int chave) {
    struct BT* r = *pag;
    int f, g;
    struct BT* pt;

    busca(chave, r, &pt, &f, &g); // verifica se a chave ja foi inserida

    if (f) {
        printf("A chave %d ja existe na arvore.\n", chave);
        return;
    }

    if (r->n == 2 * D) { //verifica se a raiz esta cheia 
        struct BT* s = novo_no();
        *pag = s; //atualiza a raiz     
        s->Filhos[0] = r; //raiz antiga vira o primeiro filho da nova
        cizao(s, 0, r);
        insert_nfull(s, chave); //insere a chave na nova raiz
    } else {
        insert_nfull(r, chave);
    }
}

void insert_nfull(struct BT *x, int chave) {
    int i = x->n - 1; //inicicializa I com o indice da ultima chave da pagina

    if (isLeaf(x)) { // se a pagina for uma folha a chave sera incerida diretamente nesta pagina 
        while (i >= 0 && x->chave[i] > chave) { // buscando a posicao correta para a chave
            x->chave[i + 1] = x->chave[i]; 
            i--;
        }
        x->chave[i + 1] = chave; //insere a nova chave
        x->n++;
    } else { // se nao for folha deve-se cacar o filho apropriado para a insercao do da chave
        while (i >= 0 && x->chave[i] > chave) {
            i--;
        }
        i++;

        if (x->Filhos[i]->n == 2 * D) {// se o filho estiver cheio ent aplica a cizao na pagina e verifica em qual filho inserir
            cizao(x, i, x->Filhos[i]);

            if (x->chave[i] < chave) {
                i++;
            }
        }
        insert_nfull(x->Filhos[i], chave);
    }
}
// Função para remover uma chave de um nó da B-tree
void removeChave(struct BT *no, int idx) {
    for (int i = idx + 1; i < no->n; ++i) {
        no->chave[i - 1] = no->chave[i];
    }
    no->n--;
}

// Função para obter o índice da primeira chave maior ou igual a k
int acha_chave(struct BT *no, int k) {
    int idx = 0;
    while (idx < no->n && no->chave[idx] < k) {
        ++idx;
    }
    return idx;
}

// Função para remover uma chave de um nó que não é folha
void remove_n_folha(struct BT *no, int idx) {
    int k = no->chave[idx];

    // Se o filho à esquerda (predecessor) tem pelo menos D chave
    if (no->Filhos[idx]->n >= D) {
        // Encontrar o predecessor (maior chave no subárvore esquerda)
        struct BT *cur = no->Filhos[idx];
        while (!isLeaf(cur)) {
            cur = cur->Filhos[cur->n];
        }
        int pred = cur->chave[cur->n - 1];
        no->chave[idx] = pred;
        removeNo(no->Filhos[idx], pred);
    }
    // Se o filho à direita (sucessor) tem pelo menos D chave
    else if (no->Filhos[idx + 1]->n >= D) {
        // Encontrar o sucessor (menor chave no subárvore direita)
        struct BT *cur = no->Filhos[idx + 1];
        while (!isLeaf(cur)) {
            cur = cur->Filhos[0];
        }
        int succ = cur->chave[0];
        no->chave[idx] = succ;
        removeNo(no->Filhos[idx + 1], succ);
    }
    // Se ambos os Filhos têm menos de D chave, fundi-los
    else {
        // Fundir no->chave[idx] e no->Filhos[idx + 1] em no->Filhos[idx]
        struct BT *child = no->Filhos[idx];
        struct BT *irmao = no->Filhos[idx + 1];

        // Puxar a chave do meio para child
        child->chave[child->n] = k;
        for (int i = 0; i < irmao->n; ++i) {
            child->chave[i + child->n + 1] = irmao->chave[i];
        }
        if (!isLeaf(child)) {
            for (int i = 0; i <= irmao->n; ++i) {
                child->Filhos[i + child->n + 1] = irmao->Filhos[i];
            }
        }

        child->n += irmao->n + 1;
        removeChave(no, idx);
        free(irmao);
        removeNo(child, k);
    }
}

// Função para remover uma chave de uma folha
void remove_s_folha(struct BT *no, int idx) {
    removeChave(no, idx);
}

// Função principal para remover uma chave
void removeNo(struct BT *no, int k) {
    int idx = acha_chave(no, k);

    // A chave a ser removida está presente neste nó
    if (idx < no->n && no->chave[idx] == k) {
        if (isLeaf(no)) {
            remove_s_folha(no, idx);
        } else {
            remove_n_folha(no, idx);
        }
    } else {
        // Se este nó é uma folha, então a chave não está presente na árvore
        if (isLeaf(no)) {
            printf("A chave %d não está presente na árvore\n", k);
            return;
        }

        // O nó filho onde a chave pode estar presente
        bool flag = (idx == no->n);

        // Se o filho onde a chave pode estar tem menos de D chave, preenche
        if (no->Filhos[idx]->n < D) {
            preencher(no, idx);
        }

        // Se o último filho foi fundido, ele deve ter sido fundido com o filho anterior
        // Portanto, recursivamente remover da posição anterior
        if (flag && idx > no->n) {
            removeNo(no->Filhos[idx - 1], k);
        } else {
            removeNo(no->Filhos[idx], k);
        }
    }
}

// Função auxiliar para preencher um nó filho que tem menos de D chave
void preencher(struct BT *no, int idx) {
    if (idx != 0 && no->Filhos[idx - 1]->n >= D) {
        empresta_ant(no, idx);
    } else if (idx != no->n && no->Filhos[idx + 1]->n >= D) {
        empresta_prox(no, idx);
    } else {
        if (idx != no->n) {
            merge(no, idx);
        } else {
            merge(no, idx - 1);
        }
    }
}

// Função auxiliar para emprestar uma chave do nó filho anterior
void empresta_ant(struct BT *no, int idx) {
    struct BT *child = no->Filhos[idx];
    struct BT *irmao = no->Filhos[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->chave[i + 1] = child->chave[i];
    }

    if (!isLeaf(child)) {
        for (int i = child->n; i >= 0; --i) {
            child->Filhos[i + 1] = child->Filhos[i];
        }
    }

    child->chave[0] = no->chave[idx - 1];

    if (!isLeaf(child)) {
        child->Filhos[0] = irmao->Filhos[irmao->n];
    }

    no->chave[idx - 1] = irmao->chave[irmao->n - 1];
    child->n += 1;
    irmao->n -= 1;
}

// Função auxiliar para emprestar uma chave do nó filho próximo
void empresta_prox(struct BT *no, int idx) {
    struct BT *child = no->Filhos[idx];
    struct BT *irmao = no->Filhos[idx + 1];

    child->chave[child->n] = no->chave[idx];

    if (!isLeaf(child)) {
        child->Filhos[child->n + 1] = irmao->Filhos[0];
    }

    no->chave[idx] = irmao->chave[0];

    for (int i = 1; i < irmao->n; ++i) {
        irmao->chave[i - 1] = irmao->chave[i];
    }

    if (!isLeaf(irmao)) {
        for (int i = 1; i <= irmao->n; ++i) {
            irmao->Filhos[i - 1] = irmao->Filhos[i];
        }
    }

    child->n += 1;
    irmao->n -= 1;
}

// Função auxiliar para fundir dois nós Filhos
void merge(struct BT *no, int idx) {
    struct BT *child = no->Filhos[idx];
    struct BT *irmao;
    child->chave[D - 1] = no->chave[idx];

    for (int i = 0; i < irmao->n; ++i) {
        child->chave[i + D] = irmao->chave[i];
    }

    if (!isLeaf(child)) {
        for (int i = 0; i <= irmao->n; ++i) {
            child->Filhos[i + D] = irmao->Filhos[i];
        }
    }

    for (int i = idx + 1; i < no->n; ++i) {
        no->chave[i - 1] = no->chave[i];
    }

    for (int i = idx + 2; i <= no->n; ++i) {
        no->Filhos[i - 1] = no->Filhos[i];
    }

    child->n += irmao->n + 1;
    no->n--;

    free(irmao);
}
