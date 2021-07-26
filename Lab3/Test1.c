#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct product {
	char * name;
	int count;
	int priceInNegE2;
	int tradeMarginInNegE2;
} product;

typedef struct productArray {
	product *productsArray;
	int productsMaxSize;
	int productsCount;
} productArray;

typedef union productField
{
	char * name;
	double price;
	int count;
	float tradeMargin;
} productField;

int addProduct(productArray *const mas, char *const str);//Done
int removeProduct(productArray *const mas, int index);//Done
void showProducts(productArray *const mas);//Done
void sortProducts(productArray *const mas, char *const str);
int findElem(productArray *const mas, char *const str, productField data);
int changeElem(productArray *const mas, int index);//Done

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

int ignoreSpaces(char *const str, int i) {
	for(; str[i] == ' ' || str[i] == '\t'; ++i);
	return i;
}

int fillProductStructer(product *const elem, char *const str) {
	//Начинаем переводить строку в структуру.
	char * word;
	int i = 0;
	int maxSize;
	int count;

//Игнорируем пробелы в начале
	i = ignoreSpaces(str, i);
	if( str[i] == '\0')
		return -1;

//Выделяем память под name в product и копируем туда запись
	if ( !(elem->name = (char *)malloc(sizeof(char) * 10)) )
		return -1;

	for(maxSize = 10, count = 0; str[i] && str[i] != ' ' && str[i] != '\t'; ++count, ++i) {
		//Расширяем выделенную память, если выходим за пределы
		if(count == maxSize - 1) {
			maxSize += 10;
			if ( !(elem->name = (char *)realloc(elem->name, sizeof(char) * maxSize)) )
				return -1;
		}
		elem->name[count] = str[i];
	}
		
	elem->name[count] = '\0';
	if ( !(elem->name = (char *)realloc(elem->name, (count + 1) * sizeof(char))) )
		return -1;
	
	i = ignoreSpaces(str, i+1);

//Заполняем поле count
	elem->count = 0;
	for(;str[i] && str[i] != ' ' && str[i] != '\t'; ++i) {
		if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		elem->count *= 10;
		elem->count += (str[i] - '0');
	}
	
	i = ignoreSpaces(str, i+1);

//Заполняем поле price так, что последние 2  разряда обозначают десятую и сотую часть числа
	elem->priceInNegE2 = 0;
	int flagToStop = -1;
	for(; str[i] && str[i] != ' ' && str[i] != '\t'; ++i) {
		//После встречи с точкой мы считываем только 2 числа
		if(str[i] == '.' || str[i] == ',') {
			flagToStop = 3;
			continue;
		}
		else if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		//Флаг уменьшается каждый ход, пока не достигнет 0
		if(flagToStop > 0) {
			--flagToStop;
		}
		//Считываем пока флаг != 0
		if(flagToStop) {
			elem->priceInNegE2 *= 10;
			elem->priceInNegE2 += (str[i] - '0');
		}
	}
	
	//Если в тексте не было '.' поправим для коректного отображения
	if(flagToStop == -1) {
		elem->priceInNegE2 *= 100;
	}

	i = ignoreSpaces(str, i+1);

//Заполняем поле tradeMargin так, что последние 2  разряда обозначают десятую и сотую часть числа
	elem->tradeMarginInNegE2 = 0;
	flagToStop = -1;
	for(; str[i] && str[i] != ' ' && str[i] != '\t'; ++i) {
		//После встречи с точкой мы считываем только 2 числа
		if(str[i] == '.' || str[i] == ',') {
			flagToStop = 3;
			continue;
		}
		else if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		//Флаг уменьшается каждый ход, пока не достигнет 0
		if(flagToStop > 0) {
			--flagToStop;
		}
		//Считываем пока флаг != 0
		if(flagToStop) {
			elem->tradeMarginInNegE2 *= 10;
			elem->tradeMarginInNegE2 += (str[i] - '0');
		}
	}
	//Если в тексте не было '.' поправим для коректного отображения
	if(flagToStop == -1) {
		elem->tradeMarginInNegE2 *= 100;
	}
	return 0;
}

int addProduct(productArray *const mas, char *const str) {
//Выделяем память под массив при добавлении первой записи и расширяем по мере необходимости
	if (!mas->productsCount && !(mas->productsArray = (product *)malloc(sizeof(product) * mas->productsMaxSize)) )
		return 0;
	
	if(mas->productsCount == mas->productsMaxSize) {
		mas->productsMaxSize += 5;
		if ( !(mas->productsArray = (product *)realloc(mas->productsArray, sizeof(product) * mas->productsMaxSize)) )
			return -1;
	}

	if( fillProductStructer(&(mas->productsArray[mas->productsCount]), str) == -1) {
		return -1;
	}

	++(mas->productsCount);
	return (mas->productsCount - 1);
}

void showProducts(productArray *const mas) {
	for(int i = 0; i != mas->productsCount; ++i) {
		printf("Row %d: %s    %d    ", i, mas->productsArray[i].name, mas->productsArray[i].count);
		printf("%d.%d    ", mas->productsArray[i].priceInNegE2 / 100, mas->productsArray[i].priceInNegE2 % 100);
		printf("%d.%d\n", mas->productsArray[i].tradeMarginInNegE2 / 100, mas->productsArray[i].tradeMarginInNegE2 % 100);
	}
}

void freeArray(productArray *const mas) {
	for(int i = 0; i != mas->productsCount; ++i) {
		free(mas->productsArray[i].name);
	}
	free(mas->productsArray);
	mas->productsCount = 0;
	mas->productsMaxSize = 10;
}

int removeProduct(productArray *const mas, int index) {
	if(index >= mas->productsCount) {
		return -1;
	}
	free(mas->productsArray[index].name);
	for(;index < mas->productsCount - 1; ++index) {
		mas->productsArray[index] = mas->productsArray[index + 1];
	}
	--(mas->productsCount);
	return 0;
}

int changeElem(productArray *const mas, int index) {
	char *str = readString();
	if(index >= mas->productsCount)
		return -1;
	if(fillProductStructer(&(mas->productsArray[index]), str) == -1)
		return -1;
	free(str);
	return 0;
}

int main() {
	productArray mas;
	mas.productsMaxSize = 10;
	mas.productsCount = 0;
	if( addProduct(&mas, "chair    2    10.34    0.5") == -1) {
		printf("Error\n");
	}
	if( addProduct(&mas, "table    124314    123406.34    0857.5") == -1) {
		printf("Error\n");
	}
	if( addProduct(&mas, "carpet    21312    10757.348757    78570.5") == -1) {
		printf("Error\n");
	}
	if( addProduct(&mas, "sofa    1    0    100") == -1) {
		printf("Error\n");
	}
	showProducts(&mas);
	removeProduct(&mas, 0);
	showProducts(&mas);
	removeProduct(&mas, 1);
	showProducts(&mas);
	removeProduct(&mas, 1);
	showProducts(&mas);
	changeElem(&mas, 0);
	showProducts(&mas);
	freeArray(&mas);
	getchar();
}