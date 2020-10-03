#include <stdio.h>
#include <tuple>
#include <vector>
using namespace std;
#define PB push_back

constexpr int kN = int(1E3 + 10);

int cnt[kN][kN];

int main() {
	int n;
	vector<tuple<int, int, int>> v;
	scanf("%d", &n);
	if (n & 1) {
		for (int i = 1; i <= n / 2; i++) for (int j = 1; j <= n; j++) v.PB({j, (j + i - 1) % n + 1, (j + i + i - 1) % n + 1});
	}
	else {
		n--;
		for (int i = 1; i <= n / 2; i++) for (int j = 1; j <= n; j++) 
			v.PB({j, (j + i - 1) % n + 1, (j + i + i - 1) % n + 1});
		for (int i = 2; i <= n / 2; i++) for (int j = 1; j <= n; j++) 
			v.PB({j, (j + i - 1) % n + 1, (j + i + i - 1) % n + 1});
		n++;
		for (int i = 1; i < n; i++) v.PB({n, i, i % (n - 1) + 1});
		for (int i = 1; i < n; i++) v.PB({n, i, i % (n - 1) + 1});
		for (int i = 1; i < n; i++) v.PB({n, i, (i + 1) % (n - 1) + 1});
	}

	printf("%d\n", int(v.size()));
	for (tuple<int, int, int> i : v) printf("%d %d %d\n", get<0>(i), get<1>(i), get<2>(i)); 
} 
