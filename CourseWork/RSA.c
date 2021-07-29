#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct intArray {
	int * array;
	int maxSize;
	int count;
	int delta;
} intArray;

void setUpIntArray(intArray *const mas, int maxSize, int delta) {
	mas->count = 0;
	mas->maxSize = maxSize;
	mas->delta = delta;
}

int pushIntArray(intArray *const mas, int item) {
	//Если масив пуст, то выделяем под него память
	if(!mas->count && !(mas->array = (int *)malloc(sizeof(int) * mas->maxSize))) {
		return -1;
	}
	//Расширяем выделенную память, если выходим за пределы
	if(mas->count == mas->maxSize) {
		mas->maxSize += mas->delta;
		if ( !(mas->array = (int *)realloc(mas->array, sizeof(int) * mas->maxSize)) )
			return -1;
	}
	mas->array[mas->count] = item;
	++(mas->count);
	return mas->count - 1;
}
/*
void freeIntArray(intArray *const mas) {
	free(mas->array);
	mas->count = 0;
	mas->maxSize = 10;
}
*/
typedef struct charArray {
	char * array;
	int maxSize;
	int count;
	int delta;
} charArray;

void setUpCharArray(charArray *const mas, int maxSize, int delta) {
	mas->count = 0;
	mas->maxSize = maxSize;
	mas->delta = delta;
}

int pushCharArray(charArray * mas, char item) {
	//Если масив пуст, то выделяем под него память
	if(!mas->count && !(mas->array = (char *)malloc(sizeof(char) * mas->maxSize))) {
		return -1;
	}
	//Расширяем выделенную память, если выходим за пределы
	if(mas->count == mas->maxSize - 1) {
		mas->maxSize += mas->delta;
		if ( !(mas->array = (char *)realloc(mas->array, sizeof(char) * mas->maxSize)) )
			return -1;
	}
	mas->array[mas->count] = item;
	++(mas->count);
	mas->array[mas->count] = '\0';
	return mas->count - 1;
}
/*
void freeCharArray(charArray *const mas) {
	free(mas->array);
	mas->count = 0;
	mas->maxSize = 10;
}
char * intToStr(int number) {
	char *str;
	int i;
	int j;
	if(!(str = (char *)malloc(sizeof(char) * 11))) {
		return 0;
	}
	for(i = 1; number > i * 10; i *= 10);
	for(j = 0; i; i /= 10, ++j) {
		str[j] = number / i;
		number %= i;
	}
	str[j] = '\0';
	return str;
}
*/

typedef struct RSA {
	int p; // два простых числа
	int q;
	int fi; //Функция Эйлера получателя
	int d; // private key
	int n; // n получателя
	int e; //случайная открытая экспонента
} RSA;


int evklid(int U, int V, int restU, int restV)
{
	if (V == 0)
		return restU;
	int q = U / V;
	return evklid(V, U % V, restV, restU - q * restV);
}

//Устанавливает начальные значения для структуры
void setUpRSA(RSA *const rsa, int e, int p, int q) {
	rsa->p = p;
	rsa->q = q;
	rsa->n = p * q;
	rsa->fi = (p - 1) * (q - 1);
	
	rsa->e = e;
	

	//Находим мультипликативно обратное число по алгоритму евклида
	int V = rsa->e;
	int U = rsa->fi;
	if (U < V) {
		rsa->d = evklid(V, U, 1, 0);
		if (rsa->d < 0)
			rsa->d += V;
	}
	else {
		rsa->d = evklid(U, V, 0, 1);
		if (rsa->d < 0)
			rsa->d += U;
	}

}

//Функция возводит number в степень expo считая остаток от деления на deter
int pow_special(int number, int expo, int deter)
{
	long long result = 1;
	for(int i = 0; i < expo; ++i) {
		result *= number;
		result %= deter;
	}
	return (int)result;
}

intArray * makeSigne(intArray *const signe, int hash, int d, int n)
{
	for (int i = 0; msg[i]; ++i) {
		pushIntArray(signe, pow_special(msg[i], d, n));
	}
	return signe;
}
int getHash(intArray *const signe, int e, int n)
{
	int hash = 0;
	for (int i = 0; i < signe->count; ++i) {
		hash *= 10;
		hash += pow_special(signe->array[i], e, n);
	}
	return hash;
}



int makeHash(char *const str) {
	const int alphabet = 256;
	const int mod = 1e9+7;
	long long hash = 0;
	int m = 1;
	for (int i = 0; str[i]; ++i) {
    	hash = (hash + m * str[i]) % mod;
    	m = (m * alphabet) % mod;
	}
	return (int)hash;
}

int main()
{
	RSA gen;
	intArray signe;
	charArray hash;
	char msg[] = "1234";

	setUpIntArray(&signe, 10, 10);
	setUpCharArray(&hash, 10, 10);
	setUpRSA(&gen, 17, 3557, 2579);
	makeSigne(&signe, msg, gen.d, gen.n);

	printf("Msg is: %s\nSigne is: ", msg);
	for(int i = 0; i < signe.count; ++i) {
		printf("%d ", signe.array[i]);
	}
	printf("\n");

	getHash(&hash, &signe, gen.e, gen.n);
	printf("Decoded hash: %s\n", hash.array);
	printf("Control hash: %d", )

	free(signe.array);
	free(hash.array);
	
	getchar();
	return 0;
}
