#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(1E3 + 10);

int a[kN][kN];
int main() {
	int n, ans = 0, k;
	while (scanf("%d", &n) != EOF) {
		ans = 0;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
		if (n == 1) {
			printf("0\n");
			continue;
		}
		k = a[1][2];
		for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) k = min(k, a[i][j]);
		for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (a[i][j] == k) ans++;
		printf("%d\n", ans);
	}
} 
