#include <stdio.h>
#define ARR_MAX 200001
int ar[ARR_MAX], ck[ARR_MAX];
int n;
void init() {
	for (int i = 0; i < n; i++)
		ar[i] = ck[i] = 0;
}
int main() {
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		scanf("%d", &n);
		init();
		for (int i = 0; i < n; i++)
			scanf("%d", &ar[i]);

		ck[0] = ar[0];
		int ans = ck[0];
		for (int i = 1; i < n; i++) {
			ck[i] = ck[i - 1] + ar[i] > ar[i] ? ck[i - 1] + ar[i] : ar[i];
			if (ans < ck[i]) ans = ck[i];
		}
		printf("#%d %d\n", t, ans);
	}
}