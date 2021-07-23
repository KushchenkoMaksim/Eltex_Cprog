#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Проверка того, что символы слева равны символам справа
int checkEqualParts(char *const str, int indexL, int indexR) {
	int level;
	for(level = 0; str[indexL] == str[indexR] && indexL >= 0 && indexR != '\0'; --indexL, ++indexR, ++level);
	return level * 2;
}

char ** getFragments(char *const str) {
	char ** masOut;
	int masCount = 0;

	//Выделяет память под массив указателей
	if ( !(masOut = (char **)malloc(sizeof(char *) * strlen(str))) ) {
		return 0;
	}
	memset(masOut, 0, sizeof(char *) * strlen(str));

	//Алгоритмы нахождения отличаются для полиндромов четного и нечетного размера
	for(int i = 1, size; str[i]; ++i) {
		//Проверка на четный полиндром
		size = checkEqualParts(str, i - 1, i);
		if(size >= 7) {
			//Если полиндром подходящий, выделим память под строку и скопируем её
			if ( !(masOut[masCount] = (char *)malloc(sizeof(char ) * (size + 1))) ) {
				return 0;
			}
			strncpy(masOut[masCount], str + i - size / 2, size);
			masOut[masCount][size] = '\0';
			++masCount;
		}
		//Проверка на нечетный полиндром
		size = checkEqualParts(str, i - 1, i + 1) + 1;
		if(size >= 7) {
			//Если полиндром подходящий, выделим память под строку и скопируем её
			if ( !(masOut[masCount] = (char *)malloc(sizeof(char ) * (size + 1))) ) {
				return 0;
			}
			strncpy(masOut[masCount], str + i - (size - 1) / 2, size);
			masOut[masCount][size] = '\0';
			++masCount;
		}
	}
	return masOut;
}

//Функции для тестирования

//Освобождает память для двумерного массива
void freeMas(char ** mas) {
	for (int i = 0; mas[i]; ++i) {
		free(mas[i]);
	}
	free(mas);
}

//Выводит двумерный массив на экран
void printMas(char ** mas) {
	for (int i = 0; mas[i]; ++i) {
		printf("Row %d: %s", i, mas[i]);
		printf("\n");
	}
}

int main() {
	char str[] = "123432151234321";
	char ** result = getFragments(str);

	printMas(result);

	freeMas(result);
	getchar();
	return 0;
}
