#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(5E3 + 10);
int dp[kN];

void pre() {
	dp[0] = 0;
	dp[1] = 0;
	vector<int> v;
	for (int i = 2; i < kN; i++) {
		v.clear();
		dp[i] = -1;
		for (int j = 1; j < i; j++) v.PB(dp[j - 1] ^ dp[i - j - 1]);
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for (int j = 0; j < v.size(); j++) if (v[j] != j) {
			dp[i] = j;
			break;
		}
		if (dp[i] == -1) dp[i] = int(v.size());
	}
	return ;
}

int main() {
	int t, n;
	scanf("%d", &t);
	pre();
	while (t--) {
		scanf("%d", &n);
		if (dp[n] != 0) printf("First\n");
		else printf("Second\n");
	}
}

