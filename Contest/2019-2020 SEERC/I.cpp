#include <stdio.h>
#include <algorithm>
using namespace std;
constexpr int kN = int(1E3 + 10);
int ABS(int n) {return n >= 0 ? n : -n;}
int a[kN], b[kN];
int main() {
	int n, ans = 0, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		tmp = ABS(a[i] - b[1]);
		for (int j = 2; j <= n; j++) tmp = min(tmp, ABS(a[i] - b[j]));
		ans = max(ans, tmp);
	}
	printf("%d\n", ans);
} 
