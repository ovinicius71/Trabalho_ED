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
