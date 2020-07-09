#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int kN = 4e3 + 10;
int a[kN];
int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ans = (a[1] - a[2] + kMod) % kMod;
	printf("%d\n", ans);
	return 0;
} 
