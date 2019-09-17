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

struct Circle {
	P c;
	double r;
	Circle(P c, double r = 0): c(c), r(r) {}
};
bool onsegment(P p, P a, P b) {
	return dcmp((a - p) ^ (b - p)) == 0 && dcmp((a - p) * (b - p)) <= 0;
}
bool segment_intersection(P p1, P p2, P p3, P p4) { // end points are not allowed
	return dcmp((p2 - p1) ^ (p3 - p1)) * dcmp((p2 - p1) ^ (p4 - p1)) < 0 
		&& dcmp((p4 - p3) ^ (p1 - p3)) * dcmp((p4 - p3) ^ (p2 - p3)) < 0;
	
}
bool parallel(Line l1, Line l2) {return same(l1.a * l2.b, l1.b * l2.a);}
P line_intersection(Line l1, Line l2) {
	return P(-l1.b * l2.c + l1.c * l2.b, l1.a * l2.c - l1.c * l2.a) / (-l1.a * l2.b + l1.b * l2.a);	
}
double Area(vector<P> &p) {
	double res = 0;
	for(int i = 1; i < (int)p.size() - 1; i++) 
		res += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
	return res * 0.5;
}
bool cmp(P a, P b) {return same(a.y, b.y) ? a.x < b.x : a.y < b.y;}
vector<P> convexhull(vector<P> ps) {
	vector<P> p;
	for(int i = 0; i < (int)ps.size(); i++) {
		while(p.size() >= 2 && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) > 0) p.pop_back();
		p.push_back(ps[i]);
	}
	int t = (int)p.size();
	for(int i = (int)ps.size() - 2; i >= 0; i--) {
		while(p.size() > t && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) > 0) p.pop_back();
		p.push_back(ps[i]);
	}
	p.pop_back();
	return p;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	vector<P> vec;
	for(int i = 0; i < n; i++) {
		P p; cin >> p.x >> p.y;
		vec.push_back(p);
	}
	sort(vec.begin(), vec.end(), cmp);
	vector<P> convex = convexhull(vec);	
	cout << int(convex.size()) << '\n';
	for(P p : convex) cout << int(p.x) << ' ' << int(p.y) << '\n';
	return 0;
}
