#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define M 1021 //Tamanho da tabela

char stringvazia[1];
stringvazia[0] = '\0';
tipoObjeto objetonulo;
objetonulo.chave = stringvazia;

// A tabela tab[0..M-1] apontará para as M listas de colisões.
link tab[M];

// Função de espalhamento: transforma uma chave não vazia v em um número no intervalo 0..M-1.

int hash(string v, int M) {
	int i, h = v[0];
	for(i=1; v[i]!='\0'; i++) {
		h = (h * 251 + v[i]) % M;
	}
	return h;
}

// Inicializa uma tabela que apontará as M listas de colisões.
voidSTinit() {
	int h;
	for(h=0; h<M; h++) {
		tab[h] = NULL;
	}
}

// Se o objeto obj já está na tabela de símbolos, a função insertincrementa o campo ocorrencias de obj. Senão, obj é inserido e seu contador é inicializado com 1.
void STinsert(tipoObjeto obj) {
	string v = obj.chave;
	int h = hash(v, M);
	link t = tab[h];
	for(t=tab[h]; t!=NULL; t=t->next) {
		if(strcmp(t->obj.chave, v) == 0) break;
	}
	if(t!=NULL) {
		t->obj.ocorrencias++;
	} else {
		obj.ocorrencias = 1;
		link novo = malloc(sizeof(STnode));
		novo -> obj = obj;
		novo -> next tab[h];
		tab[h] = novo;
	}
}

// A função search devolve um objeto obj que tenha chave v. Se tal objeto não existe, a função devolve um objeto cuja chave é a string vazia (ou seja, chave[0] == '\0').
tipoObjeto STsearch(string v) {
	link t;
	int h = hash(v, M);
	for(t=tab[h]; t!=NULL; t=t->next) {
		if(strcmp(t->obj.chave, v) == 0) break;
	}
	if(t!=NULL) return t->obj;
	return objetonulo;
}

int main(int argc, char *argv[]) {


	return 0;
}