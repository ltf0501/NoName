#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define PB push_back
constexpr int kN = int(5E2 + 10);
constexpr double kEps = 1E-9, kInf = 1E16;

int dcmp(double x) {
	if (fabs(x) < kEps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
	Point () {}
	Point (double xx, double yy) {x = xx, y = yy;}
	Point operator - (Point b) const {return Point(x - b.x, y - b.y);}
	double operator * (Point b) const {return x * b.x + y * b.y;}
	double operator ^ (Point b) const {return x * b.y - y * b.x;}
};

int x[kN], y[kN], X1[kN], Y1[kN], X2[kN], Y2[kN], cnt[kN];


bool onsegment(Point p, Point a, Point b) {
	return dcmp((a - p) ^ (b - p)) == 0 && dcmp((a - p) * (b - p)) <= 0;
}

pair<double, double> pr(int a, int b) {
	if (onsegment(Point(x[a], y[a]), Point(X1[b], Y1[b]), Point(X2[b], Y2[b]))) return {-kInf, kInf};
	if (y[a] <= Y1[b] && y[a] <= Y2[b]) return {-kInf, -kInf};
	double dx, dy, l, r, xpos;
	if (y[a] <= Y1[b]) {
		dx = X1[b] - X2[b], dy = Y1[b] - Y2[b];
		xpos = X2[b] + dx / dy * (y[a] - Y2[b]);
		if (xpos < x[a]) {
			dx = x[a] - X2[b], dy = y[a] - Y2[b]; 
			return {-kInf, x[a] - y[a] / dy * dx};
		}
		else {
			dx = x[a] - X2[b], dy = y[a] - Y2[b]; 
			return {x[a] - y[a] / dy * dx, kInf};
		}
	}
	if (y[a] <= Y2[b]) {
		dx = X1[b] - X2[b], dy = Y1[b] - Y2[b];
		xpos = X1[b] + dx / dy * (y[a] - Y1[b]);
		if (xpos < x[a]) {
			dx = x[a] - X1[b], dy = y[a] - Y1[b]; 
			return {-kInf, x[a] - y[a] / dy * dx};
		}
		else {
			dx = x[a] - X1[b], dy = y[a] - Y1[b]; 
			return {x[a] - y[a] / dy * dx, kInf};
		}
	
	}

	dx = x[a] - X1[b], dy = y[a] - Y1[b];
	l = x[a] - y[a] / dy * dx;
	
	dx = x[a] - X2[b], dy = y[a] - Y2[b];
	r = x[a] - y[a] / dy * dx;

	return {min(l, r), max(l, r)};
}

void solve() {
	int n, m, now = 0;
	double ans = 0, lst = -kInf;
	pair<double, double> tmp;
	vector<pair<double, int>> tp; // time, do
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
	for (int i = 1; i <= n; i++) cnt[i] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			tmp = pr(i, j);
			tp.PB({tmp.F, i});
			tp.PB({tmp.S, -i});
		}
	}
	sort(tp.begin(), tp.end());
	for (pair<double, int> i : tp) {
		if (now == n) ans += i.F - lst;
		lst = i.F;
		if (i.S > 0) {
			if (cnt[i.S] == 0) now++;
			cnt[i.S]++;
		}
		else {
			if (cnt[-i.S] == 1) now--;
			cnt[-i.S]--;
		}
	}
	if (ans > 1E9) printf("-1\n");
	else printf("%.20lf\n", ans);
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
