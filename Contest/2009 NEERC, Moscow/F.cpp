#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("farm.in", "r", stdin);
	freopen("farm.out", "w", stdout);

	int n; scanf("%d", &n);

	int x = n / 4;
	long long ans;
	bool flag = 0;
	if(n % 4 == 0) {
		ans = 2LL * x * x;
		flag = 0;
	}
	else if(n % 4 == 1) {
		ans = 2LL * x * x + x - 1;
		flag = 1;
	}
	else if(n % 4 == 2) {
		ans = 2LL * x * x + 2 * x;
		flag = 0;
	}
	else if(n % 4 == 3) {
		ans = 2LL * x * x + 3 * x;
		flag = 1;
	}
	printf("%lld.%d\n", ans, flag ? 5 : 0);
	return 0;
} 
