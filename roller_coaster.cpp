#include <iostream>
#include <stdio.h>

using namespace std;


#define MAXN 2000001
#define mod 1000000007
int a[MAXN], b[MAXN];

struct Rail {
	long long a;
	long long b;
};
Rail rail[MAXN], temp[MAXN];


void merge(Rail ar[], int left, int mid, int right) {
	
	int i, j;
	i = left, j = mid + 1;
	int tempCnt = left;
	while (i <= mid && j <= right) {
		if (ar[j].a*ar[i].b + ar[j].b < ar[i].a*ar[j].b + ar[i].b) {
			temp[tempCnt++] = ar[i++];
		}
		else {
			temp[tempCnt++] = ar[j++];
		}
	}

	if (i > mid) {
		for (int k = j; k <= right; k++)
			temp[tempCnt++] = ar[k];
	}
	else {
		for (int k = i; k <= mid; k++)
			temp[tempCnt++] = ar[k];
	}

	for (int k = left; k <= right; k++)
		ar[k] = temp[k];


}

void mergeSort(Rail ar[], int left, int right) {

	if (left < right) {
		int mid = (left + right) / 2;

		mergeSort(ar, left, mid);
		mergeSort(ar, mid + 1, right);
		merge(ar, left, mid, right);
	}
}


int MinRailSpeed(int N, int *a, int *b) {

	for (int i = 0; i < N; i++)
	{
		rail[i].a = a[i];
		rail[i].b = b[i];
	}

	mergeSort(rail, 0, N-1);

	int v = 1;

	for (int i = 0; i < N; i++) 
		v = (int)(((long long)(rail[i].a)*v + rail[i].b) % mod);

	return v;
}

int main(void) {
	setbuf(stdout, NULL);

	int TestCase; for (scanf("%d", &TestCase); TestCase--;) {

		int N; scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			scanf("%d%d", &a[i], &b[i]);
		}

		int answer = MinRailSpeed(N, a, b);

		static int tc = 0;
		printf("#%d %d\n", ++tc, answer);
	}
	return 0;
}