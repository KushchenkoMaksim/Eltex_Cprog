#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//�������� ����, ��� ������� ����� ����� �������� ������
int checkEqualParts(char *const str, int indexL, int indexR) {
	int level;
	for(level = 0; str[indexL] == str[indexR] && indexL >= 0 && indexR != '\0'; --indexL, ++indexR, ++level);
	return level * 2;
}

char ** getFragments(char *const str) {
	char ** masOut;
	int masCount = 0;

	//�������� ������ ��� ������ ����������
	if ( !(masOut = (char **)malloc(sizeof(char *) * strlen(str))) ) {
		return 0;
	}
	memset(masOut, 0, sizeof(char *) * strlen(str));

	//��������� ���������� ���������� ��� ����������� ������� � ��������� �������
	for(int i = 1, size; str[i]; ++i) {
		//�������� �� ������ ���������
		size = checkEqualParts(str, i - 1, i);
		if(size >= 7) {
			//���� ��������� ����������, ������� ������ ��� ������ � ��������� �
			if ( !(masOut[masCount] = (char *)malloc(sizeof(char ) * (size + 1))) ) {
				return 0;
			}
			strncpy(masOut[masCount], str + i - size / 2, size);
			masOut[masCount][size] = '\0';
			++masCount;
		}
		//�������� �� �������� ���������
		size = checkEqualParts(str, i - 1, i + 1) + 1;
		if(size >= 7) {
			//���� ��������� ����������, ������� ������ ��� ������ � ��������� �
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

//������� ��� ������������

//����������� ������ ��� ���������� �������
void freeMas(char ** mas) {
	for (int i = 0; mas[i]; ++i) {
		free(mas[i]);
	}
	free(mas);
}

//������� ��������� ������ �� �����
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