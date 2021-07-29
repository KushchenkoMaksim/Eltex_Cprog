#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Динамический массив для хранения подписи
typedef struct intArray {
	int * array;
	int maxSize;
	int count;
	int delta;
} intArray;

//Настройка значений для автоматического расширения массива
void setUpIntArray(intArray *const mas, int maxSize, int delta) {
	mas->count = 0;
	mas->maxSize = maxSize;
	mas->delta = delta;
}


//Добавление элемента в массимв
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

//Структура для хранения значений различных параметров RSA
typedef struct RSA {
	int p; // два простых числа
	int q;
	int fi; //Функция Эйлера получателя
	int d; // private key
	int n; // n получателя
	int e; //открытая экспонента ДОЛЖНА БЫТЬ ПРОСТЫМ ЧИСЛОМ
} RSA;

//Расширенный алгоритм Евклида
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
	

	//Алгоритм нахождения числа обратного e по модулю fi с помощью алгоритма Евклида
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

//Делает подпись для числа hash
intArray * makeSigne(intArray *const signe, int hash, int d, int n)
{
	int i;
	int j;
	for(i = 1; hash > i * 10; i *= 10);
	for(j = 0; i != 0; i /= 10, ++j) {
		pushIntArray(signe, pow_special(hash / i + '0', d, n));
		hash %= i;
	}

	return signe;
}

//Получает число hash из подписи signe
int getHash(intArray *const signe, int e, int n)
{
	int hash = 0;
	for (int i = 0; i < signe->count; ++i) {
		hash *= 10;
		hash += pow_special(signe->array[i], e, n) - '0';
	}
	return hash;
}

//Получить хэш строки
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
	char msg[] = "asdbhja scajb";
	int hash;

	setUpIntArray(&signe, 10, 10);
	setUpRSA(&gen, 17, 3557, 2579);

	hash = makeHash(msg);
	makeSigne(&signe, hash, gen.d, gen.n);
	printf("Msg is: %s\nHash is: %d\nSigne is: ", msg, hash);
	for(int i = 0; i < signe.count; ++i) {
		printf("%d ", signe.array[i]);
	}
	printf("\n");


	hash = getHash(&signe, gen.e, gen.n);
	printf("Decoded hash: %d\n", hash);
	printf("Control hash: %d\n", makeHash(msg));

	free(signe.array);
	
	getchar();
	return 0;
}
