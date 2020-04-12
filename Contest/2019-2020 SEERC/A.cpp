#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

int n, m;
int a[kN];
int cnt[kN], pre[kN];
int minus[kN];
vector<int> pos[kN];
int sgn[kN];

int CalcAns(int l, int r) { return r - l + 1 > 2 ? (r - l + 1 - 1) / 2 : 0; }
void Break(int p, map<int, int> &segs, int &ans) {
	auto it = segs.lower_bound(p);
	if (it == segs.end()) {
		it = segs.find(segs.rbegin()->first);
	} else {
		if (it->first == p) return;
		it = prev(it);
	}
	ans -= CalcAns(it->first, it->second);
	ans += CalcAns(it->first, p - 1);
	ans += CalcAns(p, it->second);
	segs[p] = it->second;
	it->second = p - 1;
}
void Mend(int p, map<int, int> &segs, int &ans) {
	auto it = segs.lower_bound(p);
	if (it == segs.begin() || it->first != p) return;
	auto prv = prev(it);
	ans -= CalcAns(it->first, it->second);
	ans -= CalcAns(prv->first, prv->second);
	ans += CalcAns(prv->first, it->second);
	prv->second = it->second;
	segs.erase(it);
}

void add(int x, int y) { // add [x, y)
	if(x == y) return;
	if(x > y) swap(x, y);
	pre[x + 1]++, pre[y]--;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]), cnt[a[i]]++, pos[a[i]].push_back(i);

	for(int i = 0; i < n; i++) {
		add(a[i], a[(i + 1) % n]);	
	}

	vector<int> qs;
	unordered_map<int, int> q_ans;
	for (int i = 0; i < n; i++) qs.push_back(a[i]);
	sort(qs.begin(), qs.end());
	qs.erase(unique(qs.begin(), qs.end()), qs.end());
	for (int i = 0; i < n; i++) {
		sgn[i] = a[i] > qs[0] ? 1 : a[i] < qs[0] ? -1 : 0;
	}
	map<int, int> segs;
	int ans = 0;
	int l = 0;
	for (int i = 1; i < n; i++) {
		if (sgn[i - 1] && sgn[i] && sgn[i - 1] != sgn[i]) {
			// PASS
		} else {
			segs[l] = i - 1;
			ans += CalcAns(l, i - 1);
			l = i;
		}
	}
	segs[l] = n - 1;
	ans += CalcAns(l, n - 1);
	int v = qs[0];
	for (int q : qs) {
		auto DeBuG = [&]() {
			cerr << "Q: " << q << '\n';
			cerr << "SIGN: ";
			for (int i = 0; i < n; i++) cerr << sgn[i] << ' ';
			cerr << '\n';
			cerr << "SEGS: ";
			for (auto p : segs) cerr << p.first << '/' << p.second << ' ';
			cerr << '\n';
			cerr << "QANS: " << q_ans[q] << '\n';
		};
		while (v < q) {
			for (int p : pos[v]) sgn[p] = -1;
			for (int p : pos[v]) {
				if (p + 1 < n && sgn[p] == sgn[p + 1]) Break(p + 1, segs, ans);
				if (p && sgn[p - 1] == sgn[p]) Break(p, segs, ans);
				if (p + 1 < n && sgn[p] != sgn[p + 1]) Mend(p + 1, segs, ans);
				if (p && sgn[p - 1] != sgn[p]) Mend(p, segs, ans);
			}
			++v;
		}
		for (int p : pos[q]) {
			sgn[p] = 0;
			if (p + 1 < n) Break(p + 1, segs, ans);
			if (p) Break(p, segs, ans);
		}
		q_ans[q] = ans;
		//DeBuG();
		if (sgn[0] && sgn[n - 1] && sgn[0] != sgn[n - 1]) {
			q_ans[q] -= CalcAns(segs.begin()->first, segs.begin()->second);
			q_ans[q] -= CalcAns(segs.rbegin()->first, segs.rbegin()->second);
			q_ans[q] += CalcAns(segs.rbegin()->first, segs.begin()->second + n);
		}
		for (int p : pos[q]) sgn[p] = -1;
		for (int p : pos[q]) {
			if (p + 1 < n && sgn[p] == sgn[p + 1]) Break(p + 1, segs, ans);
			if (p && sgn[p - 1] == sgn[p]) Break(p, segs, ans);
			if (p + 1 < n && sgn[p] != sgn[p + 1]) Mend(p + 1, segs, ans);
			if (p && sgn[p - 1] != sgn[p]) Mend(p, segs, ans);
		}
		++v;
	}

	for(int i = 1; i <= m; i++) pre[i] += pre[i - 1];
	//for(int i = 1; i <= m; i++) printf("%d ", pre[i]);
	//puts("");
	//for(int i = 1; i <= m; i++) printf("%d ", cnt[i]);
	//puts("");
	for(int i = 1; i <= m; i++) {
		if(cnt[i] == 0) printf("-1 ");
		else printf("%d ", n - cnt[i] + pre[i] - q_ans[i]);
	}
	puts("");
	return 0;
} 
