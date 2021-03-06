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

