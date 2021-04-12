#include <stdio.h>
#define MAXAR 200001
struct A {
	int s, e, c;
}node[MAXAR], temp[MAXAR],tempp;
int prt[5001];
void merge(int first, int mid, int last) {
	int i, j, k;
	i = first, j = mid + 1, k = first;
	while (i <= mid && j <= last) {
		if (node[i].c < node[j].c) {
			temp[k++] = node[i++];
		}
		else {
			temp[k++] = node[j++];
		}
	}
	if (i > mid) {
		for (int l = j; l <= last; l++) {
			temp[k++] = node[l];
		}
	}
	else {
		for (int l = i; l <= mid; l++) {
			temp[k++] = node[l];
		}
	}
	for (int l = first; l <= last; l++) {
		node[l] = temp[l];
	}
}
void mergeSort(int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(first, mid);
		mergeSort(mid + 1, last);
		merge(first, mid, last);
	}
}
void init() {
	for (int i = 0; i < MAXAR; i++)
		node[i] = tempp;
}
int getParent(int a) {
	if (prt[a] == a) return a;
	return prt[a] = getParent(prt[a]);
}
void unionParent(int a, int b) {
	a = getParent(a);
	b = getParent(b);

	if (a < b) prt[b] = a;
	else prt[a] = b;
}
int find(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a == b) return 1;
	return 0;
}
int main() {
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		init();
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			prt[i] = i;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &node[i].s, &node[i].e, &node[i].c);
		}
		mergeSort(0, n - 1);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			int a = node[i].s;
			int b = node[i].e;
			int c = node[i].c;

			if (find(a, b)) continue;
			ans += c;
			unionParent(a, b);
		}
		printf("#%d %d\n", t, ans);
	}
}