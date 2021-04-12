#include <stdio.h>
int map[11][11];
int ck[11];
int M;
void dfs(int p, int n, int q) {
	for (int i = 1; i <= n; i++) {
		if (map[p][i] && !ck[i]) {
			ck[i] = 1;
			dfs(i, n, q + 1);
			ck[i] = 0;
		}
	}
	if (q > M) M = q;
}
void init() {
	for (int i = 0; i < 11; i++) {
		ck[i] = 0;
		for (int j = 0; j < 11; j++)
			map[i][j] = 0;
	}
}
int main() {
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		init();
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			int k;
			scanf("%d", &k);
			int ar[11];
			for (int j = 0; j < k; j++) {
				scanf("%d", &ar[j]);
				if (j) {
					map[ar[j - 1]][ar[j]] = 1;
				}
			}
		}
		printf("#%d ", t);
		int max = -1;
		for (int i = 1; i <= n; i++) {
			int ans = 0;
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (map[i][j]) ans++;
			}
			printf("%d ", ans);
			ck[i] = 1;
			M = 0;
			dfs(i, n,1);
			ck[i] = 0;
			if (M > max) max = M;
		}
		printf("%d", max);

	}
}
