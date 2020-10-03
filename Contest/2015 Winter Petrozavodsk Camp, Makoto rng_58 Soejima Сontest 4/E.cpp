#include <stdio.h>
#include <algorithm>
using namespace std;

constexpr int kN = int(1E3 + 10);

int a[kN];

int main() {
	int n, cnt = 0, now = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) if (now < a[i]) {
		cnt++;
		now += a[i];
	}
	printf("%d\n", cnt);
} 
