#include <stdio.h>
#include <algorithm>
using namespace std;
constexpr int kN = int(1E6 + 10);

int a[kN];

int main() {
	int n, k, ans = 1;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; i++) if (a[i] + a[i - 1] <= k) ans = i;
	printf("%d\n", ans);
} 
