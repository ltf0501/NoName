#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int kN = int(3E5 + 10);
#define PB push_back
int a[kN];
int main() {
	int k, n, m, lst = 1, now = 1, cnt;
	vector<int> v;
	scanf("%d%d%d", &k, &n, &m);
	for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
	if (a[1] == -1) a[1] = 1;
	for (int i = 2; i <= k; i++) if (a[i] == -1) a[i] = a[i - 1];
	for (int i = 2; i <= k; i++) if (a[i] < a[i - 1]) {
		printf("-1\n");
		return 0;
	}
	if (n < k) {
		printf("-1\n");
		return 0;
	}

	for (int i = 1; i <= k; i++) v.PB(a[i]);
	reverse(v.begin(), v.end());

	a[k + 1] = m;
	for (int i = 1; i <= k; i++) {
		for (int j = a[i] + 1; j <= a[i + 1]; j++) {
			cnt = 0;
			while (cnt < i && v.size() < n) {
				v.PB(j);
				cnt++;
			}
			if (v.size() >= n) break;
		}
			if (v.size() >= n) break;
	}
	reverse(v.begin(), v.end());
	if (v.size() < n) printf("-1\n");	
	else {
		printf("%d", v[0]);
		for (int i = 1; i < n; i++) printf(" %d", v[i]);
		printf("\n");
	}
} 
