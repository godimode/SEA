
// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
/*

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}
*/

/////////////////////////////////////////////////////////////
#define MAXN 301

char names[MAXN][11];
char tags[MAXN][11];
int n, m;
int H, W;
int isExist[MAXN * MAXN];
int S[MAXN][MAXN];
struct A {
	int name;
	int tag;
	int exist;
}a[MAXN][MAXN];

int mstrcmp(const char* a, const char* b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

void mstrcpy(char* dest, const char* src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void init(int R, int C) {
	n = m = 0;
	H = R, W = C;
	for (int i = 0; i < MAXN * MAXN; i++)
		isExist[i] = 0;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			a[i][j].exist = S[i][j] = 0;
}

int can_put(int r, int c, int h, int w) {
	if (r + h - 1 > H || c + w - 1 > W) return 0;
	if (S[r + h-1][c + w-1] - S[r + h-1][c-1] - S[r-1][c + w-1] + S[r - 1][c - 1] == 0) return 1;
	return 0;
}

int addItem(char name[], char tag[], int height, int width,
	int mode, int r, int c) {
	if (mode == 1) { // 자동배치
		int flag = 0;
		for (int i = 1; i <= W; i++) {
			for (int j = 1; j <= H; j++) {
				if (can_put(j, i, height, width)) {
					flag = 1;

					mstrcpy(names[n++], name);

					int temp = -1;
					for (int k = 0; k < m; k++) {
						if (!mstrcmp(tags[k], tag)) {
							temp = k;
							break;
						}
					}
					if (temp == -1) mstrcpy(tags[m++], tag);

					for (int k = j; k < j + height; k++) {
						for (int l = i; l < i + width; l++) {
							a[k][l].exist = 1;
							a[k][l].name = n - 1;
							if (temp == -1) a[k][l].tag = m - 1;
							else a[k][l].tag = temp;
						}
					}
					for (int k = j; k <= H; k++) {
						for (int l = i; l <= W; l++) {
							S[k][l] = S[k - 1][l] + S[k][l - 1] - S[k - 1][l - 1] + a[k][l].exist;
						}
					}
					isExist[H * (j - 1) + i] = 1;
					return 1;
				}
			}
		}
		return 0;
	}
	else {
		if (can_put(r, c, height, width)) {
			mstrcpy(names[n++], name);
			int temp = -1;
			for (int i = 0; i < m; i++) {
				if (!mstrcmp(tags[i], tag)) {
					temp = i;
					break;
				}
			}
			if (temp == -1) mstrcpy(tags[m++], tag);
			for (int k = r; k < r + height; k++) {
				for (int l = c; l < c + width; l++) {
					a[k][l].exist = 1;
					a[k][l].name = n - 1;
					if (temp == -1) a[k][l].tag = m - 1;
					else a[k][l].tag = temp;
				}
			}
			for (int k = r; k <= H; k++) {
				for (int l = c; l <= W; l++) {
					S[k][l] = S[k - 1][l] + S[k][l - 1] - S[k - 1][l - 1] + a[k][l].exist;
				}
			}
			isExist[H * (r - 1) + c] = 1;
			return 1;
		}
		return 0;
	}
}

int removeItemByName(char name[]) {

	int idx = -1;
	for (int i = 0; i < n; i++) {
		if (!mstrcmp(names[i], name)) idx = i;
	}
	if (idx == -1) return 0;
	int flag = 0;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			if (a[i][j].name == idx && a[i][j].exist==1) {
				a[i][j].exist = 0;
				isExist[H * (i - 1) + j] = 0;
				flag = 1;
			}
		}
	}
	if (flag == 0) return 0;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + a[i][j].exist;
		}
	}
	if (flag) return 1;
	return 0;
}

int removeItemByTag(char tag[]) {
	
	int idx = -1;
	for (int i = 0; i < m; i++) {
		if (!mstrcmp(tags[i], tag)) idx = i;
	}
	if (idx == -1) return 0;

	int ans = 0;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			if (a[i][j].tag == idx) {
				a[i][j].exist = 0;

				if (isExist[H * (i - 1) + j]) {
					isExist[H * (i - 1) + j] = 0;
					ans++;
				}
			}
		}
	}
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + a[i][j].exist;
		}
	}
	return ans;
}

int getItem(int r, int c, char name[], char tag[]) {
	if (a[r][c].exist) {

		mstrcpy(name, names[a[r][c].name]);
		mstrcpy(tag, tags[a[r][c].tag]);
		return 1;
	}
	return 0;
}

int getArea(char tag[]) {
	int ans = 0;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			if (a[i][j].exist && !mstrcmp(tags[a[i][j].tag], tag)) ans++;
		}
	}
	return ans;
}