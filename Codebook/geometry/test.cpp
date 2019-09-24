#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

bool same(double a, double b) {return dcmp(a - b) == 0;}
#define Vector P
struct P {
	double x, y;
	P(double x = 0, double y = 0): x(x), y(y) {}
	P operator + (P b) {return P(x + b.x, y + b.y);}
	P operator - (P b) {return P(x - b.x, y - b.y);}
	P operator * (double b) {return P(x * b, y * b);}
	P operator / (double b) {return P(x / b, y / b);}
	double operator * (P b) {return x * b.x + y * b.y;} // Dot
	double operator ^ (P b) {return x * b.y - y * b.x;} // Cross
	double abs() {return hypot(x, y);}
	P unit() {return *this / abs();}
	P spin(double o) {
		double c = cos(o), s = sin(o);
		return P(c * x - s * y, s * x + c * y);
	}
};

struct Line {
	//ax + by + c = 0
	double a, b, c, theta;
	P pa, pb;
	Line(): a(0), b(0), c(0), theta(0), pa(), pb() {}
	Line(P pa, P pb): a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), theta(atan2(-a, b)), pa(pa), pb(pb) {}
	P projection(P p) {return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs());}
	P reflection(P p) {return p + (projection(p) - p) * 2;}
	double get_ratio(P p) {return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs());}
	P dis(P p) {return ((pb - pa) ^ (p - pa)) / (pb - pa).abs();} // directed distance
};
bool onsegment(P p, P a, P b) {
	return dcmp((a - p) ^ (b - p)) == 0 && dcmp((a - p) * (b - p)) <= 0;
}

struct Circle {
	P c;
	double r;
	Circle(P c, double r = 0): c(c), r(r) {}
};
int point_in_polygon(vector<P> ps, P p) {
	int cnt = 0;
	int wn = 0;
	for(int i = 0; i < (int)ps.size(); i++) {
		int ii = (i + 1) % (int)ps.size();
		if(onsegment(p, ps[i], ps[ii])) return -1;
		int k = dcmp((ps[ii] - ps[i]) ^ (p - ps[i]));
		int d1 = dcmp(ps[i].y - p.y);
		int d2 = dcmp(ps[ii].y - p.y);
		if(k > 0 && d1 <= 0 && d2 > 0) wn++;
		if(k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	if(wn != 0) return 1; // inside
	return 0; // outside
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	vector<P> ps;
	for(int i = 0; i < n; i++) {
		P p; cin >> p.x >> p.y;
		ps.push_back(p);
	}
	int q; cin >> q;
	while(q--) {
		P p; cin >> p.x >> p.y;
		int res = point_in_polygon(ps, p);
		if(res == -1) cout << 1 << '\n';
		else if(res == 1) cout << 2 << '\n';
		else cout << 0 << '\n';
	}
	return 0;
}
