#define NAME_MAXLEN 10
#define PATH_MAXLEN 2005

#define MAX_DIR 50005

typedef unsigned long long ull;

struct Folder {
	ull key; // name
	Folder* parent;
	Folder* childs[30];
	int dirN;
}folder[MAX_DIR], tempF;
int dir_cnt;

ull getHash(char name[]) {
	ull h = 0;
	register int i;
	for (i = 0; name[i]; i++) {
		h = (h << 5) + name[i] - 'a' + 1;
	}
	return h;
}


void init(int n) {
	dir_cnt = 0;
	register int i;
	for (i = 0; i < MAX_DIR; i++)
		folder[i] = tempF;
	Folder* newFolder = &folder[0];
	newFolder->dirN = 1;
	
}

Folder* cd(char path[]) {

	char temp[NAME_MAXLEN];
	int path_len = 0;
	int temp_len = 0;
	Folder* cur;
	while (path[path_len] != '\0') {

		temp_len = 0;
		while (path[path_len] != '/') {
			temp[temp_len++] = path[path_len++];
		}
		if (path_len == 0) {
			cur = &folder[0];
		}
		else {
			temp[temp_len] = '\0';
			ull h = getHash(temp);
			for (int i = 0; i < 30; i++) {
				if (cur->childs[i] && cur->childs[i]->key == h) {
					cur = cur->childs[i];
					break;
				}
			}
		}
		path_len++;
	}
	return cur;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {

	// path를 /로 분리해서 제일 마지막으로 이동
	Folder* cur = cd(path);
	
	// name을 path의 마지막부분에 연결
	Folder* newFolder = &folder[++dir_cnt];
	ull h = getHash(name);
	newFolder->key = h;
	newFolder->parent = cur;
	for (int i = 0; i < 30; i++) {
		if (cur->childs[i] == 0) {
			cur->childs[i] = newFolder;
			break;
		}
	}
	
	while (newFolder) {
		newFolder->dirN++;
		newFolder = newFolder->parent;
	}
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {

	Folder* cur = cd(path);
	for (int i = 0; i < 30; i++) {
		if (cur->parent->childs[i] == cur) {
			cur->parent->childs[i] = 0;
			//cur->parent->dirN -= cur->dirN;

			int n = cur->dirN;
			Folder* address = cur->parent;
			// parent 위로 쭉 다 빼줘야함
			while (address) {
				address->dirN -= n;
				address = address->parent;
			}
			break;
		}
	}
}
void dfs(Folder* p, Folder* q) {

	for (int i = 0; i < 30; i++) {
		if (p->childs[i] != 0) {
			Folder* newF = &folder[++dir_cnt];
			newF->key = p->childs[i]->key;
			newF->dirN = p->childs[i]->dirN;
			newF->parent = q;
			q->childs[i] = newF;
			dfs(p->childs[i], q->childs[i]);
		}
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	
	Folder* ctrlC = cd(srcPath);
	Folder* ctrlV = cd(dstPath);

	Folder* newFolder = &folder[++dir_cnt];
	newFolder->key = ctrlC->key;
	newFolder->dirN = ctrlC->dirN;
	newFolder->parent = ctrlV;
	dfs(ctrlC, newFolder);

	for (int i = 0; i < 30; i++) {
		if (ctrlV->childs[i] == 0) {
			ctrlV->childs[i] = newFolder;
			Folder* address = ctrlV;
			while (address) {
				address->dirN += newFolder->dirN;
				address = address->parent;
			}
			break;
		}
	}
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	
	Folder* ctrlZ = cd(srcPath);
	Folder* ctrlV = cd(dstPath);

	for (int i = 0; i < 30; i++) {
		if (ctrlZ->parent->childs[i] == ctrlZ) {
			ctrlZ->parent->childs[i] = 0;
			
			Folder* address = ctrlZ->parent;
 			while (address) {
				address->dirN -= ctrlZ->dirN;
				address = address->parent;
			}
			break;
		}
	}
	for (int i = 0; i < 30; i++) {
		if (ctrlV->childs[i] == 0) {
			ctrlV->childs[i] = ctrlZ;
			//ctrlV->dirN += ctrlZ->dirN;
			ctrlZ->parent = ctrlV;
			
			Folder* address = ctrlV;
			while (address) {
				address->dirN += ctrlZ->dirN;
				address = address->parent;
			}
			break;
		}
	}
}

int cmd_find(char path[PATH_MAXLEN + 1]) {

	Folder* cur = cd(path);
	return cur->dirN-1;
}