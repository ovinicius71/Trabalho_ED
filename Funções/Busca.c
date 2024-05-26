struct BT* busca (int x , struct BT* pt_raiz,int f, int g){
    struct BT* p = pt_raiz;
    struct BT* pt_loc = NULL;
    f = 0;
    int i;

    while (p!=NULL){
        i = 0;
        g = 1;
        pt_loc = p;
        while (i <= p->n){
            if (x > p->chave[i]){
                i = i+1;
                g = i;
            }
            else if (x == p->chave[i]){
                p = NULL;
                f = 1;
                i = p->n +2;
            }
            else {
                p = p->Filho[i-1];
                i = p->n +2;
            }
            if (i = p->n+1){
                p = p->Filho[p->n];
            }
        }
    }
}