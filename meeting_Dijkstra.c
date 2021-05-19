#include <stdio.h>

#define MAX_NODE 1000001
#define MAX_EDGE 2000001
#define INF 2100000000
typedef struct {
    int node;
    int cnt;
}Heap;

typedef struct {
    int start, end, cnt, prev;
}Edge;

Heap heap[3 * MAX_EDGE];
int heap_len = 0;
int dist[MAX_NODE + 1], dist2[MAX_NODE + 1];
int last_edge[MAX_NODE + 1], last_edge2[MAX_NODE + 1];
Edge edge[MAX_EDGE + 1], edge2[MAX_EDGE + 1];
int n, m, start;

void init() {
    for (int i = 0; i <= n; i++)
        dist[i] = INF, dist2[i] = INF;
    heap_len = 0;
    for (int i = 0; i <= m; i++)
        last_edge[i] = last_edge2[i] = 0;
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
   // freopen("eval_input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int TC;
    scanf("%d", &TC);
    for (int t = 1; t <= TC; t++) {

        scanf("%d %d %d", &n, &m, &start);
        init();
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %d", &edge[i].start, &edge[i].end, &edge[i].cnt);
            edge[i].prev = last_edge[edge[i].start];
            last_edge[edge[i].start] = i;

            edge2[i].start = edge[i].end;
            edge2[i].end = edge[i].start;
            edge2[i].cnt = edge[i].cnt;
            edge2[i].prev = last_edge2[edge2[i].start];
            last_edge2[edge2[i].start] = i;
        }
        for (int i = 0; i <= n; i++)
            dist[i] = dist2[i] = INF;
        Heap newHeap;
        newHeap.node = start, newHeap.cnt = 0;
        heap_push(newHeap);
        dist[start] = 0;
        while (heap_len > 0) {
            Heap next = heap_pop();
            if (next.cnt > dist[next.node]) continue;
            for (int i = last_edge[next.node]; i; i = edge[i].prev) {
                Edge e = edge[i];
                if (dist[e.end] > dist[next.node] + e.cnt) {
                    dist[e.end] = dist[next.node] + e.cnt;
                    newHeap.node = e.end, newHeap.cnt = dist[e.end];
                    heap_push(newHeap);
                }
            }
        }
        heap_len = 0;
        newHeap.node = start, newHeap.cnt = 0;
        heap_push(newHeap);
        dist2[start] = 0;
        while (heap_len > 0) {
            Heap next = heap_pop();
            if (next.cnt > dist2[next.node]) continue;
            for (int i = last_edge2[next.node]; i; i = edge2[i].prev) {
                Edge e = edge2[i];
                if (dist2[e.end] > dist2[next.node] + e.cnt) {
                    dist2[e.end] = dist2[next.node] + e.cnt;
                    newHeap.node = e.end, newHeap.cnt = dist2[e.end];
                    heap_push(newHeap);
                }
            }
        }
        int max = -1;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INF || dist2[i] == INF) {
                dist[i] = INF;
                continue;
            }
            else {
                dist[i] += dist2[i];
                if (max < dist[i]) max = dist[i];
            }
        }
        printf("#%d %d\n", t, max);
    }
}