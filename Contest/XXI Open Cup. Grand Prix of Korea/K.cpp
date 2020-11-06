#include <bits/stdc++.h>
using namespace std;
const int kN = 1e3 + 10;
typedef pair<int, int> pii;
#define F first
#define S second

int n;
pair<pii, int> a[kN];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		a[i] = make_pair(make_pair(x, y), i);
	}
	sort(a + 1, a + n + 1);
	printf("%d\n", 2 * n - 1);
	for(int i = 1; i <= n; i++) printf("%d ", a[i].S);
	for(int i = n - 1; i >= 1; i--) printf("%d ", a[i].S); 
	puts("");
	return 0;
} 
