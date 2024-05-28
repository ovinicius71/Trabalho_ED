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