#include <stdio.h>

constexpr int kN = int(2E3 + 10);
int p[kN], l[kN], r[kN], s[kN];

int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}
int dis(int x1, int y1, int x2, int y2) {
	int x = x2 - x1, y = y2 - y1;
	return x * x + y * y;
}

void Merge(int l, int r) {
	l = Find(l), r = Find(r);
	p[r] = l;
	return ;
}

int main() {
	int n, m, k, L, R;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) scanf("%d%d%d", &l[i], &r[i], &s[i]);
	L = k + 1, R = k + 2;
	for (int i = 1; i <= k; i++) p[i] = i;
	p[k + 1] = k + 1, p[k + 2] = p[k + 2];
	for (int i = 1; i <= k; i++) {
		if (l[i] <= s[i] || (m - r[i]) <= s[i]) Merge(L, i);
		if (r[i] <= s[i] || (n - l[i]) <= s[i]) Merge(R, i);
		for (int j = i + 1; j <= k; j++) if (dis(l[i], r[i], l[j], r[j]) <= (s[i] + s[j]) * (s[i] + s[j])) Merge(i, j);
		
	}
	if (Find(L) == Find(R)) printf("N\n");
	else printf("S\n");
} 
