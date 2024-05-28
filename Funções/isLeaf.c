int isLeaf(struct BT* pt_raiz) {
    for (int i = 0; i <= pt_raiz->n; i++) { //percorre todos os filhos da pagina para ver se é folha ou não
        if (pt_raiz->Filhos[i] != NULL) {
            return 0;
        }
    }
    return 1;
}