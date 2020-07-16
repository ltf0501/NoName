#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 250010;

int n, k;
vector<int> vals;

struct P {
	int x, y;
	P(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	P operator+(P b) const {
		return P(x + b.x, y + b.y);
	}
	P operator-(P b) const {
		return P(x - b.x, y - b.y);
	}
	int64_t operator^(P b) const {
		return 1LL * x * b.y - 1LL * y * b.x;
	}
	bool operator<(P b) const {
		return x != b.x ? x < b.x : y < b.y;
	}
	int64_t abs() const {
		return 1LL * x * x + 1LL * y * y;
	}
} pts[kN];
vector<P> at[kN];

vector<P> ConvexHull(const vector<P> &ps) {
	vector<P> p;
	for (int i = 0; i < int(ps.size()); i++) {
		while (int(p.size()) >= 2 && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0) {
			p.pop_back();
		}
		p.push_back(ps[i]);
	}
	int t = int(p.size());
	for (int i = int(ps.size()) - 2; i >= 0; i--) {
		while (int(p.size()) > t && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0) {
			p.pop_back();
		}
		p.push_back(ps[i]);
	}
	p.pop_back();
	return p;
}

// v needs to be sorted
int64_t Furthest(vector<P> &vv) {
	//cerr << "---\n";
	//for (auto p : v) {
	//	cerr << p.x << ' ' << p.y << '\n';
	//}
	auto hull = ConvexHull(vv);
	auto &v = hull;
	//cerr << "---\n";
//	for (auto p : hull) {
//		cerr << p.x << ' ' << p.y << '\n';
//	}
	if (hull.size() == 1) return 0;
	if (hull.size() == 2) return (v[0] - v[1]).abs();
	int64_t ans = 0;
	for (int p1 = 0, p2 = 1; p1 < int(v.size()); p1++) {
		int nxt1 = p1 + 1;
		if (nxt1 >= int(v.size())) nxt1 -= int(v.size());
		auto l1 = v[nxt1] - v[p1];
		for (;;) {
			int nxt = p2 + 1;
			if (nxt >= int(v.size())) nxt -= int(v.size());
			//cerr << l1.x << ' ' << l1.y << '\n';
			//cerr << (v[nxt] - v[p2]).x << ' ' << (v[nxt] - v[p2]).y << '\n';
			//cerr << p1 << '/' << nxt1 << ":" << p2 << '/' << nxt << ' ' << (l1 ^ (v[nxt] - v[p2])) << '\n';
			if ((l1 ^ (v[nxt] - v[p2])) > 0) {
				ans = max(ans, (v[p1] - v[p2]).abs());
				p2 = nxt;
			} else {
				break;
			}
		}
		//cerr << "PAIR: " << p1 << ' ' << p2 << '\n';
		ans = max(ans, (v[p1] - v[p2]).abs());
	}
	//cerr << "DIST: " << ans << '\n';
	return ans;
}

int Solve(int64_t m) {
	int i = 0, ans = 0;
	while (i < int(vals.size())) {
		int j = 0;
		vector<P> cur = at[i], nxt, tmp;
		while (i + (1 << (j + 1)) <= int(vals.size())) {
			nxt.clear();
			for (int p = i + (1 << j); p < i + (1 << (j + 1)); p++) {
				for (auto x : at[p]) nxt.push_back(x);
			}
			sort(nxt.begin(), nxt.end());
			tmp.resize(cur.size() + nxt.size());
			merge(cur.begin(), cur.end(), nxt.begin(), nxt.end(), tmp.begin());
			if (Furthest(tmp) > m) break;
			swap(cur, tmp);
			++j;
		}
		int l = i + (1 << j) - 1, r = min(int(vals.size()), i + (1 << (j + 1)));
		while (r - l > 1) {
			int mm = (l + r) >> 1;
			nxt.clear();
			for (int p = i + (1 << j); p <= mm; p++) {
				for (auto x : at[p]) nxt.push_back(x);
			}
			sort(nxt.begin(), nxt.end());
			tmp.resize(cur.size() + nxt.size());
			merge(cur.begin(), cur.end(), nxt.begin(), nxt.end(), tmp.begin());
			if (Furthest(tmp) > m) r = mm;
			else l = mm;
		}
		//cerr << i << "->" << r << '\n';
		i = r;
		++ans;
	}
	//cerr << m << ": " << ans << '\n';
	//cerr << "===\n";
	return ans;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> pts[i].x >> pts[i].y;
		vals.push_back(pts[i].x);
	}
	sort(pts, pts + n);
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	for (int i = 0; i < n; i++) {
		auto idx = lower_bound(vals.begin(), vals.end(), pts[i].x) - vals.begin();
		at[idx].push_back(pts[i]);
	}
	int64_t l = 0;
	for (int i = 0; i < int(vals.size()); i++) {
		auto tmp = minmax_element(at[i].begin(), at[i].end());
		l = max<int64_t>(l, tmp.second->y - tmp.first->y);
	}
	l = l * l - 1;
	int64_t r = 2'000'000'000'000'000'000LL;
	//cerr << Solve(7) << '\n';
	//cerr << Solve(8) << '\n';
	//cerr << Solve(9) << '\n';
	//return 0;
	while (r - l > 1) {
		auto m = (l + r) >> 1;
		if (Solve(m) > k) l = m;
		else r = m;
	}
	cout << r << '\n';
} 
