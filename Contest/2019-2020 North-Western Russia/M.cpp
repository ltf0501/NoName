#include <stdio.h>
#include <unordered_map>
using namespace std;
typedef long long int ll;
constexpr int kN = int(2E3 + 10);
int a[kN];

ll solve() {
	unordered_map<int, int> m;
	int n;
	ll ans = 0;
	scanf("%d", &n);
	m.reserve(n * n);
	m.max_load_factor(0.5);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i - 1; j++) m[a[j] + a[i]]--;
		for (int j = i + 1; j <= n; j++) m[a[i - 1] + a[j]]++;
		ans += m[a[i] << 1];
	}

	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) printf("%lld\n", solve());
} 
