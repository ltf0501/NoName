#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(2E3 + 10);
constexpr double kEps = 1E-7, kPi = acos(-1);


int dcmp(double x) {
	if (fabs(x) < kEps) return 0;
	return x < 0 ? -1 : 1;
}

int compare(double x, double y) {
	return dcmp(x - y);
}

bool same(double a, double b) {
	return dcmp(a - b) == 0;
}

struct Point {
	double x, y;
	explicit Point() {}
	explicit Point(double a, double b) {x = a; y = b;}
	Point operator + (Point b) const {return Point(x + b.x, y + b.y);}
	Point operator - (Point b) const {return Point(x - b.x, y - b.y);}
	Point operator * (double b) const {return Point(x * b, y * b);}
	Point operator / (double b) const {return Point(x / b, y / b);}
	double operator * (Point b) const {return x * b.x + y * b.y;}
	double operator ^ (Point b) const {return x * b.y - y * b.x;}
	double abs() const {return hypot(x, y);}
	Point unit() const {return *this / abs();}
	Point spin(double o) const {
		double c = cos(o), s = sin(o);
		return Point(c * x - s * y, s * x + c * y);
	}
	void in() {
		scanf("%lf%lf", &x, &y);
		return ;
	}
};

int n;
bool alive[kN];
double theta, radius;
Point pnt[kN];

double Area(Point a, Point b, Point c) {
	//printf("Area((%lf, %lf), (%lf, %lf), (%lf, %lf))\n", a.x, a.y, b.x, b.y, c.x, c.y);
	//printf("area = %lf\n", fabs((b - a) ^ (c - a)) / 2);
	return fabs((b - a) ^ (c - a)) / 2;
}

bool in(Point p, Point v, Point pp) {
	//printf("p = (%lf, %lf), pp = (%lf, %lf)\n", p.x, p.y, pp.x, pp.y);
	if (dcmp(pp.x - p.x) == 0 && dcmp(pp.y - p.y) == 0) return true;
	if (dcmp(radius - (pp - p).abs()) >= 0) {
		double angle1 = atan2(v.y, v.x) - theta / 2;
		double angle2 = angle1 + theta;
		double anglem1 = atan2(pp.y - p.y, pp.x - p.x);
		double anglem2 = atan2(pp.y - p.y, pp.x - p.x) + 2 * kPi;
		double anglem3 = atan2(pp.y - p.y, pp.x - p.x) - 2 * kPi;
		//printf("angle1 = %lf, angle2 = %lf, anglem1 = %lf\n", angle1, angle2, anglem1);
		if (compare(angle1, anglem1) <= 0 && compare(anglem1, angle2) <= 0) return true;
		if (compare(angle1, anglem2) <= 0 && compare(anglem2, angle2) <= 0) return true;
		if (compare(angle1, anglem3) <= 0 && compare(anglem3, angle2) <= 0) return true;
	}
	return false;
}

void stand(Point p, Point v) {
	for (int i = 1; i <= n; i++) if (alive[i]) {
		if(in(p, v, pnt[i])) alive[i] = false;
	}
	return ;
}

void rotate(Point p, Point v, double alpha) {
	//printf("rotate\n");
	for (int i = 1; i <= n; i++) if (alive[i]) {
		//printf("radius = %lf, dis = %lf\n", radius, (pnt[i] - p).abs());
		if (dcmp(pnt[i].x - p.x) == 0 && dcmp(pnt[i].y - p.y) == 0) alive[i] = false;
		else if (dcmp(radius - (pnt[i] - p).abs()) >= 0) {
			double angle1 = atan2(v.y, v.x) - theta / 2;
			double angle2 = angle1 + theta;
			angle1 -= alpha;
			double anglem1 = atan2(pnt[i].y - p.y, pnt[i].x - p.x);
			double anglem2 = atan2(pnt[i].y - p.y, pnt[i].x - p.x) + 2 * kPi;
			double anglem3 = atan2(pnt[i].y - p.y, pnt[i].x - p.x) - 2 * kPi;
			//printf("angle1 = %lf, angle2 = %lf, anglem1 = %lf\n", angle1, angle2, anglem1);
			if (compare(angle1, anglem1) <= 0 && compare(anglem1, angle2) <= 0) alive[i] = false;
			if (compare(angle1, anglem2) <= 0 && compare(anglem2, angle2) <= 0) alive[i] = false;
			if (compare(angle1, anglem3) <= 0 && compare(anglem3, angle2) <= 0) alive[i] = false;
		}
	}
	return ;
}

