#include <stdio.h>

int ler_opcao();
void menu();

int main ()

{
	int opcao;
	
	while (1) {
		menu();
		opcao = ler_opcao();

		switch(opcao) {
			case 1: {
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
"[9] - Finalizar"
);
}