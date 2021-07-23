/*
Создает строку, убирает повторяющиеся символы
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pair{
	char sym;
	int count;
} pair;

char toLower(char sym) {
    if(sym >= 'A' && sym <= 'Z') {
        sym = sym - 'A' + 'a';
    }
    return sym;
}

int checkSym(pair *const mas, char sym) {
    int i;
	for(i = 0; mas[i].sym; ++i) {
		if (mas[i].sym == toLower(sym)) {
			return 1;
		}
	}
	mas[i].sym = toLower(sym);
	mas[i].count = 1;
	return 0;
}

void findRepeatingSym(char *str) {
	pair *repeating;
	
	repeating = (pair *)malloc(sizeof(pair) * strlen(str));
	memset(repeating, 0, sizeof(pair) * strlen(str));
	
	for(int i = 0; str[i]; ++i) {
		if(checkSym(repeating, str[i])) {
		   strcpy(str + i, str + i + 1);
		   --i;
		}
	}
	free(repeating);
}

int main() {
    char str[] = "123 ABC abc 12345";
    findRepeatingSym(str);
    printf("%s\n", str);
	return 0;
}
