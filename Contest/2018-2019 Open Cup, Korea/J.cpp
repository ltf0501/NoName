#include <bits/stdc++.h>
using namespace std;
 
int h[300010], par[300010], djs[300010], n, L[300010], R[300010];
bool went[300010];
pair<int, int> qu[300010];
vector<int> v[300010];
 
int Find(int x) { return x == par[x] ? x : par[x] = Find(par[x]); }
 
void Merge(int x, int y) {
	int px = x, py = y;
	par[px] = py;
	djs[py] = djs[px];
}
int now;
int64_t ans;
vector<int64_t> arr;
void pre() {
	now = 0;
	int top = 0, last = 0;
	for (int i = 0; i < n; i++) {
		par[i] = djs[i] = i;
		went[i] = false;
	}
	while (top < n) {
		last = top;
		while (top < n && (last == top || qu[top].first == qu[last].first)) {
			int p = qu[top++].second;
			if (p > 0 && went[p - 1]) Merge(p - 1, p);
			if (p + 1 < n && went[p + 1]) Merge(p, Find(p + 1));
			went[p] = true;
		}
		for (int i = last; i < top; i++) L[i] = djs[Find(qu[i].second)], R[i] = Find(qu[i].second), v[now].push_back(i);
		now++;
	}
	return ;
}
 
void Solve(int64_t area_r, int64_t area_l = 0, bool collect = false) {
	ans = 0;
	if (area_r <= 0) return ;
	for (int j = 0; j < now; j++) {
		auto req_w = area_r / qu[v[j][0]].first;
		auto req_w_l = (area_l + qu[v[j][0]].first - 1) / qu[v[j][0]].first;
		auto req_w_r = area_r / qu[v[j][0]].first;
		int last_r = INT_MAX;
		if (collect) {
			for (int i : v[j]) {
				auto c = qu[i];
				int64_t l_w = c.second - L[i], r_w = min(last_r - 1, R[i]) - c.second;
				last_r = c.second;
				l_w = min(l_w, req_w_r - 1);
				for (int64_t i = max(0LL, req_w_l - r_w - 1); i <= l_w; i++) if (req_w_l - i - 1 <= r_w) { 
					for (int64_t j = max(req_w_l - i - 1, 0LL); j <= r_w; j++) 
						if (i + j + 1 <= req_w_r) arr.push_back(c.first * (i + j + 1));
						else break;
				}
				else break;
			}
		}
		else if (req_w) for (int i : v[j]) {
			auto c = qu[i];
			int64_t l_w = c.second - L[i], r_w = min(last_r - 1, R[i]) - c.second;
			last_r = c.second;
			l_w = min(l_w, req_w - 1);
			r_w = min(r_w, req_w - 1);
			if (l_w + r_w + 1 <= req_w) {
				ans += (l_w + 1) * (r_w + 1);
			} else {
				ans += (r_w + 1) * (req_w - r_w);
				ans += req_w * (l_w - (req_w - r_w) + 1);
				ans -= ((req_w - r_w + l_w) * (l_w - (req_w - r_w) + 1)) >> 1;
			}
		}
	}
	return ;
}
 
int64_t SearchVal(int64_t q) {
	int64_t al = 0, ar = n * 1'000'000'000LL + 1;
	while (al + 1 != ar) {
		auto am = (al + ar) >> 1;
		Solve(am);
		if (ans >= q)
			ar = am;
		else
			al = am;
	}
	return ar;
}
 
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> h[i];
		qu[i] = {h[i], i};
	}
	sort(qu, qu + n, greater<pair<int, int>>());
	pre();
	int64_t l, r; 
	cin >> l >> r;
	auto area_l = SearchVal(l);
	auto area_r = SearchVal(r);
	Solve(area_l);
	auto idx_l = ans + 1; 
	Solve(area_r - 1);
	auto idx_r = ans + 1; 
	if (area_l == area_r) {
		for (auto i = l; i <= r; i++) cout << area_l << ' ';
		cout << '\n';
		return 0;
	}
	for (auto i = l; i < idx_l; i++) cout << area_l << ' ';
	Solve(area_r - 1, area_l + 1, true);
	sort(arr.begin(), arr.end());
	for (auto a : arr) cout << a << ' ';
	for (auto i = idx_r; i <= r; i++) cout << area_r << ' ';
	cout << '\n';
}
