#define MAX_TABLE 1000001
typedef unsigned long long ull;

struct Node {
	ull key;
	int data;
	Node* next;
};

Node node[MAX_TABLE];
Node* Hash[MAX_TABLE];
int nodeCnt;

void init() {
	nodeCnt = 0;
}

int find(char key[]) {
	ull hash = 0;
	int i = 0;
	while (key[i]) {
		hash = (hash << 5) + key[i++] - 'a' + 1;
	}
	int hash_key = hash % MAX_TABLE;

	Node* p = Hash[hash_key];
	while (1) {
		if (p->key != hash) p = p->next;
		else return p->data;
	}
}

void add(char key[], int data) {
	ull hash = 0;
	int i = 0;
	while (key[i]) {
		hash = (hash << 5) + key[i++] - 'a' + 1;
	}
	int hash_key = hash % MAX_TABLE;
	node[nodeCnt].data = data;
	node[nodeCnt].key = hash;

	if (Hash[hash_key]) {
		node[nodeCnt].next = Hash[hash_key];
	}	
	Hash[hash_key] = &node[nodeCnt++];
	
}

int remove(char key[]) {
	return find(key);
}