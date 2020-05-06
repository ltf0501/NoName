#include <bits/stdc++.h>
using namespace std;
const int kN = 1e6 + 10;

bool pos[kN];
int main() {
	int n, k; scanf("%d%d", &n, &k);
	int ans = 0;
	for(int i = 0; i < k; i++) {
		int x; scanf("%d", &x);
		for(int j = x; j <= n; j += x) pos[j] ^= 1; 	
		int tmp = 0;
		for(int j = 1; j <= n; j++) tmp += pos[j];
		ans = max(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
} 
