#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 20;
const ll kInf = 1e16;

int n;
int r[1 << kN], b[1 << kN];
ll R[1 << kN], B[1 << kN];
ll dp[1 << kN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < (1 << n); i++) scanf("%d", r + i);
	for(int i = 0; i < (1 << n); i++) scanf("%d", b + i);

	for(int i = 0; i < (1 << n); i++) R[i] = r[i], B[i] = b[i];
	for(int i = 0; i < n; i++) {
		for(int mask = 0; mask < (1 << n); mask++) {
			if(mask & (1 << i)) R[mask] += R[mask ^ (1 << i)], B[mask] += B[mask ^ (1 << i)];
		}
	}

	for(int i = 1; i < (1 << n); i++) dp[i] = kInf;

	dp[0] = min(R[0], B[0]);
	for(int mask = 1; mask < (1 << n); mask++) {
		for(int i = 0; i < n; i++) if(mask & (1 << i)) {
			dp[mask] = min(dp[mask], min(R[mask] - R[mask ^ (1 << i)], B[mask] - B[mask ^ (1 << i)]) + dp[mask ^ (1 << i)]); 
		}
	}
	printf("%lld\n", dp[(1 << n) - 1]);
	return 0; 
} 
