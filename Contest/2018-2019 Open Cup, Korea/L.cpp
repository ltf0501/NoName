#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100010;

int a[kN], b[kN], b_pref[kN], n, nxt[kN][2];
pair<int, int> ans[kN];

pair<int, int> Solve(int x) {
	pair<int, int> ret{};
	int ctr = 1, cnt[2] = {}, cur_type = b[1] >= 0, i = 0, bad = 0;

	auto Jump = [&]() {
		int old_i = i;
		i = max(i + x, nxt[old_i][!cur_type]) - 1;
		ctr += i - old_i;
		if (i >= n) {
			ctr -= i - n + 1;
			i -= i - n + 1;
		}
		int d = b_pref[i] - b_pref[old_i];
		cnt[0] += (ctr - 1) - d;
		cnt[1] += d;
		if (nxt[old_i][!cur_type] <= i) {
			//cerr << "!" << i << ":" << old_i << ":" << i - nxt[old_i][!cur_type] + 1 << "!\n";
			bad += i - nxt[old_i][!cur_type] + 1;
		}
	};

	Jump();
	for (++i; i < n; i++) {
		++cnt[b[i] >= 0];
		if (cnt[!cur_type]) ++bad;
		++ctr;
		if (cnt[!cur_type] && ctr - 1 >= x) {
			--ctr;
			if (cnt[!cur_type]) --bad;
			--cnt[b[i] >= 0];
			++ret.first;
			ret.second += bad;
			//cerr << ctr << ':' << i << ':' << cnt[0] << ':' << cnt[1] << ':' << bad << '/';
			cnt[0] = cnt[1] = 0;
			bad = 0;
			ctr = 1;
			cur_type = b[i + 1] >= 0;
			Jump();
		}
	}
	++ret.first;
	ret.second += bad;
	//cerr << ctr << ':' << n << ':' << cnt[0] << ':' << cnt[1] << ':' << bad << '\n';
	return ret;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) b[i] = a[i] - a[i - 1];
	for (int i = 1; i < n; i++) b_pref[i] = b_pref[i - 1] + (b[i] >= 0);
	nxt[n - 1][0] = nxt[n - 1][1] = INT_MAX;
	for (int i = n - 1; i > 0; i--) {
		nxt[i - 1][0] = nxt[i][0];
		nxt[i - 1][1] = nxt[i][1];
		nxt[i - 1][b[i] >= 0] = i;
	}
	for (int i = 0; i < n; i++) {
		//cerr << nxt[i][0] << ':' << nxt[i][1] << '\n';
	}
	for (int i = 1; i < n; i++) b_pref[i] = b_pref[i - 1] + (b[i] >= 0);
	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		if (!ans[x].first) ans[x] = Solve(x);
		cout << ans[x].first << ' ' << ans[x].second << '\n';
	}
}
