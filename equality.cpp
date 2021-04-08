#include<stdio.h>
#define MAX 1000000000
#define ARRAY_MAX 100000
int n;
int arr[ARRAY_MAX];

int ckck(int mid, int k) {

	int copy[ARRAY_MAX];
	for (int i = 0; i < n; i++)
		copy[i] = arr[i];

	for (int i = 0; i < n - 1; i++) {
		int temp = copy[i + 1] - copy[i];
		if (temp > mid) {
			copy[i + 1] -= temp - mid;
			k -= temp - mid;
		}
	}
	for (int i = n - 1; i > 0; i--) {
		int temp = copy[i - 1] - copy[i];
		if (temp > mid) {
			copy[i - 1] -= temp - mid;
			k -= temp - mid;
		}
	}
	if (k >= 0) return 1;
	return 0;
}
int main() {
	int TC, k;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		int first = 0, last = MAX;
		while (first <= last) {
			int mid = (first + last) / 2;

			if (ckck(mid, k)) last = mid - 1;
			else first = mid + 1;
		}
		printf("#%d %d\n", t, first);
	}
}