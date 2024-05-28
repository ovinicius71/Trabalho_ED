#include <stdio.h>
#include <stdlib.h>
#define D 2
struct BT {
    int chave[2*D];
    struct BT *Filhos[(2*D)+1]; 
    int n; 
};
void cizao(struct BT* x, int i, struct BT* y);
void printKeys (struct BT* pt_raiz);
void buscaB(int x, struct BT* pt_raiz, struct BT** pt, int* f, int* g);
struct BT* novo_no ();

int ler_opcao();
void menu();

int main (){
    struct BT* raiz = NULL;
    int opcao;
	
	while (1) {
		menu();
		opcao = ler_opcao();

		switch(opcao) {
			case 1: {
                int x;
                printf ("digite o numero a ser incerido: ");
                scanf ("%d", &x);

			}
			break;
			
			case 2: {
                
			}
			break;
			
			case 3: {
				
			}
			break;
			
			case 4: {
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
"[4] - printar \n"
"[9] - Finalizar");
}

void buscaB(int x, struct BT* pt_raiz, struct BT** pt, int* f, int* g) {
    struct BT* p = pt_raiz; //p raiz 
    *pt = NULL;
    *f = 0;

    while (p != NULL) {
        int i = 1;
        *g = 1;
        *pt = p;

        while (i <= p->n && x > p->chave[i - 1]) {
            i++;
            *g = i;
        }

        if (i <= p->n && x == p->chave[i - 1]) {
            p = NULL; // Chave encontrada, sair do loop principal
            *f = 1;
        } else {
            if (i == 1) {
                p = p->Filhos[0];
            } else {
                p = p->Filhos[i - 1];
            }
        }
    }
}

struct BT* novo_no (){
	struct BT * novo = (struct BT*)malloc(sizeof(struct BT)); // cria um nova pagina
	novo->n = 0;
	for (int i; i <= (2*D)+1;i++){ //define seus filhos como NULL
		novo->Filhos[i] = NULL;
	}
	return novo;

}
void printKeys(struct BT* pt_raiz) {
    if (pt_raiz != NULL) {	
        int i;
        for (i = 0; i < pt_raiz->n; i++) { //percorre todas as chaves da pagina e printandos logo em seguidas
            printf("%d ", pt_raiz->chave[i]);
        }
        for (i = 0; i <= pt_raiz->n; i++) { //percorre todas as paginas e chama a funcao novamente para ela
            printKeys(pt_raiz->Filhos[i]);
        }
    }
    else{
        printf("Arvore vazia");
    }
}
int isLeaf(struct BT* pt_raiz) {
    for (int i = 0; i <= pt_raiz->n; i++) { //percorre todos os filhos da pagina para ver se é folha ou não
        if (pt_raiz->Filhos[i] != NULL) {
            return 0;
        }
    }
    return 1;
}
void cizao(struct BT* x, int i, struct BT* y) { //X pai , I indice do onde o filho esta, Y filho
    struct BT* z = novo_no();
    z->n = D;

    for (int j = 0; j < D; j++) { // chaves da segunda metade de Y sao copiadas para Z
        z->chave[j] = y->chave[j + D];
    }

    if (isLeaf(y) == 0) { //Se y for folha os ponteiros para os filhos tmb sao transferidos
        for (int j = 0; j < D; j++) {
            z->Filhos[j] = y->Filhos[j + D];
        }
    }

    y->n = D; // atualiza a quantidade de chaves

    for (int j = x->n; j >= i + 1; j--) { // ajuste no pai para ganhar um novo filho
        x->Filhos[j + 1] = x->Filhos[j];
    }

    x->Filhos[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) { //ajusta as chaves do pai para armazenar a chave media do filho
        x->chave[j + 1] = x->chave[j];
    }

    x->chave[i] = y->chave[D];
    x->n++;
}

void insert(struct BT ** pag, int chave) {
    struct BT* r = *pag;

    if (r->n == D*2) {
        struct BT* s = criaNo();
        *pag = s;
        s->Filhos[0] = r;
        cizao(s, 0, r);
        insert_nfull(s, chave);
    } else {
        insert_nfull(r, chave);
    }
}

void insert_nfull(struct BT * x, int chave) {
    int i = x->n - 1;

    if (isLeaf(x)) {
        while (i >= 0 && x->chave[i] > chave) {
            x->chave[i + 1] = x->chave[i];
            i--;
        }
        x->chave[i + 1] = chave;
        x->n++;
    } else {
        while (i >= 0 && x->chave[i] > chave) {
            i--;
        }
        i++;

        if (x->Filhos[i]->n == 2*D) {
            cizao(x, i, x->Filhos[i]);

            if (x->chave[i] < chave) {
                i++;
            }
        }
        insert_nfull(x->Filhos[i], chave);
    }
}
