#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(3E2 + 10), kInf = int(1E6 + 10);
constexpr double kEps = 4E-7;
constexpr double pi = acos(-1);

int dcmp(double a, double b) {
	double diff = a - b;
	if(fabs(a - b) < kEps) return 0;
	return diff > 0 ? 1 : -1;
}

struct P {
	double x, y;
	P(): x(0), y(0) {}
	P(double a, double b) {x = a, y = b;}
	void in() {
		scanf("%lf%lf", &x, &y);
		return ;
	}
	P operator + (P b) {return P(x + b.x, y + b.y);}
	P operator - (P b) {return P(x - b.x, y - b.y);}
	P operator * (double d) {return P(x * d, y * d);}
	P operator / (double d) {return P(x / d, y / d);}
	void operator -= (P p) {
		x -= p.x;
		y -= p.y;
	}
	double operator * (P b) {return x * b.x + y * b.y;}
	double operator ^ (P b) { return x * b.y - y * b.x;}
	double abs() {return hypot(x, y);}
	P unit() {return *this / abs();}
	P spin(double o) {
		double c = cos(o), s = sin(o);
		return P(c * x - s * y, s * x + c * y);
	}
};

double Dis2(P a, P b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct L {
	P p, q;
	double a, b, c; // ax + by = c
	L() {}
	L(P p, P q): p(p), q(q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = p ^ q;
	}
	P projection(P _p) {
		return p +
			(q - p).unit() *
			((q - p) * (_p - p) / (q - p).abs());
	} 
	double dis(P _p) {
		return ((q - p) ^ (_p - p)) / (q - p).abs();
	}
};
struct C {
	P o;
	double r;
	C() {}
	C(P _o, double _r): o(_o), r(_r) {}
	void in() {
		o.in();
		scanf("%lf", &r);
		return ;
	}
};

int CC_Position(C c1, C c2) {
	double d = (c1.o - c2.o).abs();
	if(dcmp(c1.r, c2.r) == -1) swap(c1, c2);
	if(dcmp(c2.r + d, c1.r) == -1) return 0;
	if(dcmp(c2.r + d, c1.r) == 0) return 1;
	if(dcmp(c1.r + c2.r, d) == 1) return 2;
	if(dcmp(c1.r + c2.r, d) == 0) return 3;
	return 4;
}

int CL_Position(C c, L l) { // 0: 2 intersections, 1: 1 intersection, 2: no intersections
	double d = fabs(l.dis(c.o));
	return dcmp(d, c.r) + 1;
}

vector<L> PC_Tangent(C c, P p) {
	double d = (p - c.o).abs();
	if(dcmp(d, c.r) == -1) return {};
	vector<L> res;
	if(dcmp(d, c.r) == 0) {
		P i = (p - c.o).unit().spin(pi / 2.0); 
		res.push_back(L(p, p + i));
	}
	else {
		double theta = acos(c.r / d);
		P i = (p - c.o).unit(), j = i.spin(theta) * c.r, k = i.spin(-theta) * c.r; 
		res.push_back(L(p, c.o + j));
		res.push_back(L(p, c.o + k));
	}
	return res;
}
vector<L> CC_Tangent(C c1, C c2) {
	if(dcmp(c1.r, c2.r) == -1) swap(c1, c2);
	int pos = CC_Position(c1, c2);
	vector<L> res;
	if(pos > 0) {
		if(dcmp(c1.r, c2.r) == 0) {
			double r = c1.r;
			P i = (c2.o - c1.o).unit().spin(pi / 2);
			res.push_back(L(c1.o + i * r, c2.o + i * r)); 
			res.push_back(L(c1.o - i * r, c2.o - i * r)); 
		}
		else {
			double x = (c1.r * c2.o.x - c2.r * c1.o.x) / (c1.r - c2.r);
			double y = (c1.r * c2.o.y - c2.r * c1.o.y) / (c1.r - c2.r);
			P p(x, y);
			auto tmp = PC_Tangent(c1, p);
			for(auto l : tmp) res.push_back(l);
		}
	}
	if(pos > 2) {
		double x = (c1.r * c2.o.x + c2.r * c1.o.x) / (c1.r + c2.r);
		double y = (c1.r * c2.o.y + c2.r * c1.o.y) / (c1.r + c2.r);
		P p(x, y);
		auto tmp = PC_Tangent(c1, p);
		for(auto l : tmp) res.push_back(l);
	}
	return res;
} 

C circle[kN];
int n;

vector<P> CL_Intersection(C c, L l) {
	int pos = CL_Position(c, l);
	if(pos == 2) return {};
	else if(pos == 1) {
		return {l.projection(c.o)};
	}
	else {
		double d = fabs(l.dis(c.o));
		double theta = acos(d / c.r);
		P p = l.projection(c.o);
		P i = (p - c.o).unit(), j = i.spin(theta) * c.r, k = i.spin(-theta) * c.r;
		vector<P> res;
		res.push_back(c.o + j), res.push_back(c.o + k);
		return res;
	}
}
bool OnSegment(P p, P a, P b) {
	  return dcmp((a - p) ^ (b - p), 0) == 0 &&
		      dcmp((a - p) * (b - p), 0) <= 0;
}

double SC_Distance(P p, P q, C c) {
	L l(p, q);
	P r = l.projection(c.o);
	if(OnSegment(r, p, q)) return fabs(l.dis(c.o));
	else return min((c.o - p).abs(), (c.o - q).abs());
}
bool Ok(L l) {
	if(CL_Position(circle[n - 1], l) == 2) return 0;
	if(CL_Position(circle[n], l) == 2) return 0;
	auto pp = CL_Intersection(circle[n - 1], l);
	P p = pp[0];
	auto qq = CL_Intersection(circle[n], l);
	P q = qq[0];
	for(int i = 1; i <= n - 2; i++) {
		double dd = SC_Distance(p, q, circle[i]);
		if(dcmp(dd, circle[i].r) == -1) return 0;
	}
	return 1;
}
int main() {
#ifdef ONLINE_JUDGE
	freopen("garden.in", "r", stdin);
	freopen("garden.out", "w", stdout);
#endif

	scanf("%d", &n);
	n += 2;
	for (int i = 1; i <= n; i++) circle[i].in();
	vector<L> v;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			auto tmp = CC_Tangent(circle[i], circle[j]); 
			for(auto l : tmp) v.push_back(l);
		}
	}

	for(auto l : v) {
		if(Ok(l)) {
			return puts("YES"), 0;
		}
	}
	puts("NO");
	return 0;
} 
