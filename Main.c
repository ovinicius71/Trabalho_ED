#include <stdio.h>
#include <stdlib.h>

#define D 2

struct BT {
    int chave[2*D];
    struct BT *Filhos[(2*D)+1];
    int n;
};

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

    for (int j = 0; j < D; j++) { // Copia as últimas D chaves de y para z
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

    
    if (!isLeaf(y)) {   // Se y não é uma folha, copia os últimos D+1 filhos de y para z
        for (int j = 0; j < D; j++) {
            z->Filhos[j] = y->Filhos[j + D ];
        }
    }

    y->n = D;  // Atualiza o número de chaves em y
    
    for (int j = x->n; j >= i + 1; j--) { // Move os filhos de x para a direita para abrir espaço para z
        x->Filhos[j + 1] = x->Filhos[j];
    }

    x->Filhos[i + 1] = z;

   
    for (int j = x->n - 1; j >= i; j--) {    // Move as chaves de x para a direita para abrir espaço para a chave do meio
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