#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

#define F first
#define S second

typedef long long int ll;
constexpr int kMod = int(1E9 + 7), kN = int(1E5 + 10);

ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}

ll Rev(ll n) {return Pow(n, kMod - 2);}

struct Flag {
	int64_t mul, add;
	Flag() : mul(1), add(0) {}
	Flag(int64_t m, int64_t a) : mul(m), add(a) {}
	bool empty() { return mul == 1 && add == 0; }
	int64_t apply(int64_t x) {
		return (x * mul + add) % kMod;
	}
};

Flag operator+(const Flag &a, const Flag &b) {
	return Flag(a.mul * b.mul % kMod, (a.add * b.mul + b.add) % kMod);
}

struct seg_tree {
	ll val[kN << 2];
	Flag flag[kN << 2];
	void pull(int n) {
		val[n] = val[n << 1] + val[n << 1 | 1];
		return ;
	}
	// flag[n] = flag[n] + Flag(a, b);
	void push(int n) {
		if (!flag[n].empty()) {
			flag[n << 1] = flag[n << 1] + flag[n];
			val[n << 1] = flag[n].apply(val[n << 1]);
			flag[n << 1 | 1] = flag[n << 1 | 1] + flag[n];
			val[n << 1 | 1] = flag[n].apply(val[n << 1 | 1]);
			flag[n] = Flag();
		}
	}
	void init(int n, int l, int r) {
		flag[n] = Flag(1, 0);
		if (l == r) val[n] = 1; 
		else {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
			pull(n);
		}
		return ;	
	}
	void set(int n, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			auto f = Flag(0, 1);
			flag[n] = flag[n] + f;
			val[n] = f.apply(val[n]);
		}
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			set(n << 1, l, mid, L, R);
			set(n << 1, mid + 1, r, L, R);
			pull(n);
		}
		return ;
	}
	void mul(int n, int l, int r, int L, int R, ll x) {
		if (L <= l && r <= R) {
			auto f = Flag(x, 0);
			flag[n] = flag[n] + f;
			val[n] = f.apply(val[n]);
		}
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			mul(n << 1, l, mid, L, R, x);
			mul(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	ll ask(int n, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[n];
		else if (l > R || L > r) return 0;
		else {
			int mid = (l + r) >> 1;
			push(n);
			return (ask(n << 1, l, mid, L, R) + ask(n << 1 | 1, mid + 1, r, L, R)) % kMod;
		}
	}
};



int l[kN], r[kN], x[kN], n;
string s[kN];
seg_tree sg;
map<int, pair<int, ll>> ma;
ll ans;

void insert(int L, int R, ll val) {
	map<int, pair<int, ll>>:: iterator u;
	pair<int, pair<int, ll>> tmp;
	u = --ma.upper_bound(L);
	if (u -> S.F >= R) {
		tmp = *u;
		ma.erase(u);
		ans = (ans + sg.ask(1, 1, n, L, R) * tmp.S.S) % kMod;
		sg.set(1, 1, n, L, R);
		if (tmp.F < L) ma.insert({tmp.F, {L - 1, tmp.S.S}});
		if (tmp.S.F > R) ma.insert({R + 1, {tmp.S.F, tmp.S.S}});
	}
	else {
		tmp = *u;
		ma.erase(u);
		ans = (ans + sg.ask(1, 1, n, L, tmp.S.F) * tmp.S.S) % kMod;
		sg.set(1, 1, n, L, tmp.S.F);
		if (tmp.F < L) ma.insert({tmp.F, {L - 1, tmp.S.S}});
	}
	while (true) {
		u = ma.lower_bound(L);
		if (u == ma.end()) break;
		if (u -> F > R) break;
		tmp = *u;
		ma.erase(u);
		if (tmp.S.F >= R) {
			ans = (ans + sg.ask(1, 1, n, tmp.F, R) * tmp.S.S) % kMod;
			sg.set(1, 1, n, tmp.F, R);
		}
		else {
			ans = (ans + sg.ask(1, 1, n, tmp.F, tmp.S.F) * tmp.S.S) % kMod;
			sg.set(1, 1, n, tmp.F, tmp.S.F);
		}
		if (tmp.S.F > R) ma.insert({R + 1, {tmp.S.F, tmp.S.S}});
	}
	ma.insert({L, {R, val}});
	return ;
}

int main() {
	int q;
	cin >> n >> q;
	for (int i = 1; i <= q; i++) cin >> l[i] >> r[i] >> s[i] >> x[i];
	ma[1] = {n, 0};

	sg.init(1, 1, n);
	for (int i = 1; i <= q; i++) {
		if (s[i][0] == '+') insert(l[i], r[i], x[i]);
		else if (s[i][0] == '-') insert(l[i], r[i], kMod - x[i]);
		else if (s[i][0] == '*') sg.mul(1, 1, n, l[i], r[i], x[i]);
		else sg.mul(1, 1, n, l[i], r[i], Rev(x[i]));

		//for (pair<int, pair<int, ll>> i : ma) printf("(%d, (%d, %lld))\n", i.F, i.S.F, i.S.S);
		//for (pair<int, pair<int, ll>> i : ma) printf("(%d, (%d, %lld))\n", i.F, i.S.F, sg.ask(1, 1, n, i.F, i.S.F));
		//printf("ans = %lld\n", ans);
	}

	for (pair<int, pair<int, ll>> i : ma) 
		ans = (ans + sg.ask(1, 1, n, i.F, i.S.F) * i.S.S) % kMod;
	printf("%lld\n", ans);
}
