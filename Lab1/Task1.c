#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Проверка на то, что передан символ-число
int isNumber(char sym) {
	if (sym <= '9' && sym >= '0')
		return 1;
	return 0;
}
//Получение основания системы счисления и количество разрядов числа
int getBaseAndDigitsFromStr(char* str, int *digits) {
	int base = 0;
	int i;
	for (i = 0; isNumber(str[i]); ++i)
		if (base < str[i] - '0')
			base = str[i] - '0';
	*digits = i;
	return base+1;
}

//Перевод в нужную систему счисления
int getNumInBaseFromStr(char *str, int base, int digits) {
	int multiplier = 1;
	int num = 0;
	for (int i = 1; i < digits; i++, multiplier*=base);
	for (int i = 0; i < digits; i++, multiplier/=base) {
		num += (str[i] - '0') * multiplier;
	}
	return num;
}

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

int main() {
	char *str;
	int digits;
	int base;
	int number;

	//получаем строку для работы
	if ( !(str = readString()) ) {
		printf("Cant read string");
		exit(1);
	}
	for (int i = 0; str[i]; ++i) {
		digits = 0;
		base = 0;
		number = 0;
		if (isNumber(str[i])) {
			base = getBaseAndDigitsFromStr(&str[i], &digits);
			if ( base ) {
				number = getNumInBaseFromStr(&str[i], base, digits);
			}
			str[i] = number % 255;
			strcpy(&str[i + 1], &str[i + digits]);
		}
	}
	printf("Result: %s\n", str);
	free(str);
	getchar();
	return 0;
}
