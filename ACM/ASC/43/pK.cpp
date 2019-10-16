#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps = 1e-10;
const int maxn = 1e5 + 10;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
bool same(double a, double b) {return dcmp(a - b) == 0;}
#define Vector P
struct P {
	double x, y;
	P(double x = 0, double y = 0) : x(x), y(y) {}
	P operator + (P b) {return P(x + b.x, y + b.y);}
	P operator - (P b) {return P(x - b.x, y - b.y);}
	P operator * (double b) {return P(x * b, y * b);}
	P operator / (double b) {return P(x / b, y / b);}
	double operator * (P b) {return x * b.x + y * b.y;}
	double operator ^ (P b) {return x * b.y - y * b.x;}
};
struct Line {
	double a, b, c, theta;
	P pa, pb;
	Line() : a(0), b(0), c(0), theta(0), pa(), pb() {}
	Line(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), theta(atan2(-a, b)), pa(pa), pb(pb) {}
	double get_val(P p) {return a * p.x + b * p.y + c;}
};
bool segment_intersection(P p1, P p2, P p3, P p4) {
	return dcmp((p2 - p1) ^ (p3 - p1)) * dcmp((p2 - p1) ^ (p4 - p1)) < 0
			&& dcmp((p4 - p3) ^ (p1 - p3)) * dcmp((p4 - p3) ^ (p2 - p3)) < 0;
}
P a[maxn];
int main() {
	int n;
	ios_base::sync_with_stdio(false); cin.tie(0);
	freopen("kingdom.in", "r", stdin);
	freopen("kingdom.out", "w", stdout);
	while(cin >> n && n) {
		for(int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
		P s, t;
		cin >> s.x >> s.y >> t.x >> t.y;
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			int l = i + 1, r = i + n - 1;	
			while(l != r) {
				int m = (l + r) >> 1;
				Line line = Line(a[i], a[m % n]);	
				double v1 = line.get_val(s), v2 = line.get_val(t); 
				//cout << "m = " << m << " v1 = " << v1 << " v2 = " << v2 << '\n'; 
				if(dcmp(v1) >= 0 && dcmp(v2) >= 0) l = m + 1;
				else r = m;
			}
			int le = l;
			//cout << line.get_val(s) << ' ' << line.get_val(t) << '\n'; 
			l = le, r = i + n - 1;
			while(l != r) {
				int m = (l + r) >> 1;
				if(segment_intersection(s, t, a[i], a[m % n])) l = m + 1;
				else r = m;
			}
			int ri = l;
			//cout << line.get_val(s) << ' ' << line.get_val(t) << '\n'; 
			//cout << "le = " << le << " ri = " << ri << '\n';
			ans += ri - le;
		}
		cout << ans / 2 << '\n';
	}
	return 0;
}
