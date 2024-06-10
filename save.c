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
int isLeaf(struct BT* pt_raiz);
// Função para remover uma chave da árvore B
void remove_key(struct BT* root, int x);

// Função para realizar a concatenação de duas páginas irmãs
void concatenate(struct BT* parent, int index);

// Função para realizar a redistribuição de chaves entre duas páginas irmãs
void redistribute(struct BT* parent, int index);

// Função auxiliar para encontrar o sucessor de uma chave na árvore B
int find_successor(struct BT* root);

// Função para buscar uma chave na árvore B e remover, se existir
void search_and_remove(struct BT* root, int x);


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
                search_and_remove(raiz,val);
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

void remove_key(struct BT* root, int x) {
    if (root == NULL)
        return;
    
    search_and_remove(root, x);
}

void search_and_remove(struct BT* root, int x) {
    int i = 0;
    while (i < root->n && x > root->chave[i])
        i++;
    
    if (i < root->n && x == root->chave[i]) {
        // Remover a chave x encontrada
        for (int j = i; j < root->n - 1; j++)
            root->chave[j] = root->chave[j+1];
        root->n--;

        // Verificar se a página ficou com menos chaves que o mínimo
        if (root->n < D) {
            // Se a página é uma folha, não pode ocorrer redistribuição, apenas concatenação
            if (isLeaf(root)) {
                concatenate(root,i);
                // Concatenar ou redistribuir com irmãos
                // A implementação da função concatenate e redistribute é necessária
                printf("Executar operação de concatenação ou redistribuição\n");
            } else {
                // Buscar sucessor na árvore e substituir a chave removida pelo sucessor
                int successor = find_successor(root);
                search_and_remove(root, successor);
                root->chave[i] = successor;
            }
        }
    } else {
        // Se não encontrou a chave na página atual, descer na árvore
        if (isLeaf(root))
            return;
        search_and_remove(root->Filhos[i], x);
    }
}

int find_successor(struct BT* root) {
    // Percorre a árvore B até encontrar a folha mais à esquerda
    while (!isLeaf(root))
        root = root->Filhos[0];
    // O sucessor é a primeira chave da folha mais à esquerda
    return root->chave[0];
}

void concatenate(struct BT* parent, int index) {
    // Verificar se os índices são válidos
    if (index < 0 || index >= parent->n || index >= 2*D - 1) {
        printf("Índice inválido para concatenar páginas irmãs.\n");
        return;
    }

    // Obter as páginas irmãs
    struct BT* left_sibling = parent->Filhos[index];
    struct BT* right_sibling = parent->Filhos[index + 1];

    // Verificar se as páginas irmãs não estão cheias
    if (left_sibling->n + right_sibling->n >= 2*D) {
        printf("As páginas irmãs estão cheias. Não é possível concatenar.\n");
        return;
    }

    // Transferir todas as chaves do irmão direito para o irmão esquerdo
    for (int i = 0; i < right_sibling->n; i++) {
        left_sibling->chave[left_sibling->n - i] = right_sibling->chave[i];
    }

    // Atualizar o número de chaves no irmão esquerdo
    left_sibling->n += right_sibling->n;

    // Se o nó não for uma folha, transferir os ponteiros também
    if (!isLeaf(left_sibling)) {
        for (int i = 0; i <= right_sibling->n; i++) {
            left_sibling->Filhos[left_sibling->n + i] = right_sibling->Filhos[i];
        }
    }

    // Remover o ponteiro do pai para o irmão direito
    for (int i = index + 1; i < parent->n; i++) {
        parent->Filhos[i] = parent->Filhos[i + 1];
    }

    // Atualizar o número de chaves no pai
    parent->n--;

    // Liberar a memória do irmão direito
    free(right_sibling);

    printf("Executar operação de concatenação.\n");
}
void redistribute(struct BT* parent, int index) {
    // Verificar se os índices são válidos
    if (index < 0 || index >= parent->n || index >= 2*D - 1) {
        printf("Índice inválido para redistribuir chaves entre páginas irmãs.\n");
        return;
    }

    // Obter as páginas irmãs
    struct BT* left_sibling = parent->Filhos[index];
    struct BT* right_sibling = parent->Filhos[index + 1];

    // Verificar se as páginas irmãs não têm chaves suficientes para redistribuir
    if (left_sibling->n + right_sibling->n < 2*D) {
        printf("As páginas irmãs não têm chaves suficientes para redistribuição.\n");
        return;
    }

    // Realizar redistribuição de chaves entre os irmãos
    if (left_sibling->n < right_sibling->n) {
        // Transferir a chave do pai para o irmão esquerdo
        left_sibling->chave[left_sibling->n] = parent->chave[index];
        left_sibling->n++;

        // Atualizar a chave do pai para a primeira chave do irmão direito
        parent->chave[index] = right_sibling->chave[0];

        // Mover todas as outras chaves no irmão direito uma posição para a esquerda
        for (int i = 0; i < right_sibling->n - 1; i++) {
            right_sibling->chave[i] = right_sibling->chave[i + 1];
        }

        // Atualizar o número de chaves no irmão direito
        right_sibling->n--;
    } else {
        // Transferir a chave do pai para o irmão direito
        for (int i = right_sibling->n; i > 0; i--) {
            right_sibling->chave[i] = right_sibling->chave[i - 1];
        }
        right_sibling->chave[0] = parent->chave[index];
        right_sibling->n++;

        // Atualizar a chave do pai para a última chave do irmão esquerdo
        parent->chave[index] = left_sibling->chave[left_sibling->n - 1];

        // Atualizar o número de chaves no irmão esquerdo
        left_sibling->n--;
    }

    printf("Executar operação de redistribuição.\n");
}