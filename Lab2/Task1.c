#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//���������� ������ �� ������� ����� ��������� ����������
int checkAscendingPart(int *const masIn, int size, int index) {
	for (int last = masIn[index]; ++index < size && last < masIn[index]; last = masIn[index]);
	return index;
}

int ** getAscendingParts(int *const masIn, int size) {
	int ** masOut;
	int masCount = 0;
	int descentingCount = 0;

	//�������� ������ ��� ���������
	if ( !(masOut = (int **)malloc(sizeof(int *) * (size / 2 + 1))) ) {
		return 0;
	}
	memset(masOut, 0, sizeof(int *) * (size / 2 + 1));

	//�������� ������ ��� ������ �������������� ������
	if ( !(masOut[0] = (int *)malloc(sizeof(int ) * (size + 1))) ) {
		return 0;
	}
	masOut[0][0] = 0;
	
	for (int i = 0; i < size; ) {
		int nextPart;
		int partSize;

		//������� ��� ������������� ������������ ����� � �������� � ������
		nextPart = checkAscendingPart(masIn, size, i);
		partSize = nextPart - i;
		if ( partSize != 1) {
			//���� ���� ������������ �����
			++masCount;
			if ( !(masOut[masCount] = (int *)malloc(sizeof(int ) * (partSize + 1))) ) {
				return 0;
			}
			masOut[masCount][0] = partSize;
			memcpy(masOut[masCount] + 1, masIn + i, sizeof(int) * (partSize));
		}
		else {
			//���� ���� ��������� �����
			++(masOut[0][0]);
			masOut[0][masOut[0][0]] = masIn[i];
		}
		i = nextPart;
	}
	return masOut;
}

//������� ��� ������������

//����������� ������ ��� ���������� �������
void freeMas(int ** mas) {
	for (int i = 0; mas[i]; ++i) {
		free(mas[i]);
	}
	free(mas);
}

//������� ��������� ������ �� �����
void printMas(int ** mas) {
	for (int i = 0; mas[i]; ++i) {
		printf("Row %d: ", i);
		for (int j = 1; j <= mas[i][0]; ++j) {
			printf("%d, ", mas[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int mas[] = { 1, 2, 3, 2, 1, 2, 3 };
	int ** result = getAscendingParts(mas, sizeof(mas) / sizeof(int));

	printMas(result);

	freeMas(result);
	getchar();
	return 0;
}