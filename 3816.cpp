#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 100000;

int FindAnagram(int Len1, char *S1, int Len2, char *S2);

char S1[MAXN + 5];
char S2[MAXN + 5];

int main(void) {
	setbuf(stdout, NULL);

	int TestCase; for (scanf("%d", &TestCase); TestCase--;) {

		scanf("%s", S1);
		scanf("%s", S2);

		//L1 = Length of S1, L2 = Length of S2
		int L1 = 0, L2 = 0;
		for (; S1[L1]; L1++);
		for (; S2[L2]; L2++);

		int answer = FindAnagram(L1, S1, L2, S2);

		static int tc = 0;
		printf("#%d %d\n", ++tc, answer);
	}
	return 0;
}
int ck_S1[30];
int ck_S2[30];

int same_array() {
	for (int i = 0; i < 30; i++) {
		if (ck_S1[i] != ck_S2[i]) return 0;
	}
	return 1;
}

void init() {
	for (int i = 0; i < 30; i++)
		ck_S1[i] = ck_S2[i] = 0;
}
int FindAnagram(int Len1, char *S1, int Len2, char *S2) {
	int answer = 0;
	init();

	for (int i = 0; i < Len1; i++)
		ck_S1[S1[i] - 'a']++;

	for (int i = 0; i < Len1; i++)
		ck_S2[S2[i] - 'a']++;

	for (int i = Len1; i <= Len2; i++) {
		if (same_array())
			answer++;

		if (i == Len2) break;
		ck_S2[S2[i - Len1]-'a']--;
		ck_S2[S2[i]-'a']++;
	}
	return answer;
}