#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

#define MAX_BOOK 50011
#define MAX_TABLE 50001
typedef unsigned long long ull;

struct Books {
	Books* next;
	ull key;
	int section;
	int isDel;
	int counted;
}books[MAX_BOOK], initBook;
int book_cnt;
Books* book_tb[MAX_TABLE];

struct Types {
	ull key;
	Types* next;
	Books* book;
}types[MAX_BOOK * 5], initType;
int type_cnt;
int count_Idx;
Types* type_tb[MAX_TABLE];

ull getHash(char key[]) {
	ull h = 0;
	for (int i = 0; key[i]; i++) {
		h = (h << 6) + key[i] - 'A' + 1;
	}
	return h;
}

void init(int M)
{
	book_cnt = type_cnt = count_Idx = 0;
	register int i;
	for (i = 0; i < MAX_TABLE; i++) {
		book_tb[i] = 0;
		type_tb[i] = 0;
	}
		
	for (i = 0; i < MAX_BOOK; i++)
		books[i] = initBook;
	for (i = 0; i < MAX_BOOK * 5; i++)
		types[i] = initType;
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	ull nameHash = getHash(mName);

	Books* newBook = &books[++book_cnt];
	newBook->key = nameHash;
	newBook->section = mSection;
	newBook->isDel = 0;
	newBook->next = book_tb[nameHash%MAX_TABLE];
	book_tb[nameHash%MAX_TABLE] = newBook;

	register int i;
	Types* newType;
	for (i = 0; i < mTypeNum; i++) {
		ull typeKey = getHash(mTypes[i]);
		newType = &types[++type_cnt];
		newType->book = newBook;
		newType->next = type_tb[typeKey%MAX_TABLE];
		newType->key = typeKey;
		type_tb[typeKey%MAX_TABLE] = newType;
	}
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	int ans = 0;
	ull typeKey = getHash(mType);
	Types* address = type_tb[typeKey%MAX_TABLE];

	while (address) {
		if (address->book->section == mFrom && address->book->isDel == 0 && address->key == typeKey) {
			address->book->section = mTo;
			ans++;
		}
		address = address->next;
	}
	return ans;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	ull bookKey = getHash(mName);
	Books* address = book_tb[bookKey%MAX_TABLE];
	while (address) {
		if (address->key == bookKey && address->isDel == 0) {
			address->section = mSection;
			break;
		}
		address = address->next;
	}

}

void deleteName(char mName[MAX_NAME_LEN])
{
	ull bookKey = getHash(mName);
	Books* address = book_tb[bookKey%MAX_TABLE];
	while (address) {
		if (address->key == bookKey) {
			address->isDel = 1;
			break;
		}
		address = address->next;
	}
	
}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	++count_Idx;
	int ans = 0;
	register int i;
	for (i = 0; i < mTypeNum; i++) {
		ull typeKey = getHash(mTypes[i]);
		Types* address = type_tb[typeKey%MAX_TABLE];
		while (address) {
			if (address->key == typeKey && address->book->isDel == 0 && address->book->section == mSection && address->book->counted != count_Idx) {
				address->book->counted = count_Idx;
				ans++;
			}
			address = address->next;
		}
	}
	return ans;
}