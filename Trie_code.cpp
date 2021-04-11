
#define MAXSTR 100
#define MAX 5001

struct	Node {
	int prev, end;
	int next[26];
}node[MAX*MAXSTR], temp;
int idx;


void init_trie() {
	for (int i = 0; i <= idx; i++)
		node[i] = temp;
	idx = 0;
}

void Tries_insert(char key[MAXSTR + 1]) {
	int cur = 0;
	for (int i = 0; key[i]; i++) {
		int next = key[i] - 'a';
		if (node[cur].next[next] == 0) node[cur].next[next] = ++idx;
		cur = node[cur].next[next];
		node[cur].prev++;
	}
	node[cur].end++;
}

bool Tries_search(char key[MAXSTR + 1]) {
	int cur = 0;
	for (int i = 0; key[i]; i++) {
		int next = key[i] - 'a';
		if (node[cur].next[next] == 0) return false;
		cur = node[cur].next[next];
	}
	if (node[cur].end) return true;
	return false;
}

int Tries_CountofkeysWithPrefix(char key[MAXSTR + 1]) {
	int cur = 0;
	for (int i = 0; key[i]; i++) {
		int next = key[i] - 'a';
		if (node[cur].next[next] == 0) return 0;
		cur = node[cur].next[next];
	}
	return node[cur].prev;
}

void Tries_deleteKey(char key[MAXSTR + 1]) {
	if (Tries_search(key)) {
		int cur = 0;
		for (int i = 0; key[i]; i++) {
			int next = key[i] - 'a';
			cur = node[cur].next[next];
			node[cur].prev--;
		}
		node[cur].end--;
	}
}
