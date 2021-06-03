#define M 10007

typedef struct {
	int index;
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

int getIndex(unsigned char *word);

Word *createWord(int index, unsigned char *word);

List createList();

void initializeTable();

int hash(int x);

void listSort(List list);

void deleteWord(Word *word);

void insertTable(Word *word);

int max(int x, int y);

void readFile(char *fp);

unsigned char *searchWord(int x);

int max(int x, int y);

void printList(List list);