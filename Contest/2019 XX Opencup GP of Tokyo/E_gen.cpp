#include <bits/stdc++.h>
using namespace std;
int a[205];
int main() {
	srand(time(NULL));
	int T = 1;
	long long n = (1LL << 60) - 1, s = 1e18, k = 200;
	for(int i = 0; i < k; i++) a[i] = rand() % 100001;

	printf("%d\n", T);
	printf("%lld %lld %lld\n", n, s, k);
	sort(a, a + k);
	for(int i= 0; i < k; i++) printf("%d ", a[i]); puts("");
	return 0;
}
