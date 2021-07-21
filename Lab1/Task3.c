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

//удаляет пробелы
void removeSpaces(char *const str) {
	for (int i = 0; str[i]; ++i) {
		if(str[i] == ' ') {
			int j;
			for (j = i + 1; str[j] && str[j] == ' '; ++j);
			strcpy(str + i, str + j);
		}
	}
}

//Проверка того, что символы слева равны символам справа
int checkEqualParts(char *const str, int indexL, int indexR) {
	int level;
	for(level = 0; str[indexL] == str[indexR] && indexL >= 0 && indexR != '\0'; --indexL, ++indexR, ++level);
	return level * 2;
}

int main() {
	char *str;
	int maxSize = 1;

	//получаем входную строку
	if ( !(str = readString()) ) {
		printf("Cant read string");
		exit(1);
	}

	//Удаляет пробелы
	removeSpaces(str);

	//Алгоритмы нахождения отличаются для полиндромов четного и нечетного размера
	for(int i = 1, size; str[i]; ++i) {
		//Проверка на четный полиндром
		size = checkEqualParts(str, i - 1, i);
		if(size > maxSize) {
			maxSize = size;
		}
		//Проверка на нечетный полиндром
		size = checkEqualParts(str, i - 1, i + 1) + 1;
		if(size > maxSize) {
			maxSize = size;
		}
	}

	for(int i = 1; str[i]; ++i) {
		//Проверка на то, что в тексте есть полиндромы
		if( maxSize <= 1 )
			break;
		//Различная обработка для полиндромов четного и нечетного размера
		if( maxSize % 2 == 0 && checkEqualParts(str, i - 1, i) == maxSize ) {
			strcpy(str + i - maxSize / 2, str + i + maxSize / 2);
			i -= (maxSize) / 2 + 1;
		}
		if( maxSize % 2 == 1 && checkEqualParts(str, i - 1, i + 1) + 1 == maxSize ) {
			strcpy(str + i - (maxSize - 1) / 2, str + i + 1 + (maxSize - 1) / 2);
			i -= (maxSize - 1) / 2 + 1;
		}
	}

	printf("Result %s\n", str);

	free(str);
	getchar();
	return 0;
}