#include <bits/stdc++.h>
using namespace std;
mt19937 rng;
int main() {
	srand(clock() + time(0));
	int n = 8, q = 20;
	printf("%d %d\n", n, q);
	for(int i = 1; i <= q; i++) {
		int u = rand() % n + 1;
		int v;
		do {
			v = rand() % n + 1;
		} while(u == v);

		int a = rand() & 31;
		int w = rand() % 50;
		printf("%d %d %d %d\n", u, v, a, w);
	}
	return 0;
}
