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