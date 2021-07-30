#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct product {
	char * name;
	int count;
	int price;
	int tradeMargin;
} product;

typedef struct productArray {
	product *productsArray;
	int productsMaxSize;
	int productsCount;
} productArray;

//Сортирует массив
void sortProducts(productArray *const mas, char *const field) {
	if(strcmp(field, "price") == 0) {
		for(int i = 0; i < mas->productsCount - 1; ++i) {
			for(int j = 0; j < mas->productsCount - 1 - i; ++j) {
				if(mas->productsArray[j].price > mas->productsArray[j + 1].price){
					product temp;
					memcpy(&temp, mas->productsArray + j, sizeof(product));
					memcpy(mas->productsArray + j, mas->productsArray + j + 1, sizeof(product));
					memcpy(mas->productsArray + j + 1, &temp, sizeof(product));
				}
			}
		}
	}
	else if(strcmp(field, "name") == 0) {
		for(int i = 0; i < mas->productsCount - 1; ++i) {
			for(int j = 0; j < mas->productsCount - 1 - i; ++j) {
				if(strcmp(mas->productsArray[j].name, mas->productsArray[j + 1].name) > 0){
					product temp;
					memcpy(&temp, mas->productsArray + j, sizeof(product));
					memcpy(mas->productsArray + j, mas->productsArray + j + 1, sizeof(product));
					memcpy(mas->productsArray + j + 1, &temp, sizeof(product));
				}
			}
		}
	}
	else if(strcmp(field, "count") == 0) {
		for(int i = 0; i < mas->productsCount - 1; ++i) {
			for(int j = 0; j < mas->productsCount - 1 - i; ++j) {
				if(mas->productsArray[j].count > mas->productsArray[j + 1].count){
					product temp;
					memcpy(&temp, mas->productsArray + j, sizeof(product));
					memcpy(mas->productsArray + j, mas->productsArray + j + 1, sizeof(product));
					memcpy(mas->productsArray + j + 1, &temp, sizeof(product));
				}
			}
		}
	}
	else if(strcmp(field, "tradeMargin") == 0) {
		for(int i = 0; i < mas->productsCount - 1; ++i) {
			for(int j = 0; j < mas->productsCount - 1 - i; ++j) {
				if(mas->productsArray[j].tradeMargin > mas->productsArray[j + 1].tradeMargin){
					product temp;
					memcpy(&temp, mas->productsArray + j, sizeof(product));
					memcpy(mas->productsArray + j, mas->productsArray + j + 1, sizeof(product));
					memcpy(mas->productsArray + j + 1, &temp, sizeof(product));
				}
			}
		}
	}
	else {
		printf("No field named %s found\n", field);
	}
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

//Возвращает число из строки
int getIntFromStr(char *const str) {
	int number = 0;
	for(int i = 0; str[i]; ++i) {
		if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		number *= 10;
		number += str[i] - '0';
	}
	return number;
}

//Возвращает Int, два последних разряда кодируют вещественную часть, старшие - целую
int getCodedFloatFromStr(char *const str, int *index) {
	int number;
	int i;

	if(index) {
		i = *index;
	}
	else {
		i = 0;
	}
	//Заполняем целую часть числа
	number = 0;
	for(; str[i] != '.' && str[i] != ',' && str[i] && str[i] != ' ' && str[i] != '\t'; ++i) {
		if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		number *= 10;
		number += (str[i] - '0');
	}
	number *= 100;
	if(str[i] == '.' || str[i] == ',') {
		++i;
	}
	//Заполняем вещественную часть числа
	for(int j = 10; str[i] && str[i] != ' ' && str[i] != '\t'; ++i, j/=10) {
		if(str[i] > '9' || str[i] < '0') {
			return -1;
		}
		if(j > 0) {
			number += (str[i] - '0') * j;
		}
	}
	if(index) {
		*index = i;
	}
	return number;
}

//Поиск наиболее близкого элемента в массиве
int findElem(productArray *const mas, char *const field, char *const data) {
	if(strcmp(field, "price") == 0) {
		int maxIndex = 0;
		int number = getCodedFloatFromStr(data, 0);
		int eps = -1;
		for(int i = 0; i < mas->productsCount; ++i) {
			int temp = mas->productsArray[i].price  - number;
			if (temp < 0) {
				temp *= -1;
			}
			if(eps == -1 || eps > temp) {
				eps = temp;
				maxIndex = i;
			}
			if (!eps) {
				return maxIndex;
			}
		}
		return maxIndex;
	}
	else if(strcmp(field, "name") == 0) {
		for(int i = 0; i < mas->productsCount; ++i) {
			if(!strcmp(mas->productsArray[i].name, data)) {
				return i;
			}
		}
		return -1;
	}
	else if(strcmp(field, "count") == 0) {
		int maxIndex = 0;
		int number = getIntFromStr(data);
		int eps = -1;
		for(int i = 0; i < mas->productsCount; ++i) {
			int temp = mas->productsArray[i].count  - number;
			if (temp < 0) {
				temp *= -1;
			}
			if(eps == -1 || eps > temp) {
				eps = temp;
				maxIndex = i;
			}
			if (!eps) {
				return maxIndex;
			}
		}
		return maxIndex;
	}
	else if(strcmp(field, "tradeMargin") == 0) {
		int maxIndex = 0;
		int number = getCodedFloatFromStr(data, 0);
		int eps = -1;
		for(int i = 0; i < mas->productsCount; ++i) {
			int temp = mas->productsArray[i].tradeMargin  - number;
			if (temp < 0) {
				temp *= -1;
			}
			if(eps == -1 || eps > temp) {
				eps = temp;
				maxIndex = i;
			}
			if (!eps) {
				return maxIndex;
			}
		}
		return maxIndex;
	}
	else {
		printf("No field named %s found\n", field);
		return -1;
	}
}

//Возвращает индекс следующего символа не пробела
int ignoreSpaces(char *const str, int i) {
	for(; str[i] == ' ' || str[i] == '\t'; ++i);
	return i;
}

//Заполняем структуру из строки
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
	//Заполняем поле price так, что два последних разряда кодируют вещественную часть, старшие - целую
	elem->price = getCodedFloatFromStr(str, &i);

	i = ignoreSpaces(str, i+1);
	//Заполняем поле tradeMargin так, что два последних разряда кодируют вещественную часть, старшие - целую
	elem->tradeMargin = getCodedFloatFromStr(str, &i);

	return 0;
}

