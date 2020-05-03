#include <stdio.h>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(1E5 + 10);
constexpr ll kInf = ll(1E12 + 10);
int sz;
struct seg_tree {
	int a[kN];
	tuple<int, ll, ll, ll, ll> tp[kN << 2];
	void pull(int n) {
		if (get<1>(tp[n << 1]) <= get<1>(tp[n << 1 | 1])) {
			get<4>(tp[n]) = min(get<4>(tp[n << 1]), get<4>(tp[n << 1 | 1]));
			get<1>(tp[n]) = get<1>(tp[n << 1]);
			get<0>(tp[n]) = get<0>(tp[n << 1]);
		}
		else {
			get<4>(tp[n]) = min({get<4>(tp[n << 1]), get<4>(tp[n << 1 | 1]), 
					(get<1>(tp[n << 1]) - get<1>(tp[n << 1 | 1]) - 1) / (a[get<0>(tp[n << 1 | 1])] - a[get<0>(tp[n << 1])]) + 1});
			get<1>(tp[n]) = get<1>(tp[n << 1 | 1]);
			get<0>(tp[n]) = get<0>(tp[n << 1 | 1]);
		}
		return ;
	}
	void addtag(int n, ll f1, ll f2) {
		get<1>(tp[n]) += f1 + a[get<0>(tp[n])] * f2;
		get<2>(tp[n]) += f1;
		get<3>(tp[n]) += f2;
		get<4>(tp[n]) -= f2;
		if (get<4>(tp[n]) <= 0) {
			push(n);
			pull(n);
		}
		return ;
	}
	void push(int n) {
		if (get<2>(tp[n]) || get<3>(tp[n])) {
			addtag(n << 1, get<2>(tp[n]), get<3>(tp[n]));
			addtag(n << 1 | 1, get<2>(tp[n]), get<3>(tp[n]));
			get<2>(tp[n]) = get<3>(tp[n]) = 0;
		}
		return ;
	}
	void dfs(int n = 1, int l = 1, int r = sz) {
		tp[n] = {l, 0, 0, 0, kInf};
		if (l < r) {
			int mid = (l + r) >> 1;
			dfs(n << 1, l, mid);
			dfs(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void init(vector<int> &x) {
		sz = int(x.size()) - 1;
		for (int i = 1; i <= sz; i++) a[i] = x[i];
		dfs();
	}
	void add(int L, ll v, int n = 1, int l = 1, int r = sz) {
		if (L <= l) addtag(n, v, 1);
		else if (L <= r) {
			int mid = (l + r) >> 1;
			push(n);
			if (L <= mid) add(L, v, n << 1, l, mid);
			add(L, v, n << 1 | 1, mid + 1, r);
			pull(n);
		}
		return ;
	}
	void set(int pos, ll v, int n = 1, int l = 1, int r = sz) {
		if (l == r) get<1>(tp[n]) = v;
		else {
			int mid = (l + r) >> 1;
			push(n);
			if (pos <= mid) set(pos, v, n << 1, l, mid);
			else set(pos, v, n << 1 | 1, mid + 1, r);
			pull(n);
		}
		return ;
	}
	ll ask(int R, int n = 1, int l = 1, int r = sz) {
		if (get<0>(tp[n]) <= R) return get<1>(tp[n]);
		else {
			push(n);
			int mid = (l + r) >> 1;
			if (R > mid) return min(ask(R, n << 1, l, mid), ask(R, n << 1 | 1, mid + 1, r));
			return ask(R, n << 1, l, mid);
		}
	}
};

seg_tree sg;
int a[kN];

int main() {
	int n, lst = 1;
	ll bs = 0;
	vector<int> x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	x.PB(-1);
	x.PB(0);
	for (int i = 1; i <= n; i++) x.PB(a[i]);
	sort(x.begin(), x.end());
	x.resize(unique(x.begin(), x.end()) - x.begin());
	sg.init(x);
	for (int i = 1; i <= n; i++) a[i] = lower_bound(x.begin(), x.end(), a[i]) - x.begin();
	for (int i = 2; i <= n; i++) {
		if (a[i] >= a[lst]) {
//			 sg.set(a[i], get<1>(sg.tp[1]));
			 lst = i;
		}
		else {
			sg.set(a[i], sg.ask(a[i]));
			sg.add(a[i], -x[a[lst]]);
			bs += x[a[lst]] - x[a[i]];
		}
	}
	printf("%lld\n", get<1>(sg.tp[1]) + bs);
} 
