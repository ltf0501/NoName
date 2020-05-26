#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 200010, kM = 20, kMod = 1'000'000'007;

int n, m, st[kN * 4][kM], a[kN];

struct Ans {
	int v[kM];
};

void Merge(int *l, int *r, int *res) {
	//int pref_l[kM + 1] = {}, pref_r[kM + 1] = {};
	//for (int i = 0; i < m; i++) {
	//	pref_l[i + 1] = pref_l[i] + l[i];
	//	pref_r[i + 1] = pref_r[i] + r[i];
	//}
	//int64_t tmp[kM + kM] = {};
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j <= i; j++) {
	//		tmp[i] += 1LL * l[j] * r[i - j];
	//	}
	//	res[i] = tmp[i] % kMod;
	//}
	//for (int i = m; i < m + m; i++) {
	//	for (int j = i - m + 1; j < m; j++) {
	//		// i - j < m => j > i - m
	//		tmp[i] += 1LL * l[j] * r[i - j];
	//	}
	//	res[i - m] += tmp[i] % kMod;
	//}
	uint64_t tmp[kM + kM] = {};
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i + j] += 1LL * l[i] * r[j];
			if (__builtin_expect(tmp[i + j] > 8'000'000'000'000'000'000ULL, false)) {
				tmp[i + j] %= kMod;
			}
		}
	}
	for (int i = 0; i < m; i++) res[i] = int((tmp[i] + tmp[i + m]) % kMod);
}

void Build(int id, int l, int r) {
	if (l == r) {
		++st[id][a[l] % m];
		++st[id][0];
	} else {
		int mid = (l + r) >> 1;
		Build(id << 1, l, mid);
		Build(id << 1 | 1, mid + 1, r);
		Merge(st[id << 1], st[id << 1 | 1], st[id]);
	}
}

Ans Query(int id, int l, int r, int qL, int qR) {
	if (qL <= l && r <= qR) {
		Ans ret{};
		memcpy(&ret, st[id], sizeof(ret));
		return ret;
	}
	int mid = (l + r) >> 1;
	bool ll = false, rr = false;
	Ans la{}, ra{};
	if (qL <= mid) la = Query(id << 1, l, mid, qL, qR), ll = true;
	if (mid < qR) ra = Query(id << 1 | 1, mid + 1, r, qL, qR), rr = true;
	if (ll && rr) {
		Ans ma{};
		Merge(la.v, ra.v, ma.v);
		return ma;
	}
	return ll ? la : ra;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> a[i];
	Build(1, 0, n - 1);
//	for (int i = 0; i < n; i++) {
//		Ans qq = Query(1, 0, n - 1, i, i);
//		for (int j = 0; j < kM; j++) cerr << qq.v[j] << ' ';
//		cerr << '\n';
//	}
//	return 0;
	int q; cin >> q;
	while (q--) {
		int l, r; cin >> l >> r;
		--l;
		--r;
		cout << Query(1, 0, n - 1, l, r).v[0] << '\n';
	}
} 
