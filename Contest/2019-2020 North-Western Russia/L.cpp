#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 200010;
constexpr int kInf = 1e9;
constexpr double kEps = 1E-6;

int sa[kN], tmp[2][kN], cnt[kN], hi[kN], r[kN], nn;
int sparse[20][2 * kN];

void Build(string s) {
	int *rnk = tmp[0], *rkn = tmp[1], sigma = 256;
	int n = int(s.length());
	for (int i = 0; i < sigma; i++) cnt[i] = 0;
	for (int i = 0; i < n; i++) ++cnt[rnk[i] = s[i]];
	for (int i = 1; i < sigma; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		sa[--cnt[uint8_t(s[i])]] = i;
	}
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < sigma; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) ++cnt[rnk[i]];
		for (int i = 1; i < sigma; i++) {
			cnt[i] += cnt[i - 1];
		}
		int *sa2 = rkn;
		int p = 0;
		for (int i = n - k; i < n; i++) sa2[p++] = i;
		for (int i = 0; i < n; i++) {
			if (sa[i] >= k) sa2[p++] = sa[i] - k;
		}
		for (int i = n - 1; i >= 0; i--) {
			sa[--cnt[rnk[sa2[i]]]] = sa2[i];
		}
		rkn[sa[0]] = p = 0;
		for (int i = 1; i < n; i++) {
			if (!(rnk[sa[i - 1]] == rnk[sa[i]] && sa[i - 1] + k < n && rnk[sa[i - 1] + k] == rnk[sa[i] + k])) ++p;

			rkn[sa[i]] = p;
		}
		swap(rnk, rkn);
		if (p == n - 1) break;
		sigma = p + 1;
	}
	for (int i = 0; i < n; i++) r[sa[i]] = i;
	int id = 0;
	hi[0] = 0;
	for (int i = 0; i < n; i++) {
		if (!r[i]) {
			id = 0;
			continue;
		}
		while (i + id < n && s[i + id] == s[sa[r[i] - 1] + id]) ++id;
		hi[r[i]] = id ? id-- : 0;
	}

	//for(int i = 0; i < n; i++) cerr << sa[i] << ' '; cerr << '\n';
	//for(int i = 0; i < n; i++) cerr << r[i] << ' '; cerr << '\n';
	//for(int i = 1; i < n; i++) cerr << hi[i] << ' '; cerr << '\n';
	for (int i = 0; i < n; i++) sparse[0][i] = hi[i];
	for (int i = n; i <= n * 2; i++) sparse[0][i] = 1e9;
	for (int i = 1, d = 1; d < n; i++, d <<= 1) {
		for (int j = 0; j < n; j++) {
			sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + d]);
		}
	}
}

int QueryLcp(int l, int ri) {
	if (l > ri) swap(l, ri);
	if (l < 0 || ri >= nn) return -1;
	++l;
	int d = __lg(ri - l + 1);
	return min(sparse[d][l], sparse[d][ri - (1 << d) + 1]);
}

int64_t a = 1, b = 1;

int p[kN], sz[kN];
set<int> s[kN];
int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}
void Union(int x, int y, int h) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y], p[y] = x;
	for(auto val : s[y]) {
		auto it = s[x].lower_bound(val);
		int mn = kInf;
		if(it != s[x].end()) mn = *it - val;
		if(it != s[x].begin()) mn = min(mn, val - *prev(it));
		if(a * mn < b * (h + mn)) a = h + mn, b = mn;
		s[x].insert(val);
	}
}
vector<int> mrge[kN];
int main() {
	string str; cin >> str;
	Build(str);
	nn = int(str.size());
	for(int i = 1; i < nn; i++) {
		mrge[hi[i]].push_back(i);	
	}

	for(int i = 0; i < nn; i++) p[i] = i, sz[i] = 1, s[i].insert(i);
	for(int len = nn; len >= 0; len--) {
		for(int id : mrge[len]) {
			int l = sa[id - 1], r = sa[id];
			Union(l, r, len);
		}
	}
	int64_t g = __gcd(a, b);
	a /= g, b /= g;
	cout << a << '/' << b << '\n';
	return 0;
}

