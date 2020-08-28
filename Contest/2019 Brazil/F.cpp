#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(1E5 + 10);
 
struct seg_tree {
	int val[kN << 2], flag[kN << 2], low[kN << 2]; 
	void addtag(int n, int x) {
		flag[n] += x;
		val[n] += x;
		return ;
	}
	void pull(int n) {
		if (val[n << 1] == val[n << 1 | 1]) {
			low[n] = low[n << 1] + low[n << 1 | 1];
			val[n] = val[n << 1]; 
		}
		else if (val[n << 1] < val[n << 1 | 1]) {
			val[n] = val[n << 1];
			low[n] = low[n << 1];
		}
		else {
			val[n] = val[n << 1 | 1];
			low[n] = low[n << 1 | 1];
		}
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
		val[n] = flag[n] = 0;
		low[n] = r - l + 1; 
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) addtag(n, x);
		else if (!(L > r || l > R)) {
			int mid = (l + r) >> 1;
			push(n);
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
	}
	int query(int n, int l, int r, int pos) {
		if (l == r) return val[n];
		else {
			int mid = (l + r) >> 1;
			push(n);
			if (pos <= mid) return query(n << 1, l, mid, pos);
			else return query(n << 1 | 1, mid + 1, r, pos);
		}
	}
};
 
seg_tree sg;
int x1[kN], y1[kN], x2[kN], y2[kN], X1, Y1, X2, Y2;
 
ll go(int x, int n) {
	vector<tuple<int, int, int, int>> v;
	int pos = 0, sz = n << 1;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		v.PB({x1[i] - x, -1, max(Y1, y1[i] - x), min(Y2, y2[i] + x)});
		v.PB({x2[i] + x + 1, 1, max(Y1, y1[i] - x), min(Y2, y2[i] + x)});
	}
	sort(v.begin(), v.end());
	sg.init(1, 1, kN);
	if (Y1 > 1) sg.add(1, 1, kN, 1, Y1 - 1, 1);
	sg.add(1, 1, kN, Y2 + 1, kN, 1);
	for (int i = X1; i <= X2; i++) {
		while (pos < sz) {
			if (get<0>(v[pos]) <= i) {
				sg.add(1, 1, kN, get<2>(v[pos]), get<3>(v[pos]), -get<1>(v[pos]));
				pos++;
			}
			else break;
		}
		if (sg.val[1] == 0) ans += sg.low[1];
	}
//	for (tuple<int, int, int, int> i : v) printf("(%d, %d, %d, %d)\n", get<0>(i), get<1>(i), get<2>(i), get<3>(i));
//	printf("x = %d, ans = %lld\n", x, 400 - ans);
	return ans;
}
int main() {
	int n, l, r, mid;
	ll need, p;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
	scanf("%lld%d%d%d%d", &p, &X1, &Y1, &X2, &Y2);
	for (int i = 1; i <= n; i++) {
		if (x1[i] > x2[i]) swap(x1[i], x2[i]);
		if (y1[i] > y2[i]) swap(y1[i], y2[i]);
	}
	for (int i = 1; i <= n; i++) x1[i]++, y1[i]++;
	X1++, Y1++;
	l = 0, r = kN;
	need = (100 - p) * (X2 - X1 + 1) * (Y2 - Y1 + 1);
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (go(mid, n) * 100 <= need) r = mid; 
		else l = mid;
	}
	
	printf("%d\n", r); //brute(n, p));
} 
