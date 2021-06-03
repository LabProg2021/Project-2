#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

void creatTable() {
    tab = malloc(M*sizeof(list));
    for(int i=0; i<M; i++) {
        tab[i] = NULL;
    }
}

void insertTable(Word word) {
    int v;
    v = word.index;
    list new = tab[v];
    for (new = tab[v]; new != NULL; new = new->next) {
        if(strcmp(new->obj.key, word.key) == 0 ) {
            break;
        }
    }
    if(new != NULL) {
        new->obj.count ++; 
    }
    else {
        word.count = 1;
        list in = malloc(sizeof(ListNode));
        in->obj = word;
        in->next = tab[v];
        tab[v] = in;
    }
    orderBy(v);
}

Word searchIndex(int index) {
    list t;
    for(t= tab[index]; t != NULL ; t = t->next) {
        if(t->obj.index == index) break;
    }
    if(t!=NULL) return t->next->obj;
    return t->obj;
}

void orderBy(int index) {
    list t = tab[index];
    while(t != NULL) {
        list next = t->next;
        while(next != NULL) {
            if(t->obj.count <= next->obj.count) {
                Word temp = t->obj;
                t->obj = next->obj;
                next->obj = temp;
            }
            next = next->next;
        }
        t = t->next;
    }
}

void printBy(int index) {
    list t = tab[index];
    while(t != NULL) {
        printf("%s %d %d\n", t->obj.key, t->obj.count, t->obj.index);
        t = t->next;
    }
}