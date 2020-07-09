#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(2E2 + 10);
int a[kN];
int main() {
	int n, ans = 0;
	bool turn = true;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		if (a[i] & 1) {
			ans += (a[i] >> 1) + turn;
			turn = !turn;
		}
		else ans += a[i] >> 1;
	}

	printf("%d\n", ans);
} 
