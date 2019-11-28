#include <bits/stdc++.h>
using namespace std;
 
constexpr int kC = 1 << 23;
 
int n, p, q, m, cc;
uint32_t SA, SB, SC;
uint32_t rng61() {
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	uint32_t t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}
 
vector<uint32_t> stk, stk_mx;
 
int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int tt = 1; tt <= t; tt++) {
		cout << "Case #" << tt << ": ";
		cin >> n >> p >> q >> m >> SA >> SB >> SC;		
		stk.clear(), stk_mx.clear();
		int64_t ans = 0;
		for (int i = 1; i <= n; i++) {
			if (rng61() % (p + q) < p) {
				auto x = rng61() % m + 1;
				stk.push_back(x);
				uint32_t mx = stk_mx.size() ? max(stk_mx.back(), x) : x;
				stk_mx.push_back(mx);
			} else {
				if (stk.size()) {
					auto x = stk.back();
					stk.pop_back();
					stk_mx.pop_back();
				}
			}
			ans ^= 1LL * i * (stk_mx.size() ? stk_mx.back() : 0);
		}
		cout << ans << '\n';
	}
}
