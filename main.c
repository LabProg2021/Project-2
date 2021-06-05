#include <gtk/gtk.h>
#include <ctype.h>
#include <locale.h>
#include "data.h"
#include "src.c"
#include "ui.c"

int main(int argc, char *argv[]) {

	initializeTable();

	readFile("cache.txt", "lusiadas.txt");

	/*
	//Print da tabela na consola (das i posições)
	int i = 0;
	while(i<(M-1)) {
		if(table[i] != NULL) {
			printList(table[i]);
			printf("\n");
		}
		i++;
	}
	printf("\n");
	//
	*/

	ui(argc, argv);

	return 0;
}