bool quad(Point a, Point b, Point c, Point d, Point p) {
	double areaA = Area(a, b, p) + Area(b, c, p) + Area(c, d, p) + Area(d, a, p);
	double areaB = Area(a, b, d) + Area(c, b, d);
	//printf("quad((%lf, %lf), (%lf, %lf),\n (%lf, %lf), (%lf, %lf), (%lf, %lf))\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, p.x, p.y);
	//printf(" = %d\n", dcmp(areaA - areaB));
	//printf("areaA = %lf, areaB = %lf\n", areaA, areaB);
	return same(areaA, areaB);
}


void walk(Point p, Point v, Point np) {
	stand(p, v);
	Point oa, ob, noa, nob, op1, op2, dir, nop1, nop2;
	oa = (p + (v * radius).spin(-theta / 2));
	ob = (p + (v * radius).spin(theta / 2));
	noa = oa + (np - p);
	nob = ob + (np - p);
	dir = (np - p).unit().spin(kPi / 2);
	op1 = (p + (dir * radius));
	op2 = (p - (dir * radius));
	nop1 = (np + (dir * radius));
	nop2 = (np - (dir * radius));

	//printf("oa = (%lf, %lf), noa = (%lf, %lf)\n", oa.x, oa.y, noa.x, noa.y);
	//printf("ob = (%lf, %lf), nob = (%lf, %lf)\n", ob.x, ob.y, nob.x, nob.y);
	for (int i = 1; i <= n; i++) if (alive[i]) {
		if (quad(p, oa, noa, np, pnt[i])) alive[i] = false;
		if (quad(p, ob, nob, np, pnt[i])) alive[i] = false;
	}

	if (in(p, v, op1)) {
		//printf("go(op1 = (%lf, %lf))\n", op1.x, op1.y);
		//printf("nop1 = (%lf, %lf)\n", nop1.x, nop1.y);
		for (int i = 1; i <= n; i++) if (alive[i]) {
			if (quad(p, op1, nop1, np, pnt[i])) alive[i] = false;
		}
	}
	if (in(p, v, op2)) {
		//printf("go(op2 = (%lf, %lf))\n", op2.x, op2.y);
		//printf("nop2 = (%lf, %lf)\n", nop2.x, nop2.y);
		for (int i = 1; i <= n; i++) if (alive[i]) {
			if (quad(p, op2, nop2, np, pnt[i])) alive[i] = false;
		}
	}

	stand(np, v);
	return ;
}


void solve(bool sol, bool debug) {
	int m, k;
	double t, alpha, lst = 0;
	Point p, v, d;
	scanf("%d%d%lf%lf", &n, &m, &theta, &radius);
	p.in();
	v.in();
	d.in();
	if (debug) {
		//printf("%d %d %lf %lf\n", n, m, theta, radius);
		//printf("%lf %lf %lf %lf %lf %lf\n", p.x, p.y, v.x, v.y, d.x, d.y);
	}
	v = v.unit();
	d = d.unit();
	theta = theta / 180 * kPi;
	for (int i = 1; i <= n; i++) pnt[i].in();
	if (debug) {
		//for (int i = 1; i <= n; i++) printf("%lf %lf\n", pnt[i].x, pnt[i].y);
	}
	for (int i = 1; i <= n; i++) alive[i] = true;

	stand(p, v);
	for (int i = 1; i <= m; i++) {
		scanf("%d%lf%lf", &k, &t, &alpha);
		if (debug) {
			printf("k = %d, t = %lf, alpha = %lf\n", k, t, alpha);
		}
		if (dcmp(t - lst) == 1) {
			walk(p, v, p + (d * (t - lst)));
			p = p + (d * (t - lst));
		}
		if (debug) {
			printf("p = (%lf, %lf), v = (%lf, %lf), d = (%lf, %lf)\n", p.x, p.y, v.x, v.y, d.x, d.y);
			for (int i = 1; i <= n; i++) printf("%d", alive[i] ? 1 : 0);
			printf("\n");
		}
		lst = t;
		if (k == 1) {
			rotate(p, v, alpha / 180 * kPi);
			v = v.spin(-alpha / 180 * kPi);
		}
		else d = d.spin(-alpha / 180 * kPi);

		if (debug) {
			printf("p = (%lf, %lf), v = (%lf, %lf), d = (%lf, %lf)\n", p.x, p.y, v.x, v.y, d.x, d.y);
			for (int i = 1; i <= n; i++) printf("%d", alive[i] ? 1 : 0);
			printf("\n");
		}
	}

	if (sol) {
		for (int i = 1; i <= n; i++) printf("%d", alive[i] ? 1 : 0);
		printf("\n");
	}
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		if (true) printf("Case #%d: ", i);
		solve(true, false);
	}
} 
