#include <stdio.h>
#include <stdlib.h>
#define D 2
struct BT {
    int chave[2*D];
    struct Bt *Filhos[(2*D)+1]; 
    int n; 
};
void cizao(struct BT* x, int i, struct BT* y);
void printKeys (struct BT* pt_raiz);
struct BT* busca (int x , struct BT* pt_raiz,int *f, int *g);
struct BT* novo_no ();

int ler_opcao();
void menu();

int main (){
    int opcao;
	
	while (1) {
		menu();
		opcao = ler_opcao();

		switch(opcao) {
			case 1: {
                char name [13];
                printf ("digite o nome do pokemon desejado: ");
                scanf ("%c", name);

			}
			break;
			
			case 2: {
			}
			break;
			
			case 3: {
				
			}
			break;
			
			case 4: {
				
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
"[9] - Finalizar");
}

struct BT* busca (int x , struct BT* pt_raiz,int *f, int *g){
    struct BT* p = pt_raiz; //define p como o ponteiro que percorre a BT e pt_loc vai mostrar aonde esta localizado a chave
    struct BT* pt_loc = NULL;
    *f = 0; //ira demonstrar se inserção é valida ou nao tomando f = 0 temos ela como valida e f = 1 como invalida
    int i;
	if (pt_raiz == NULL ){
		*f = 0;
		
	}
    while (p!=NULL){
        i = 0;
        *g = 0;
        pt_loc = p;
        while (i <= p->n){
            if (x > p->chave[i]){
                i = i+1;
                *g = i;
            }
            else if (x == p->chave[i]){
                p = NULL;
                *f = 1;
                i = p->n +2;
            }
            else {
                p = p->Filhos[i-1];
                i = p->n +2;
            }
            if (i = p->n+1){
                p = p->Filhos[p->n];
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
