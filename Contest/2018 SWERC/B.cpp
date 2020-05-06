#include <stdio.h>
#include <utility>
#include <deque>
using namespace std;
#define F first
#define S second
constexpr int kN = int(1E5 + 10);

struct seg_tree {
	int val[kN << 2];
	void init(int n, int l, int r) {
		val[n] = 0;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) val[n] += x;
		else if (!(L > r || l > R)) {
			int mid = (l + r) >> 1;
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
		}	
		return ;
	}
	int ask(int n, int l, int r, int pos) {
		if (l == r) return val[n];
		int mid = (l + r) >> 1;
		if (pos > mid) return ask(n << 1 | 1, mid + 1, r, pos) + val[n];
		else return ask(n << 1, l, mid, pos) + val[n];
	}
};


seg_tree sg, sg_h;
int h[kN], l[kN], r[kN];

int main() {
	int n, ans = 0, x, tmp, lhs, rhs, mid, now;
	deque<int> dq;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
	for (int i = 1; i <= n; i++) l[i]++, r[i]++;
	sg.init(1, 1, n);
	sg_h.init(1, 1, n);
	x = n;
	for (int i = 1; i <= n; i++) {
		now = 0;
		while (!dq.empty()) {
			if (dq.front() < l[i]) {
				tmp = sg.ask(1, 1, n, dq.front());
				sg.add(1, 1, n, dq.front(), l[i] - 1, -tmp);
				sg_h.add(1, 1, n, now + 1 + x, now + tmp + x, dq.front() - l[i]);
				now += tmp;
				dq.pop_front();
			}
			else break;
		}
		now = 0;
		while (!dq.empty()) {
			if (dq.back() > r[i]) {
				tmp = sg.ask(1, 1, n, dq.back());
				sg.add(1, 1, n, r[i] + 1, dq.back(), -tmp);
				sg_h.add(1, 1, n, now + 1 + x, now + x + tmp, r[i] - dq.back());
				now += tmp;
				dq.pop_back();
			}
			else break;
		}

		sg.add(1, 1, n, l[i], r[i], 1);
		x--;

		sg_h.add(1, 1, n, 1 + x, 1 + x, r[i] - l[i] + 1);

		if (!dq.empty()) {
			if (l[i] < dq.front()) dq.push_front(l[i]);
			if (dq.back() < r[i]) dq.push_back(r[i]);
		}
		else {
			dq.push_front(l[i]);
			if (dq.back() < r[i]) dq.push_back(r[i]);
		}


		
		lhs = 1, rhs = i + 1;
		while (rhs - lhs > 1) {
			mid = (lhs + rhs) >> 1;
			if (sg_h.ask(1, 1, n, mid + x) >= mid) lhs = mid;
			else rhs = mid;
		}
		ans = max(ans, lhs);

	}

	printf("%d\n", ans);
} 
