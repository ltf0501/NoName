#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
typedef long long int ll;
constexpr int kN = int(1E6 + 10), kInf = int(1E7 + 10);

struct seg_tree {
	int val[kN << 2], cnt[kN << 2], flag[kN << 2];
	void addtag(int n, int x) {
		val[n] += x;
		flag[n] += x;
		return ;
	}
	void pull(int n) {
		if (val[n << 1] < val[n << 1 | 1]) val[n] = val[n << 1], cnt[n] = cnt[n << 1];
		else if (val[n << 1] > val[n << 1 | 1]) val[n] = val[n << 1 | 1], cnt[n] = cnt[n << 1 | 1];
		else val[n] = val[n << 1], cnt[n] = cnt[n << 1] + cnt[n << 1 | 1];
		return ;
	}
	void push(int n) {
		if (flag[n]) {
			addtag(n << 1, flag[n]);
			addtag(n << 1 | 1, flag[n]);
			flag[n] = 0;
		}
		return ;
	}
	void init(int n, int l, int r) {
		if (l == r) val[n] = 0, cnt[n] = 1, flag[n] = 0;
		else {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid), init(n << 1 | 1, mid + 1, r);
			pull(n);
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) addtag(n, x);
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			add(n << 1, l, mid, L, R, x), add(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	int ask(int n, int l, int r, int L, int R) {
		if (val[n] > 0 || l > R || L > r) return 0;
		else if (L <= l && r <= R) return cnt[n];
		else {
			int mid = (l + r) >> 1;
			return ask(n << 1, l, mid, L, R) + ask(n << 1 | 1, mid + 1, r, L, R);
		}
	}
};

seg_tree sg;
int pos[kN], a[kN];

int main() {
	int n, lst = 1, npos, nxt;
	ll ans = 0;
	deque<pair<int, int>> dq;
	pair<int, int> tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sg.init(1, 1, n); // all 0
	for (int i = 1; i <= n; i++) {
		if (pos[a[i]]) {
			if (lst <= pos[a[i]]) {
				sg.add(1, 1, n, lst, pos[a[i]], kInf);
				lst = pos[a[i]] + 1;
			}
		}
		pos[a[i]] = i;
		while (!dq.empty() && dq.front().S < lst) dq.pop_front();
		sg.add(1, 1, n, i, i, a[i]);
		npos = i - 1;
		while (!dq.empty()) {
			if (a[i] > dq.back().F) {
				tmp = dq.back();
				dq.pop_back();
				if (!dq.empty()) nxt = dq.back().S + 1;	
				else nxt = lst;
				sg.add(1, 1, n, nxt, npos, a[i] - tmp.F);
				npos = nxt - 1;
			}
			else break;
		}
		dq.push_back({a[i], i});
		sg.add(1, 1, n, 1, i, -1);
		ans += sg.ask(1, 1, n, 1, i);
		//printf("lst = %d, ans = %lld\n", lst, ans);
		//for (pair<int, int> j : dq) printf("(%d, %d)\n", j.F, j.S);
		//printf("\n");
	}
	printf("%lld\n", ans);
} 
