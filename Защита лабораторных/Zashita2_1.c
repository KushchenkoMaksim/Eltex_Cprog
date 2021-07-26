/*
Выполнить первое задание второй лабы со связанным списком.

Первое задание второй лабы:
Функция получает линейный массив целых, находит в нем последовательности подряд
возрастающих значений и возвращает их в динамическом массиве указателей на линейные
массивы (аналог двумерного массива). В каждом из линейных динамических массивов
содержится копия возрастающей последовательности, начиная с индекса 1, а под
индексом 0 содержится его длина. Невозрастающие значения включаются в отдельный массив,
добавляемый в конец (или начало) массива указателей.  
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Один элемент списка
typedef struct listElem{
    int *masIn;
    struct listElem *next;
} listElem;

//Список
typedef struct list{
    listElem* front;
    listElem* back;
} list;

//Добавить элемент в конец списка.
void push(list *mas, int *inputArray) {
    if(mas->back) {
        mas->back->next = (listElem *)malloc(sizeof(listElem));
        mas->back = mas->back->next;
        mas->back->masIn = inputArray;
        mas->back->next = 0;
    }
    else {
        mas->front = (listElem *)malloc(sizeof(listElem));
        mas->back = mas->front;
        mas->back->masIn = inputArray;
        mas->back->next = 0;
    }
}

//Возвращает индекс на котором числа перестают возрастать
int checkAscendingPart(int *const masIn, int size, int index) {
	for (int last = masIn[index]; ++index < size && last < masIn[index]; last = masIn[index]);
	return index;
}

//Основная функция
list * getAscendingParts(int *const masIn, int size) {
	list *masOut;
	int * example;
	
	//Выделяет память под список
	if ( !(masOut = (list *)malloc(sizeof(list))) ) {
		return 0;
	}
	memset(masOut, 0, sizeof(list));

	//Выделяет память под массив невозрастающих частей
	if ( !(example = (int *)malloc(sizeof(int ) * (size + 1))) ) {
		return 0;
	}
	memset(example, 0, sizeof(int ) * (size + 1));
	push(masOut, example);
	
	for (int i = 0; i < size; ) {
		int nextPart;
		int partSize;

		//Находим где заканчивается возрастающая часть и получаем её размер
		nextPart = checkAscendingPart(masIn, size, i);
		partSize = nextPart - i;
		if ( partSize != 1) {
			//Если есть возрастающая часть
			if ( !(example = (int *)malloc(sizeof(int ) * (partSize + 1))) ) {
				return 0;
			}
			push(masOut, example);
			example[0] = partSize;
			memcpy(example + 1, masIn + i, sizeof(int) * (partSize));
		}
		else {
			//Если есть убывающая часть
			example = masOut->front->masIn;
			++(example[0]);
			example[example[0]] = masIn[i];
		}
		i = nextPart;
	}
	return masOut;
}

//Функции для тестирования

//Освобождает память для двумерного массива
void freeMas(list * mas) {
	for (listElem *cur = mas->front, *next; cur; cur = next) {
	    next = cur->next;
		free(cur->masIn);
	}
	free(mas);
}

//Выводит список на экран
void printMas(list * mas) {
    int i = 0;
	for (listElem *cur = mas->front; cur; cur = cur->next, ++i) {
		printf("Row %d: ", i);
		for (int j = 1; j <= (cur->masIn)[0]; ++j) {
			printf("%d, ", (cur->masIn)[j]);
		}
		printf("\n");
	}
}

int main() {
	int mas[] = { 4, 5, 6, 3, 1, 2, 3  };
	list * result = getAscendingParts(mas, sizeof(mas) / sizeof(int));

	printMas(result);

	freeMas(result);
	getchar();
	return 0;
}
