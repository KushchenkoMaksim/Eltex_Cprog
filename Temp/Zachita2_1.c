#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listElem{
    int *masIn;
    lestElem* next;
} listElem;

typedef struct list{
    listElem* front;
    listElem* back;
} list;

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

list * getAscendingParts(int *const masIn, int size) {
	list *masOut;
	int * example;
	
	//Выделяет память под массив невозрастающих частей
	if ( !(masOut = (list *)malloc(sizeof(list))) ) {
		return 0;
	}

	//Выделяет память под массив невозрастающих частей
	if ( !(example = (int *)malloc(sizeof(int ) * (size + 1))) ) {
		return 0;
	}
	push(masOut, example);
	
	for (int i = 0; i < size; ) {
		int nextPart;
		int partSize;

		//Находим где заканчивается возрастающая часть и получаем её размер
		nextPart = checkAscendingPart(masIn, size, i);
		partSize = nextPart - i;
		if ( partSize != 1) {
			//Если есть возрастающая часть
			++masCount;
			if ( !(example = (int *)malloc(sizeof(int ) * (partSize + 1))) ) {
	            push(masOut, example);
				return 0;
			}
			example = masOut->back->masIn;
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
	for (listElem *cur = mas->front, next; cur->next; cur = next, ++i) {
	    next = cur->next;
		free(cur->masIn);
	}
	free(mas);
}

//Выводит список на экран
void printMas(list * mas) {
    int i = 0;
	for (listElem *cur = mas->front; cur->next; cur = cur->next, ++i) {
		printf("Row %d: ", i);
		for (int j = 1; j <= (cur->masIn)[0]; ++j) {
			printf("%d, ", (cur->masIn)[j]);
		}
		printf("\n");
	}
}

int main() {
	int mas[] = { 1, 2, 3, 2, 1, 2, 3 };
	list * result = getAscendingParts(mas, sizeof(mas) / sizeof(int));

	printMas(result);

	freeMas(result);
	getchar();
	return 0;
}
