
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <random.h>
#include <time.h>

typedef struct intArray {
    int * array;
    int maxSize;
    int count;
} charArray;

int pushArray(charArray *const mas, int number) {
    if(!mas->count && !(mas->array = (char *)malloc(syzeof(char) * mas->maxSize))) {
        return -1;
    }
    //Расширяем выделенную память, если выходим за пределы
	if(mas->count == mas->maxSize) {
		mas->maxSize += 10;
		if ( !(mas->array = (char *)realloc(mas->array, sizeof(char) * mas->maxSize)) )
			return -1;
	}
	mas->array[mas->count] = number;
	++(mas->count);
	return mas->count;
}

int pushCharArray(char *const mas, char *str, int size) {
    if(!size && !(mas->array = (char *)malloc(syzeof(char) * mas->maxSize))) {
        return -1;
    }
    //Расширяем выделенную память, если выходим за пределы
	if(mas->count == mas->maxSize) {
		mas->maxSize += 10;
		if ( !(mas->array = (char *)realloc(mas->array, sizeof(char) * mas->maxSize)) )
			return -1;
	}
	mas->array[mas->count] = number;
	++(mas->count);
	return mas->count;
}

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
void setupRSA(RSA *const rsa, int p, int q) {
    rsa->p = p;
    rsa->q = q;
    rsa->n = p * q;
    rsa->fi = (p - 1) * (q - 1);
    
    srand(time(0));
    rsa->e = rand() % (fi - 1) + 1;
    
    //Находим мультипликативно обратное число по алгоритму евклида
	d = evklid(rsa->fi, rsa->e, 0, 1);
	if (d < 0)
		d += rsa->fi;
}

//Функция возводит number в степень expo считая остаток от деления на deter
int pow_special(int number, int expo, int deter)
{
	int result = 1;
	for(int i = 0; i < expo; ++i) {
		result *= number;
		result %= deter;
	}
	return result;
}



int * encode(char *const text, int e, int n)
{
    intArray mas;
    mas->maxSize = 10;
    mas->count = 0;
    
	for (int i = 0; text[i]; ++i) {
	    pushArray(&mas, pow_special(text[i], e, n));
	}
	return mas->array;
}
char * decode(int * chiper_text, int d, int n)
{
	char * text;
	
	int last = 0;
	for (int i = 0; i < chiper_text->count; ++i) {
		text += pow_special(chiper_text->array[i], d, n);
	}
	return text;
}


int main()
{
    std::string text;
    std::cout << "Type massage: ";
	std::cin >> text;
	RSA a(17);
	RSA b(17);
	std::vector<int32_t> e_text = a.encode(text, b.e, b.n);
	for (int32_t a : e_text) {
		std::cout << a << ' ';
	}
	std::cout << std::endl;
	std::cout << b.decode(e_text) << std::endl;
	
	return 0;
}
