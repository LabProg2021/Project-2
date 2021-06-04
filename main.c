#include <gtk/gtk.h>
#include <ctype.h>
#include <locale.h>
#include "data.h"
#include "src.c"
#include "ui.c"

int main(int argc, char *argv[]) {

	initializeTable();

	readFile("cache.txt", "lusiadas.txt");

	//print de teste
	int i = 0;
	while(i<(M-1)) {
		if(table[i] != NULL) {
			printList(table[i]);
			printf("\n");
		}
		i++;
	}
	printf("\n");
	//printList(table[7]);
	//

	ui(argc, argv);

	return 0;
}