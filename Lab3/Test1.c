#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct product {
	char * name;
	double price;
	int count;
	float tradeMargin;
} product;

typedef struct productsArray {
	product *array;
	int addProduct(char *const str);
	int removeProduct(int index);
	void printArray();
	void sortArray(char *const str);
	int findElem(char *const str, void *const data);
	void changeElem(int index);
	
} productsArray;

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


