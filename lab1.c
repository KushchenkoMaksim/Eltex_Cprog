#include <stdio.h>
int getNumInBaseFromStr(char *str, int base, int digits) {
	int multiplier = 1;
	int num = 0;
	for (int i = 1; i < digits; i++, multiplier*=base);
	for (int i = 0; i < digits; i++) {
		num += (str[i] - '0') * multiplier;
	}
	return num;
}

int readString(char *str) {
	int strSize = 10;
	int delta = 10;
	if ( !(str = (char *)malloc(sizeof(char) * strSize) )
		return 0;
	char sym;
	int i = 0;
	
	do {
		scanf("%c", &sym);

		if(i == strSize) {
			strSize += delta;
			if ( !(str = (char *)realloc(str, sizeof(char) * strSize) )
				return 0;
		}
		
		str[i++] = sym;

	}
	while(sym != '\0');
	if ( !(str = (char *)realloc(str, i * sizeof(char)) )
		return 0;
	return 1;
}

int main() {
	char *str;
	if ( !readString(str) ) {
		perror("Cant read string");
		exit(1);
	}
	for (int i = 0; str[i]; ++i) {
		if (str[i] <= '9' && str[i] >= '0') {
			
		}
	}
	
	return 0;
}
