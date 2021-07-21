#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Динамически выделяет память под строку, и считывает в неё с клавиатуры
char * readString() {
	int strSize = 10;
	int delta = 10;
	char *str;
	if ( !(str = (char *)malloc(sizeof(char) * strSize)) )
		return 0;
	char sym;
	int i = 0;
	
	printf("Type line of text\n");
	do {
		sym = getchar();
		if(i == strSize) {
			strSize += delta;
			if ( !(str = (char *)realloc(str, sizeof(char) * strSize)) )
				return 0;
		}
		
		str[i++] = sym;

	}
	while (sym != '\0' &&  sym != '\n' &&  sym != '\r');
	str[i-1] = '\0';
	if ( !(str = (char *)realloc(str, i * sizeof(char))) )
		return 0;
	return str;
}

//Находит и возвращает указатель на самую глубокую скобку. Если скобок нет - 0
char * findDeepestBrackets(char *str) {
	char * deepest = 0;
	int level = 0;
	int maxLevel = 0;
	for (int i = 0; str[i]; ++i) {
		if (str[i] == '{') {
			++level;
			if (level > maxLevel) {
				deepest = str + i;
				maxLevel = level;
			}
		}
		else if (str[i] == '}') {
			--level;
		}
	}
	return deepest;
}

int main() {
	char *strIn;
	char *strOut;

	//получаем входную строку
	if ( !(strIn = readString()) ) {
		printf("Cant read string");
		exit(1);
	}

	//создаем выходную строку
	if ( !(strOut = (char *)malloc(strlen(strIn) * sizeof(char))) ) {
		exit(1);
	}
	strOut[0] = '\0';

	//Из функции получаем указатель на самую внутреннюю пару скобок на данный момент.
	for (char *deepest = findDeepestBrackets(strIn); deepest != 0; deepest = findDeepestBrackets(strIn) ) {
		int i;
		//Считаем длину фрагмента и переносим из входной строки в выходную
		for (i = 0; deepest[i] != '}'; ++i);
		strncat(strOut, deepest + 1, i - 1);
		strcpy(deepest, deepest + i + 1);
	}
	//Текст без скобок тоже переносим в выходную строку
	strcat(strOut, strIn);
	printf("Result %s\n", strOut);
	free(strIn);
	free(strOut);
	getchar();
	return 0;
}