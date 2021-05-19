#include <stdio.h>

#define MAX_NODE 1000001
#define MAX_EDGE 2000001
#define INF 1e18
typedef long long ll;
typedef struct {
	ll node;
	ll cnt;
}Heap;

typedef struct {
	ll start, end, cnt, prev;
}Edge;

Heap heap[3 * MAX_EDGE];
ll heap_len = 0;
ll dist[MAX_NODE + 1];
ll last_edge[MAX_NODE + 1];
Edge edge[MAX_EDGE + 1];
ll prev[MAX_EDGE + 1];
ll n, m;

void init() {
	for (int i = 0; i <= MAX_NODE; i++)
		dist[i] = INF;
	heap_len = 0;
	for (int i = 0; i <= MAX_EDGE; i++)
		last_edge[i] = prev[i] = 0;
}

void heap_push(Heap item) {

	heap[++heap_len] = item;
	if (heap_len == 1) return;

	int cur = heap_len;
	while (cur > 1) {
		if (heap[cur].cnt < heap[cur / 2].cnt) {
			Heap h = heap[cur]; heap[cur] = heap[cur / 2]; heap[cur / 2] = h;
			cur /= 2;
		}
		else break;
	}
}
int small_idx(int i1, int i2) {
	return heap[i1].cnt < heap[i2].cnt ? i1 : i2;
}

Heap heap_pop() {
	Heap rHeap = heap[1];
	heap[1] = heap[heap_len--];

	int cur = 1;
	while (2 * cur <= heap_len) {
		if (2 * cur + 1 > heap_len) {
			if (heap[cur].cnt > heap[2 * cur].cnt) {
				Heap h = heap[cur]; heap[cur] = heap[2 * cur]; heap[2 * cur] = h;
			}
			break;
		}
		else {
			int idx = small_idx(2 * cur, 2 * cur + 1);
			if (heap[cur].cnt > heap[idx].cnt) {
				Heap h = heap[cur]; heap[cur] = heap[idx]; heap[idx] = h;
				cur = idx;
			}
			else break;
		}
	}
	return rHeap;
}
int main()
{
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int TC;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++) {

		scanf("%lld %lld", &n, &m);
		init();
		for (int i = 1; i <= 2* m; i+=2) {
			ll a, b, c;
			scanf("%lld %lld %lld", &a, &b, &c);
			edge[i].start = a, edge[i].end = b, edge[i].cnt = c;
			edge[i].prev = last_edge[edge[i].start];
			last_edge[edge[i].start] = i;

			edge[i + 1].start = b, edge[i + 1].end = a, edge[i + 1].cnt = c;
			edge[i+1].prev = last_edge[edge[i+1].start];
			last_edge[edge[i + 1].start] = i + 1;
		}
		for (int i = 0; i <= n; i++)
			dist[i] = INF;
		Heap newHeap;
		newHeap.node = 1, newHeap.cnt = 0;
		heap_push(newHeap);
		dist[1] = 0;
		while (heap_len > 0) {
			Heap next = heap_pop();
			ll cur = next.node;
			ll distance = next.cnt;
			if (distance > dist[cur]) continue;

			for (ll i = last_edge[next.node]; i; i = edge[i].prev) {
				Edge e = edge[i];
				ll nextPoint = edge[i].end;
				ll nextDistance = edge[i].cnt + distance;
				if (dist[nextPoint] > nextDistance) {
					dist[nextPoint] = nextDistance;
					prev[nextPoint] = edge[i].cnt;
					newHeap.node = nextPoint, newHeap.cnt = dist[nextPoint];
					heap_push(newHeap);
				}
				else if (dist[nextPoint] == nextDistance) {
					if (prev[nextPoint] > edge[i].cnt)
						prev[nextPoint] = edge[i].cnt;
				}
			}
		}
		ll ans = 0;
		for (int i = 2; i <= n; i++)
			ans += prev[i];
		printf("#%d %lld\n", t, ans);
	}
}