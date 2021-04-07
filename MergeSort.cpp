#include <stdio.h>
#define MAX_SIZE 1000001

int temp[MAX_SIZE];

int N;
int ar[MAX_SIZE];
void merge(int list[], int left, int mid, int right) {  // 나눠진 두 배열이 합쳐지는 과정

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
	// 남은거 넣기
	if (i > mid) {
		for (int p = j; p <= right; p++)
			temp[tempCnt++] = list[p];
	}
	else {
		for (int p = i; p <= mid; p++)
			temp[tempCnt++] = list[p];
	}

	// 임시 배열에서 실제 배열로 옮기기
	for (int p = left; p <= right; p++)
		list[p] = temp[p];
}

void mergeSort(int a[], int left, int right) {

	if (left < right) {
		int mid = (left + right) / 2;

		mergeSort(a, left, mid); // 쪼개기
		mergeSort(a, mid + 1, right); // 쪼개기
		merge(a, left, mid, right); // 합치기

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