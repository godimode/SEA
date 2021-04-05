#include<stdio.h>
#define MAX 200000
int n, k;
int drive[MAX], block[MAX];
void init() {
	for (int i = 0; i < n; i++)
		drive[i] = 0;
	for (int i = 0; i < k; i++)
		block[i] = 0;
}
int ckck(int mid) {
	int possible[MAX];

	int poss_length = 0, poss_cnt = 0;
	for (int i = 0; i < n; i++) {
		if (drive[i] <= mid) {
			poss_cnt++;
			if (i == n - 1) possible[poss_length] = poss_cnt;
		}
		else {
			possible[poss_length++] = poss_cnt;
			poss_cnt = 0;
		}
	}

	int poss_point = 0, block_point = 0;
	while (block_point < k && poss_point < poss_length+1) {
		if (possible[poss_point] > block[block_point]) {
			possible[poss_point] -= block[block_point++];
		}
		else if (possible[poss_point] == block[block_point]) {
			poss_point++;
			block_point++;
		}
		else {
			poss_point++;
		}
	}
	if (block_point == k) return 1;
	return 0;
}
int main() {
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		scanf("%d %d", &n, &k);
		init();
		for (int i = 0; i < n; i++)
			scanf("%d", &drive[i]);
		for (int i = 0; i < k; i++)
			scanf("%d", &block[i]);

		int first = 0, last = MAX;
		while (first <= last) {
			int mid = (first + last) / 2;
			if (ckck(mid)) {
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
		printf("#%d %d\n", t, first);
	}
}