#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#define M 10007

typedef struct {
	unsigned long index;
	unsigned char *str;
	int count;
} Word;

typedef struct lnode *List;
struct lnode {
	Word *word;
	List next;
} ListNode;

List *table;

int getKey(unsigned char *word, int i);

unsigned long getIndex(unsigned char *word);

Word *createWord(unsigned long index, unsigned char *word);

List createList();

void initializeTable();

int hash(unsigned long x);

void listSort(List list);

void deleteWord(Word *word);

void insertTable(Word *word);

int max(int x, int y);

void readFile(char *filename1, char *filename2);

int searchWord(unsigned char* caption, unsigned long x);

int max(int x, int y);

void printList(List list);

#endif