#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 1'000'000'007, kN = 1'000'010;

int fact[kN * 2], ifact[kN * 2], a[kN];
pair<int, int> st[kN * 4];
//pair<int, int> sparse[21][kN];
vector<int> vals, idx[kN];

int Pow(int x, int e) {
	if (!e) return 1;
	auto t = Pow(int(1LL * x * x % kMod), e >> 1);
	return (e & 1) ? int(1LL * t * x % kMod) : t;
}

int Catalan(int n) {
	return int(1LL * fact[n * 2] * ifact[n] % kMod * ifact[n + 1] % kMod);
}

void Build(int id, int l, int r) {
	if (l == r) st[id] = {a[l], l};
	else {
		int m = (l + r) >> 1;
		Build(id << 1, l, m);
		Build(id << 1 | 1, m + 1, r);
		st[id] = min(st[id << 1], st[id << 1 | 1]);
	}
}

pair<int, int> Query(int id, int l, int r, int qL, int qR) {
	if (qL <= l && r <= qR) return st[id];
	int m = (l + r) >> 1;
	pair<int, int> ret = {1e9, 0};
	if (qL <= m) ret = min(ret, Query(id << 1, l, m, qL, qR));
	if (m < qR) ret = min(ret, Query(id << 1 | 1, m + 1, r, qL, qR));
	return ret;
}

pair<int, int> Query(int qL, int qR) {
	//cerr << qL << ' ' << qR << Query(1, 0, kN - 1, qL, qR).first << '\n';
	return Query(1, 0, kN - 1, qL, qR);
	//int i = __lg(r - l + 1);
	//assert(l <= r);
	//int i = 0;
	//while ((1 << i) <= r - l + 1) ++i;
	//--i;
	////cerr << l << ' ' << r << ' ' << i << ' ' << (r - (1 << i) + 1) << '\n';
	//assert(r - (1 << i) + 1 >= 0);
//	pair<int, int> ret = min(sparse[i][l], sparse[i][r - (1 << i) + 1]);
//	return ret;
}

int Dfs(int l, int r) {
	if (r - l + 1 <= 1) return 1;
	//cerr << l << ' ' << r << '\n';
	auto q = Query(l, r);
	int mn = q.first, cnt = 1;
	int64_t ans = Dfs(l, q.second - 1);
	//cerr << q.second << '\n';
	for (;;) {
		if (q.second == r) break;
		auto q2 = Query(q.second + 1, r);
		////cerr << q.second + 1 << ' ' << q2.second << '\n';
		if (q2.first == mn) {
			ans = ans * Dfs(q.second + 1, q2.second - 1) % kMod;
			q = q2;
			++cnt;
			//cerr << q.second << '\n';
		} else {
			break;
		}
	}
	//cerr << l << ' ' << r << ' ' << cnt << '\n';
	ans = ans * Dfs(q.second + 1, r) % kMod;
	ans = ans * Catalan(cnt) % kMod;
	return int(ans);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	fact[0] = 1;
	for (int i = 1; i <= n * 2; i++) {
		fact[i] = int(1LL * fact[i - 1] * i % kMod);
	}
	ifact[n * 2] = Pow(fact[n * 2], kMod - 2);
	for (int i = n * 2 - 1; i >= 0; i--) {
		ifact[i] = int(1LL * ifact[i + 1] * (i + 1) % kMod);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		vals.push_back(a[i]);
		idx[a[i]].push_back(i);
	}
	Build(1, 0, kN - 1);
	//for (int i = 0; i < n; i++) sparse[0][i] = {a[i], i};
	//for (int i = 0, d = 1; d < n; i++, d <<= 1) {
	//	for (int j = 0; j + d < n; j++) {
	//		sparse[i + 1][j] = min(sparse[i][j], sparse[i][j + d]);
	//	}
	//}
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	cout << Dfs(0, n - 1) << '\n';
} 
