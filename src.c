int getKey(unsigned char *word, int i) {
	switch (word[i]) {
		case 195:
			if(word[i+1] >= 128 && word[i+1] <= 131) {
				return 2;
			} else if(word[i+1] >= 160 && word[i+1] <= 163) {
				return 2;
			} else if(word[i+1] == 167 || word[i+1] == 135) {
				return 2;
			} else {
				return (-1);
			}
		case 'a':
		case 'b':
		case 'c':
		case 'A':
		case 'B':
		case 'C':
			return 2;

		case 'd':
		case 'e':
		case 'f':
		case 'D':
		case 'E':
		case 'F':
			return 3;

		case 'g':
		case 'h':
		case 'i':
		case 'G':
		case 'H':
		case 'I':
			return 4;

		case 'j':
		case 'k':
		case 'l':
		case 'J':
		case 'K':
		case 'L':
			return 5;

		case 'm':
		case 'n':
		case 'o':
		case 'M':
		case 'N':
		case 'O':
			return 6;

		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
			return 7;

		case 't':
		case 'u':
		case 'v':
		case 'T':
		case 'U':
		case 'V':
			return 8;

		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return 9;

		default:
			return 0;
	}
}

int getIndex(unsigned char *word) {
	int i = 0;
	int n = 0;
	while(word[i] != '\0') {
		n = (n*10) + getKey(word, i);
		i++;
		if(word[i-1] == 195) i++;
	}
	return n;
}

Word *createWord(int index, unsigned char *word) {
	Word *newWord = (Word*)malloc(sizeof(Word));

	newWord->index = index;
	newWord->str = (unsigned char*) malloc(sizeof(strlen((char*)word)*sizeof(unsigned char)));
	strcpy((char*) newWord->str, (char*) word);
	newWord->count = 1;

	return newWord;
}

void initializeTable() {
    int h;
    table = malloc(M*sizeof(List));
    for(h=0; h < M; h++) {
        table[h] = NULL;
    }
}

int hash(int x) {
	int h;
	while(x>9999) {
		x /= 10;
	}
	h = x;
	return h;
}

void listSort(List list) {
    while(list != NULL) {
        List subs = list->next;
        while(subs != NULL) {
            if(list->word->count < subs->word->count) {
                Word *temp = list->word;
                list->word = subs->word;
                subs->word = temp;
            }
            subs = subs->next;
        }
        list = list->next;
    }
}

void deleteWord(Word *word) {
	free(word);
}

void insertTable(Word *word) {
	int h = hash(word->index);

	//printf("%d ", h);
	List list;
	//if(table[h] != NULL) printf("string2:%s ", table[h]->word->str);
	for (list = table[h]; list != NULL; list = list->next) {
		//printf("%p ", list);
		//printf("%s ", list->word->str);
		//printf("%s ", word->str);
		if(strcmp((char*) list->word->str, (char*) word->str) == 0 ) {
			//printf("list++ ");
			break;
		}
	}
	if(list != NULL) {
		//printf("%s ", list->word->str);
		deleteWord(word);
		(list->word->count)++;
		//printf("count:%d ", list->word->count);
	} else {
		word->count = 1;
		List new = malloc(sizeof(ListNode));
		new->word = word;
		new->next = table[h];
		table[h] = new;
		//printf("string:%s ", table[h]->word->str);
	}
	//printf("\n");
	listSort(table[h]);
}

int max(int x, int y) {
	if(x>=y) return x;
	else return y;
}

void readFile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) return;

	char temp[70];
	unsigned char word[40];
	
	while(fgets(temp, 60, fp)) {
		if(temp[strlen(temp)-1] == '\n') {
			temp[strlen(temp)-1] = '\0';
		}
		int i = 0;
		int j = 0;
		//printf("\ntemp: %s\n", temp);
		while(temp[max((i-1), 0)] != '\0') {
			//printf("temp[i]='%c' ", temp[i]);
			if(temp[i] == '\0' || isdigit(temp[i]) || temp[i] == ' ' || temp[i] == ',' || temp[i] == '(' || temp[i] == ')' || temp[i] == ';' || temp[i] == ':' || temp[i] == '.' || temp[i] == '"') {
				if(strlen((char*) word) != 0) {
					//printf("\n%d", getIndex(word));
					//printf("\nword: '%s'\n", word);
					insertTable(createWord(getIndex(word), word));
				}
				word[0] = '\0';
				j = 0;
			} else {
				word[j] = temp[i];
				j++;
				word[j] = '\0';
			}
			i++;
		}
		i = 0;
	}
	fclose(fp);
}

unsigned char *searchWord(int x) {
	int h = hash(x);

	if(x<10) {
		return (table[h]->word->str);
	}

	return ((unsigned char*)"teste");
}

void printList(List list) {
    while(list != NULL) {
        printf("%s %d %d\n", list->word->str, list->word->count, list->word->index);
        list = list->next;
    }
}