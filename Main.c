#include <stdio.h>
#include <stdlib.h>
#define D 2
struct BT {
    int chave[2*D];
    struct Bt *Filhos[(2*D)+1]; 
    int n; 
};

struct BT* busca (int x , struct BT* pt_raiz,int *f, int *g);
struct BT* novo_no (struct BT *pt_raiz, int x);

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
struct BT* novo_no (struct BT *pt_raiz, int x){
	struct BT * novo;
	int f;
	int g;


}