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
