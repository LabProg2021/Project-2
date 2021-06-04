int contador = 0;

int getKey(unsigned char *word, int i) {
	switch (word[i]) {
		case 195:
			if(word[i+1] >= 128 && word[i+1] <= 131) { // 'A' acentuados
				return 2;
			} else if(word[i+1] >= 160 && word[i+1] <= 163) { // 'a' acentuados
				return 2;
			} else if(word[i+1] == 167 || word[i+1] == 135) { // 'ç' e 'Ç'
				return 2;
			} else if(word[i+1] >= 136 && word[i+1] <= 138) { // 'E' acentuados
				return 3;
			} else if(word[i+1] >= 140 && word[i+1] <= 142) { // 'I' acentuados
				return 4;
			} else if(word[i+1] >= 146 && word[i+1] <= 148) { // 'O' acentuados
				return 6;
			} else if(word[i+1] >= 153 && word[i+1] <= 155) { // 'U' acentuados
				return 8;
			} else if(word[i+1] >= 168 && word[i+1] <= 170) { // 'e' acentuados
				return 3;
			} else if(word[i+1] >= 172 && word[i+1] <= 174) { // 'i' acentuados
				return 4;
			} else if(word[i+1] >= 178 && word[i+1] <= 181) { // 'o' acentuados
				return 6;
			} else if(word[i+1] >= 185 && word[i+1] <= 187) { // 'u' acentuados
				return 8;
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

unsigned long getIndex(unsigned char *word) {
	int i = 0;
	unsigned long n = 0;
	while(word[i] != '\0') {
		n = (n*10) + getKey(word, i);
		i++;
		if(word[i-1] == 195) i++;
	}
	return n;
}

Word *createWord(unsigned long index, unsigned char *word) {
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

int hash(unsigned long x) {
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

int toLower(unsigned char* str) {
	if(str[0] == 195) {
		if(str[1] >= 128 && str[1] <= 131) { // 'A' acentuados
			str[1] = 160 + (str[1]-128);
			return 1;
		} else if(str[1] == 135) { // 'Ç'
			str[1] = 167;
			return 1;
		} else if(str[1] >= 136 && str[1] <= 138) { // 'E' acentuados
			str[1] = 168 + (str[1]-136);
			return 1;
		} else if(str[1] >= 140 && str[1] <= 142) { // 'I' acentuados
			str[1] = 172 + (str[1]-140);
			return 1;
		} else if(str[1] >= 146 && str[1] <= 148) { // 'O' acentuados
			str[1] = 178 + (str[1]-146);
			return 1;
		} else if(str[1] >= 153 && str[1] <= 155) { // 'U' acentuados
			str[1] = 185 + (str[1]-153);
			return 1;
		} else {
			return 0;
		}
	} else {
		str[0] = tolower(str[0]);
		return 1;
	}
}

void insertTable(Word *word) {
	int h = hash(word->index);

	toLower(word->str);

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

void readFile(char *filename1, char *filename2) {
	FILE *fp = fopen(filename1, "r");
	if(fp == NULL) {
		fp = fopen(filename2, "r");
		if(fp == NULL) return;
	}

	char temp[100];
	unsigned char word[50];
	
	while(fgets(temp, 100, fp)) {
		if(temp[strlen(temp)-1] == '\n') {
			temp[strlen(temp)-1] = '\0';
		}
		int i = 0;
		int j = 0;
		//printf("\ntemp: %s\n", temp);
		while(temp[max((i-1), 0)] != '\0') {
			//printf("temp[i]='%c' ", temp[i]);
			if(temp[i] == '\0' || isdigit(temp[i]) || temp[i] == ' ' || temp[i] == ',' || temp[i] == '(' || temp[i] == ')' || temp[i] == ';' || temp[i] == ':' || temp[i] == '.' || temp[i] == '"' || temp[i] == '-' || temp[i] == '?' || temp[i] == '!' || temp[i] == '\'') {
				if(strlen((char*) word) != 0) {
					//printf("\n%ld", getIndex(word));
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

    if(table[h] == NULL) {
		return NULL;
	}



    /*if(x <= 9999) {
    	if(table[h] == NULL) {
    		return ((unsigned char *)"END");
    	}
        List find;
        if(contador == 0 ) {
            return (table[h]->word->str);
        } else if(contador > 0) {
            find = table[h];
            while (contador > 0) {
                if (find == NULL) {
                    contador = 0;
                    return ((unsigned char *)"END");
                } else {
                    contador--;
                }
                find = find->next;
            }
            return (find->word->str);
        }
    } else if(x > 9999) {
        List find;
        if(contador == 0) {
            for (find = table[h]; find != NULL; find = find->next) {
                if(find->word->index == x) {
                    return (find->word->str);
                }
            }
        } else if(contador > 0) {
            find = table[h];
            for (find = table[h]; find != NULL; find = find->next) {
                if (find->word->index == x && contador > 0) {
                    contador--;
                } else if (find->word->index == x && contador == 0) {
                    return (find->word->str);
                }
            }
        }
    }*/
    return ((unsigned char *)"END");
}

void saveFile() {
    setlocale(P_ALL, "pt_PT.UTF-8");
    FILE *fp = fopen("cache.txt", "w");
    List file;
    for (int h = 1; h < (M - 1); h++) {
        if(table[h] != NULL) {
            file = table[h];
            while(file != NULL) {
                while(file->word->count > 0) {
                    fprintf(fp, "%s ", file->word->str);
                    file->word->count --;
                }
                fprintf(fp, "\n");
                file = file->next;
            }
        }
    }
}

void printList(List list) {
    while(list != NULL) {
        printf("%s %d %ld\n", list->word->str, list->word->count, list->word->index);
        list = list->next;
    }
}