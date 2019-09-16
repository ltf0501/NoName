vector<Point> intersect(Circle a, circle b) {
	if(a.r > b.r) swap(a, b);
	double d = (a.c - b.c).abs();
	vector<Point> ps;
	if(same(a.r + b.r, d)) ps.push_back(a.c + (b.c - a.c).unit() * a.r);
	else if(a.r + b.r > d && d + a.r >= b.r) {
		double o = acos((a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d));
		Point t = (b.c - a.c).unit();
		ps.push_back(a.c + t.spin(o) * a.r);
		ps.push_back(a.c + t.spin(-o) * a.r);
	}
	return p.s;
}

double intersect_area(C a, C b) {
	if(a.r > b.r) swap(a, b);
	double d = (a.c - b.c).abs();
	if(d >= a.r + b.r - eps) return 0;
	if(d + a.r <= b.r + eps) return a.r * a.r * acos(-1);
	double p = acos((a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d));
	double q = acos((b.r * b.r + d * d - a.r * a.r) / (2.0 * b.r * d));
	return p * a.r * a.r + q * b.r * b.r - a.r * d * sin(p);
}
