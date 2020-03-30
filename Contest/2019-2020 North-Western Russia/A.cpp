#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b, n;
	scanf("%d%d%d", &a, &b, &n);
	int ans = 1 + 2 * ((n - b + b - a - 1) / (b - a));
	printf("%d\n", ans);
	return 0;
} 
