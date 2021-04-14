#include <stdio.h>
#define MAXN 60001
#define MAXE 160001

typedef struct node {
	int n;
	struct node* next;
}Node;

Node list[MAXN], mem[MAXE];
int memIdx;
int inDegree[MAXN];
int n, m;
int q[MAXE], st, ed;

void init() {
	for (int i = 0; i <= n; i++)
		inDegree[i] = 0, list[i].next = 0;
	memIdx = st = ed = 0;

}
void tplSort() {
	for (int i = 1; i <= n; i++)
		if (inDegree[i] == 0) q[++st] = i;

	while (st != ed) {
		int cur = q[++ed];
		Node* add = list[cur].next;
		while (add) {
			int next = add->n;
			Node* nextAdd = add->next;
			inDegree[next]--;
			if (inDegree[next] == 0) {
				q[++st] = next;
			}
			add = nextAdd;
		}
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {
		scanf("%d %d", &n, &m);
		init();
		for (int i = 0; i < m; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			Node* newNode = &mem[++memIdx];
			newNode->n = y;
			newNode->next = list[x].next;
			list[x].next = newNode;

			inDegree[y]++;
		}
		tplSort();
		printf("#%d ", t);
		for (int i = 1; i <= ed; i++)
			printf("%d ", q[i]);
		printf("\n");
	}
}