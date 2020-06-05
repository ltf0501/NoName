#include <stdio.h>
#include <algorithm>
using namespace std;

constexpr int kN = int(1E6 + 10);
int a[kN], b[kN];

int main() {
	int n, l = -1, r = -1, lpos, rpos;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) if (a[i] > a[i + 1]) b[i] = -1;
	else if (a[i] == a[i + 1]) b[i] = 0;
	else b[i] = 1;
	for (int i = 1; i < n; i++) if (b[i] == -1) {
		l = i;
		while (l > 1 && b[l - 1] == 0) l--;
		break;
	}


	for (int i = 1; i < n; i++) if (b[i] == -1) r = i;
	r++;
	while (r < n && b[r] == 0) r++;
	if (l == -1) {
		printf("1 1\n");
		return 0;
	}
	
	lpos = l, rpos = r;
	while (lpos < rpos) {
		swap(a[lpos], a[rpos]);
		lpos++;
		rpos--;
	}


	for (int i = 1; i < n; i++) if (a[i] > a[i + 1]) {
		printf("impossible\n");
		return 0;
	}

	printf("%d %d\n", l, r);
}

