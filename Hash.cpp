#define MAX_TABLE 60001

struct Hash {
	unsigned long long key;
	int data;
};
Hash db[MAX_TABLE];

unsigned long long getHash(char key[]) {
	unsigned long long h = 0;
	int i = 0;
	while (key[i]) {
		h = (h << 5) + key[i++] - 'a' + 1;
	}
	return h;
}

void init() {
	register int i;
	for (i = 0; i < MAX_TABLE; i++) {
		db[i].key = 0;
	}
}

int findHash(char key[]) {
	unsigned long long h = getHash(key);
	int hidx = h % MAX_TABLE;
	while (db[hidx].key != h) {
		hidx = (hidx + 1) % MAX_TABLE;
	}
	return hidx;
}

int find(char key[]) {
	int hidx = findHash(key);
	return db[hidx].data;
}

void add(char key[], int data) {
	unsigned long long h = getHash(key);
	int hidx = h % MAX_TABLE;
	while (db[hidx].key != 0) {
		if (db[hidx].key == h) {
			break;
		}
		hidx = (hidx + 1) % MAX_TABLE;
	}
	db[hidx].key = h;
	db[hidx].data = data;
}

int remove(char key[]) {
	int hidx = findHash(key);
	db[hidx].key = 0;
	return db[hidx].data;
}