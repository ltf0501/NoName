#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 250010;
const int INF = 1e9;
string s;
int n;
int f[maxn], z[maxn];
int max_left[maxn], ans[maxn];
void failure(string c, int *f) {
	int n = c.size();
	f[0] = f[1] = 0;
	for(int i = 1; i < n; i++) {
		int k = f[i];
		while(k && (c[i] != c[k])) k = f[k];
		f[i + 1] = (c[i] == c[k]) ? k + 1 : 0;
	}
}
void zalg(string str, int len) {
	int l = 0, r = 0;
	for (int i = 0; i < len; i++) {
		if (i > r) {
			l = r = i;
			while (r < len && str[r] == str[r - l]) r++;
			z[i] = r - l;
			r--;
		} else {
			if (z[i - l] < r - i + 1) {
				z[i] = z[i - l];
			} else {
				l = i;
				while (r < len && str[r] == str[r - l]) r++;
				z[i] = r - l;
				--r;
			}
		}
	}
}
ll seg[maxn << 2], pre[maxn << 2], suf[maxn << 2], sum[maxn << 2];
void push_up(int o) {
	seg[o] = max({seg[o << 1], seg[o << 1 | 1], pre[o << 1 | 1] + suf[o << 1]});
	pre[o] = max(pre[o << 1], sum[o << 1] + pre[o << 1 | 1]);
	suf[o] = max(suf[o << 1 | 1], sum[o << 1 | 1] + suf[o << 1]);
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
void build(int l = 1, int r = n, int o = 1) {
	if(l == r) {
		seg[o] = pre[o] = suf[o] = 0;
		sum[o] = -INF;
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, o << 1), build(m + 1, r, o << 1 | 1);
	push_up(o);
}
void update(int x, ll k, int l = 1, int r = n, int o = 1) {
	if(l == r) {
		sum[o] = k;
		seg[o] = pre[o] = suf[o] = max(0ll, k);
		return;
	}
	int m = (l + r) >> 1;
	if(x <= m) update(x, k, l, m, o << 1);
	else update(x, k, m + 1, r, o << 1 | 1);
	push_up(o);
}
tuple<ll, ll, ll, ll> query(int ql, int qr, int l = 1, int r = n, int o = 1) {
	if(ql <= l && r <= qr) return make_tuple(seg[o], pre[o], suf[o], sum[o]);
	int m = (l + r) >> 1;
	if(qr <= m) return query(ql, qr, l, m, o << 1);
	if(ql > m) return query(ql, qr, m + 1, r, o << 1 | 1);
	tuple<ll, ll, ll, ll> le = query(ql, qr, l, m, o << 1);
	tuple<ll, ll, ll, ll> ri = query(ql, qr, m + 1, r, o << 1 | 1);
	tuple<ll, ll, ll, ll> res;
	get<0>(res) = max({get<0>(le), get<0>(ri), get<1>(ri) + get<2>(le)});
	get<1>(res) = max(get<1>(le), get<3>(le) + get<1>(ri));
	get<2>(res) = max(get<2>(ri), get<3>(ri) + get<2>(le));
	get<3>(res) = get<3>(le) + get<3>(ri);
	return res;
}
int main() {
	freopen("cover.in", "r", stdin);
	freopen("cover.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	string s;
	cin >> s;
	n = s.size();
	failure(s, f);
	//s = '0' + s;
	zalg(s, n);
	for(int i = n; i >= 1; i--) z[i] = z[i - 1];
	z[1] = n;
	//for (int i = 1; i <= n; i++) cerr << z[i] << ' ';
	//cerr << endl;
	vector<pair<int, int>> zvals;
	for (int i = 1; i <= n; i++) zvals.emplace_back(z[i], i);
	sort(zvals.begin(), zvals.end());
	build();
	for (int i = 0, l = 0; i <= n; i++) {
		//cerr << "THRES: " << i << endl;
		//for (int i = 1; i <= n; i++) {
		//	cerr << get<0>(query(i, i)) << ' ';
		//}
		//cerr << endl;
		int ll = 1, rr = n + 1;
		while (rr - ll > 1) {
			int m = (ll + rr) >> 1;
			auto res = query(1, m);
			if (get<0>(res) >= i) rr = m;
			else ll = m;
		}
		max_left[i] = ll;
		int r = l;
		while (r < n && zvals[r].first == i) {
			update(zvals[r].second, 1);
			++r;
		}
		l = r;
	}
	//for(int i = 0; i <= n; i++) cerr << "max_left[" << i << "] = " << max_left[i] << "\n";
	for (int i = 1; i <= n; i++) {
		if (f[i]) {
			int candid = ans[f[i]];
			bool ok = max_left[candid] >= i - f[i];
			ans[i] = ok ? candid : i;
		} else {
			ans[i] = i;
		}
		cout << ans[i] << ' ';
	}
	return 0;
}