//Добавляем продукт из строки
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

//Выводит таблицу на экран
void showProducts(productArray *const mas) {
	for(int i = 0; i != mas->productsCount; ++i) {
		printf("Row %d: %s    %d    ", i, mas->productsArray[i].name, mas->productsArray[i].count);
		printf("%d.%d    ", mas->productsArray[i].price / 100, mas->productsArray[i].price % 100);
		printf("%d.%d\n", mas->productsArray[i].tradeMargin / 100, mas->productsArray[i].tradeMargin % 100);
	}
}

//Очистить таблицу
void freeArray(productArray *const mas) {
	for(int i = 0; i != mas->productsCount; ++i) {
		free(mas->productsArray[i].name);
	}
	free(mas->productsArray);
	mas->productsCount = 0;
	mas->productsMaxSize = 10;
}

//Сохранить в файл
int saveToFile(productArray *const mas, char *const filename) {
	FILE *f;
	if(!(f = fopen(filename, "w"))) {
		return -1;
	}
	for(int i = 0; i != mas->productsCount; ++i) {
		fprintf(f, "%s    %d    ", mas->productsArray[i].name, mas->productsArray[i].count);
		fprintf(f, "%d.%d    ", mas->productsArray[i].price / 100, mas->productsArray[i].price % 100);
		fprintf(f, "%d.%d\n", mas->productsArray[i].tradeMargin / 100, mas->productsArray[i].tradeMargin % 100);
	}
	fclose(f);
	return 1;
}

//Загрузить из файла
int readFromFile(productArray *const mas, char *const filename) {

	freeArray(mas);
	int strSize;
	int delta = 10;
	char *str;
	char sym;
	int i;
	FILE *f;
	if(!(f = fopen(filename, "r"))) {
		return -1;
	}
	
	sym = 0;
	while(sym != EOF) {	
		strSize = 10;
		i = 0;
		if ( !(str = (char *)malloc(sizeof(char) * strSize)) )
			return -1;
	
		do {
			sym = getc(f);
			if(i == strSize) {
				strSize += delta;
				if ( !(str = (char *)realloc(str, sizeof(char) * strSize)) )
					return 0;
			}
			str[i++] = sym;

		}
		while (sym != EOF &&  sym != '\n' &&  sym != '\r');
		str[i-1] = '\0';
		if ( !(str = (char *)realloc(str, i * sizeof(char))) )
			return -1;
		if( -1 == addProduct(mas, str)) {
			return -1;
		}
		free(str);
	}
	return 1;
}

//Удаляет продукт из массива
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

//Изменяет элемент с индексом index
int changeElem(productArray *const mas, int index) {
	char *str = readString();
	if(index >= mas->productsCount)
		return -1;
	mas->productsArray[index].count = 0;
	mas->productsArray[index].name = 0;
	mas->productsArray[index].price = 0;
	mas->productsArray[index].tradeMargin = 0;
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
	if( addProduct(&mas, "table    124314    123406.34    0857.5453") == -1) {
		printf("Error\n");
	}
	if( addProduct(&mas, "carpet    21312    10757.348757    78570.5") == -1) {
		printf("Error\n");
	}
	if( addProduct(&mas, "sofa    1    0    100") == -1) {
		printf("Error\n");
	}
	showProducts(&mas);
	printf("\n");

	//Ниже идет ряд тестов
	
	/*saveToFile(&mas, "123.txt");
	freeArray(&mas);
	readFromFile(&mas, "123.txt");
	showProducts(&mas);
	printf("\n");*/

	/*printf("Elem is on %d position\n\n", findElem(&mas, "count", "1"));
	printf("Elem is on %d position\n\n", findElem(&mas, "count", "12000"));
	printf("Elem is on %d position\n\n", findElem(&mas, "price", "10757.348757"));
	printf("Elem is on %d position\n\n", findElem(&mas, "price", "10"));
	printf("Elem is on %d position\n\n", findElem(&mas, "name", "sofa"));
	printf("Elem is on %d position\n\n", findElem(&mas, "name", "chaer"));*/

	/*sortProducts(&mas, "count");
	showProducts(&mas);
	printf("\n");
	sortProducts(&mas, "wtf");
	printf("\n");
	sortProducts(&mas, "name");
	showProducts(&mas);
	printf("\n");*/

	/*removeProduct(&mas, 0);
	showProducts(&mas);
	removeProduct(&mas, 1);
	showProducts(&mas);
	removeProduct(&mas, 1);
	showProducts(&mas);
	changeElem(&mas, 0);
	showProducts(&mas);*/


	freeArray(&mas);
	getchar();
}