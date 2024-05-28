struct BT* novo_no (){
	struct BT * novo = (struct BT*)malloc(sizeof(struct BT)); // cria um nova pagina
	novo->n = 0;
	for (int i; i <= (2*D)+1;i++){ //define seus filhos como NULL
		novo->Filhos[i] = NULL;
	}
	return novo;

}