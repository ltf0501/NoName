#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e6 + 10;
const int kMod = 1e9 + 7;
const int kInf = 1e9;

int n;
int a[kN];
int main() {
	scanf("%d", &n);
	int mx = -kInf, mn = kInf;
	int mx_id = -1, mn_id = -1;

	vector<int> p[2];
	bool is0 = 0;

	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		if(x > 0) p[1].push_back(x);
		else if(x < 0) p[0].push_back(x);
		else is0 = 1;
	}
	sort(p[0].begin(), p[0].end());
	sort(p[1].begin(), p[1].end());
	if(p[0].empty() && p[1].empty()) return puts("0 0"), 0;

	if(p[0].empty()) {
		ll sum = 0;
		for(int x : p[1]) sum = (sum + x) % kMod;
		ll mn = is0 ? 0 : 1LL * (sum - p[1][0]) * p[1][0] % kMod;
		if(mn < 0) mn += kMod;
		ll mx = 1LL * (sum - p[1].back()) * p[1].back() % kMod;
		if(mx < 0) mx += kMod;
		printf("%lld %lld\n", mn, mx);
	}
	else if(p[1].empty()) {
		ll sum = 0;
		for(int x : p[0]) sum = (sum - x) % kMod;
		//printf("sum = %lld\n", sum);
		ll mn = is0 ? 0 : 1LL * (sum + p[0].back() + kMod) * -p[0].back() % kMod;
		if(mn < 0) mn += kMod;
		ll mx = 1LL * (sum + p[0][0] + kMod) * -p[0][0] % kMod;
		if(mx < 0) mx += kMod;
		printf("%lld %lld\n", mn, mx);
	}
	else {
		int mx = p[1].back(), mn = p[0][0];
		ll ans = 0;
		for(int i = 1; i < int(p[0].size()); i++) ans = (ans + 1LL * p[0][i] * mx % kMod + kMod) % kMod;
		for(int i = 0; i < int(p[1].size()) - 1; i++) ans = (ans + 1LL * p[1][i] * mn % kMod + kMod) % kMod;
		ans = (ans + 1LL * mx * mn % kMod + kMod) % kMod;
		printf("%lld ", ans);

		ans = 0;
		for(int i = 1; i < int(p[0].size()); i++) ans = (ans + 1LL * p[0][i] * mn % kMod + kMod) % kMod;
		for(int i = 0; i < int(p[1].size()) - 1; i++) ans = (ans + 1LL * p[1][i] * mx % kMod + kMod) % kMod;
		ans = (ans + 1LL * p[0].back() * p[1][0] % kMod + kMod) % kMod;
		printf("%lld\n", ans);
	}
	//for(int i = 0; i < n; i++) {
	//	scanf("%d", &a[i]);

	//	if(mx < a[i]) {
	//		mx = a[i], mx_id = i;
	//	}
	//	if(mn > a[i]) {
	//		mn = a[i], mn_id = i;
	//	}
	//}
	//printf("mx_id = %d, mn_id = %d, mx = %d, mn = %d\n", mx_id, mn_id, mx, mn);


	//ll ans = 0; //min
	//bool ok[2] = {};
	//for(int i = 0; i < n; i++) if(i != mn_id && i != mx_id) {
	//	if(a[i] > 0) ans = (ans + 1LL * a[i] * mn % kMod + kMod) % kMod, ok[0] = 1;
	//	else ans = (ans + 1LL * a[i] * mx % kMod + kMod) % kMod, ok[1] = 1;
	//}


	//printf("%lld\n", ans);

	//ans = 0; //max
	//ok[0] = ok[1] = 0;
	//for(int i = 0; i < n; i++) if(i != mx_id && i != mn_id) {
	//	if(a[i] > 0) ans = (ans + 1LL * a[i] * mx % kMod + kMod) % kMod, ok[1] = 1;
	//	else ans = (ans + 1LL * a[i] * mn % kMod + kMod) % kMod, ok[0] = 1;
	//}
	//printf("%lld\n", ans);
	return 0;
}
