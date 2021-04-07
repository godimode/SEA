#include <stdio.h>
#define MAX_SIZE 1000001

int temp[MAX_SIZE];

int N;
int ar[MAX_SIZE];
void merge(int list[], int left, int mid, int right) {  // ������ �� �迭�� �������� ����

	int i, j, k, tempCnt;
	tempCnt = left;
	i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (list[i] < list[j]) {
			temp[tempCnt++] = list[i++];
		}
		else {
			temp[tempCnt++] = list[j++];
		}
	}
	// ������ �ֱ�
	if (i > mid) {
		for (int p = j; p <= right; p++)
			temp[tempCnt++] = list[p];
	}
	else {
		for (int p = i; p <= mid; p++)
			temp[tempCnt++] = list[p];
	}

	// �ӽ� �迭���� ���� �迭�� �ű��
	for (int p = left; p <= right; p++)
		list[p] = temp[p];
}

void mergeSort(int a[], int left, int right) {

	if (left < right) {
		int mid = (left + right) / 2;

		mergeSort(a, left, mid); // �ɰ���
		mergeSort(a, mid + 1, right); // �ɰ���
		merge(a, left, mid, right); // ��ġ��

	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &ar[i]);
	mergeSort(ar, 0, N - 1);
	for (int i = 0; i < N; i++)
		printf("%d\n", ar[i]);
}