#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//����������� �������� ������ ��� ������, � ��������� � �� � ����������
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

//������� � ���������� ��������� �� ����� �������� ������. ���� ������ ��� - 0
char * findDeepestBrackets(char *str) {
	char * deepest = 0;
	int level = 0;
	int maxLevel = 0;
	for (int i = 0; str[i]; ++i) {
		if (str[i] == '{') {
			++level;
			if (level > maxLevel) {
				deepest = str + i;
				maxLevel = level;
			}
		}
		else if (str[i] == '}') {
			--level;
		}
	}
	return deepest;
}

int main() {
	char *strIn;
	char *strOut;

	//�������� ������� ������
	if ( !(strIn = readString()) ) {
		printf("Cant read string");
		exit(1);
	}

	//������� �������� ������
	if ( !(strOut = (char *)malloc(strlen(strIn) * sizeof(char))) ) {
		exit(1);
	}
	strOut[0] = '\0';

	//�� ������� �������� ��������� �� ����� ���������� ���� ������ �� ������ ������.
	for (char *deepest = findDeepestBrackets(strIn); deepest != 0; deepest = findDeepestBrackets(strIn) ) {
		int i;
		//������� ����� ��������� � ��������� �� ������� ������ � ��������
		for (i = 0; deepest[i] != '}'; ++i);
		strncat(strOut, deepest + 1, i - 1);
		strcpy(deepest, deepest + i + 1);
	}
	//����� ��� ������ ���� ��������� � �������� ������
	strcat(strOut, strIn);
	printf("Result %s\n", strOut);
	free(strIn);
	free(strOut);
	getchar();
	return 0;
}