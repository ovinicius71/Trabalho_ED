void buscaB(int x, struct BT* pt_raiz, struct BT** pt, int* f, int* g) {
    struct BT* p = pt_raiz;
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
