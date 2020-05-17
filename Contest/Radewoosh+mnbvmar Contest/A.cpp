#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
using namespace std;
#define F first
#define S second
constexpr int kN = int(3E5 + 10);
constexpr long double eps = 1E-10;
struct seg_tree {
	long double val[kN << 2], flag[kN << 2];
	void pull(int n) {
		val[n] = val[n << 1] + val[n << 1 | 1];
		return ;
	}
	void addtag(int n, int l, int r, long double x) {
		val[n] = (r - l + 1) * x;
		flag[n] = x;
		return ;
	}
	void push(int n, int l, int r) {
		if (flag[n] > eps) {
			int mid = (l + r) >> 1;
			addtag(n << 1, l, mid, flag[n]);
			addtag(n << 1 | 1, mid + 1, r, flag[n]);
			flag[n] = 0;
		}
		return ;
	}
	void init(int n, int l, int r, int a[]) {
		flag[n] = 0;
		if (l == r) val[n] = a[l];
		else {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid, a);
			init(n << 1 | 1, mid + 1, r, a);
			pull(n);
		}
		return ;
	}
	
	void set(int n, int l, int r, int L, int R, long double x) {
		if (L <= l && r <= R) addtag(n, l, r, x);	
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n, l, r);
			set(n << 1, l, mid, L, R, x);
			set(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}

	long double ask(int n, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[n];
		else if (l > R || L > r) return 0;
		else {
			int mid = (l + r) >> 1;
			push(n, l, r);
			return ask(n << 1, l, mid, L, R) + ask(n << 1 | 1, mid + 1, r, L, R);
		}
	}
};

int a[kN];
seg_tree sg;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q, l, r;
	string s;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sg.init(1, 1, n, a);
	while (q--) {
		cin >> s;
		if (s[0] == 'g') {
			cin >> l;
			cout << fixed << setprecision(20) << sg.ask(1, 1, n, l, l) << '\n';
		}
		else {
			cin >> l >> r;
			sg.set(1, 1, n, l, r, sg.ask(1, 1, n, l, r) / (r - l + 1));
		}
	}
} 
