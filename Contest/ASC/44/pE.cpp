#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int kN = int(1E2 + 10);
void solve(int n) {
	int tot = n + 1;
	vector<int> v;
	n <<= 1;
	printf("1");
	for (int i = 2; i <= n; i++) printf(" %d",i); 
	printf("\n");
	for (int i = 3; i <= tot; i += 2) {
		if (i == tot) i--;
		v.push_back(i);
	}
	for (int i = 1; i <= tot; i += 2) printf("%d ", i);
	for (int i = 2; i < tot; i += 2) v.push_back(i);
	printf("2");
	for (int i = 4; i <= tot; i += 2) printf(" %d", i);
	if (v.size() > tot - 2) v.pop_back();
	for (int i : v) printf(" %d", (i + tot) > n ? i + 2 : i + tot);
	printf("\n");
	printf("1");
	for (int i = tot + 1; i <= n; i++) printf(" %d",i);
	printf(" %d", tot);
	for (int i = 3; i < tot; i++) printf(" %d", i);
	printf(" 2");
	printf("\n");
	return ;
}
int main() {
	#ifdef ONLINE_JUDGE
	freopen("embedding.in", "r", stdin);
	freopen("embedding.out", "w", stdout);
	#endif
	int n;
	while (true) {
	scanf("%d", &n);
		if (n == 3) printf("1 2 3 4 5 6\n1 4 5 3 2 6\n2 6 1 3 4 5\n");
		else if (n == 0) break;
		else solve(n);
	}
}
