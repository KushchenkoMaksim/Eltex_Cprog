/*
Программа ищет повторы символов в строке и выводит на экран. Игнорирует регистр.
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

void addSym(pair *const mas, char sym) {
    int i;
	for(i = 0; mas[i].sym; ++i) {
		if (mas[i].sym == toLower(sym)) {
			++(mas[i].count);
			return ;
		}
	}
	mas[i].sym = toLower(sym);
	mas[i].count = 1;
}

void printPairs(pair *const mas) {
	for(int i = 0; mas[i].sym; ++i) {
		printf("%c appeared %d times\n", mas[i].sym, mas[i].count);
	}
}

void findRepeatingSym(char *str) {
	pair *repeating;
	repeating = (pair *)malloc(sizeof(pair) * strlen(str));
	memset(repeating, 0, sizeof(pair) * strlen(str));
	for(int i = 0; str[i]; ++i) {
		addSym(repeating, str[i]);
	}
	printPairs(repeating);
	free(repeating);
}

int main() {
    findRepeatingSym("1ABC2abc");
	return 0;
}rn 0;
}
