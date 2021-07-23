/*
Создает строку и копирует туда посимвольно
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

char * findRepeatingSym(char *str) {
    char *strOut;
	pair *repeating;
	int outIndex;
	
	outIndex = 0;
    strOut = (char *)malloc(strlen(str) + 1);
	
	repeating = (pair *)malloc(sizeof(pair) * strlen(str));
	memset(repeating, 0, sizeof(pair) * strlen(str));
	
	for(int i = 0; str[i]; ++i) {
		if(!checkSym(repeating, str[i])) {
		    strOut[outIndex++] = str[i];
		}
	}
	strOut[outIndex] = '\0';
	free(repeating);
	return strOut;
}

int main() {
    char *result = findRepeatingSym("123 ABC abc 12345");
    printf("%s\n", result);
    free(result);
	return 0;
}
