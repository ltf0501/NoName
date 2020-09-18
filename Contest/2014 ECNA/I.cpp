#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back

constexpr double kEps = 1E-8;
const double kPi = 4 * atan(1);

constexpr int kN = int(3E2 + 10), kInf = int(1E9 + 10);

struct Edge {
	int to, rev, cap;
};

vector<Edge> graph[kN];
int iter[kN], dep[kN], went[kN];

void AddEdge(int u, int v, int c) {
	graph[u].PB({v, int(graph[v].size()), c});
	graph[v].PB({u, int(graph[u].size() - 1), 0});
	return ;
}

void Bfs(int s, int t) {
	int nxt;
	queue<int> q;
	q.push(s);
	iter[s] = dep[s] = 0;
	went[s] = t;
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		for (Edge i : graph[nxt]) if (i.cap > 0 && went[i.to] != t) {
			went[i.to] = t;
			q.push(i.to);
			dep[i.to] = dep[nxt] + 1;
			iter[i.to] = 0;
		}
	}
	return ;
}

int Dfs(int u, int t, int nv) {
	if (u == t) return nv;
	int tmp;
	for (int &i = iter[u]; i < int(graph[u].size()); i++) {
		Edge& nxt = graph[u][i];
		if (nxt.cap > 0 && dep[nxt.to] > dep[u]) {
			tmp = Dfs(nxt.to, t, min(nxt.cap, nv));
			if (tmp > 0) {
				nxt.cap -= tmp;
				graph[nxt.to][nxt.rev].cap += tmp;
				return tmp;
			}
		}
	}
	return 0;
}

int Dinic(int s, int t) {
	int cnt = 0, ans = 0, f;
	for (int i = 0; i < kN; i++) went[i] = 0;
	while (true) {
		Bfs(s, ++cnt);
		if (went[s] != went[t]) break;
		while ((f = Dfs(s, t, kInf)) > 0) ans += f;
	}
	return ans;
}

int dcmp(double x) {
	if (fabs(x) < kEps) return 0;
	return x < 0 ? -1 : 1;
}

struct Point {
	double x, y;
	Point (double x = 0, double y = 0) : x(x), y(y) {}
	Point operator + (Point b) const {
		return Point(x + b.x, y + b.y);
	}
	Point operator - (Point b) const {
		return Point(x - b.x, y - b.y);
	}
	Point operator / (double b) const {
		return Point(x / b, y / b);
	}
	Point operator * (double b) const {
		return Point(x * b, y * b);
	}
	double operator * (Point b) const {
		return x * b.x + y * b.y;
	}
	double operator ^ (Point b) const {
		return x * b.y - y * b.x;
	}
	double abs() const {return hypot(x, y);}
	Point unit() const {return *this / abs();}
	Point spin(double o) const {
		double c = cos(o), s = sin(o);
		return Point(c * x - s * y, s * x + c * y);
	}
};

struct Line {
	double a, b, c; // ax + by = c
	Point pa, pb;
	Line() : a(0), b(0), c(0), pa(), pb() {}
	Line(Point pa, Point pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
	Point projection(Point p) {
		return pa + (pb - pa).unit() * ((pb - pa).unit() * (p - pa));
	}
	double dis(Point p) {
		return (pb - pa).unit() ^ (p - pa);
	}
};

struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(Point c, double r = 0) : c(c), r(r) {}
};

bool onsegment(Point p, Point a, Point b) {
	return dcmp((a - p) ^ (b - p)) == 0 &&
				 dcmp((a - p) * (b - p)) <= 0;
}

bool segment_intersection(Point p1, Point p2, Point p3, Point p4) {
	return dcmp((p2 - p1) ^ (p3 - p1)) * dcmp((p2 - p1) ^ (p4 - p1)) < 0 &&
				 dcmp((p4 - p3) ^ (p1 - p3)) * dcmp((p4 - p3) ^ (p2 - p3)) < 0;
}

int CL_Position(Circle c, Line l) {
	double d = fabs(l.dis(c.c));
	return dcmp(d - c.r) + 1;
}

Point line_intersection(Line l1, Line l2) {
	return Point(-l1.b * l2.c + l1.c * l2.b, l1.a * l2.c - l1.c * l2.a) / (-l1.a * l2.b + l1.b * l2.a);
}

vector<Point> CL_Intersection(Circle c, Line l) {
	int pos = CL_Position(c, l);
	if (pos == 2) return {};
	else if (pos == 1) return {l.projection(c.c)};
	else {
		double d = fabs(l.dis(c.c));
		vector<Point> res;
		if(dcmp(d) == 0) { // vector = (l.b, -l.a)
			Point j = Point(l.b, -l.a).unit();
			res.push_back(c.c + j * c.r), res.push_back(c.c - j * c.r);
		}
		else {
			double theta = acos(d / c.r);
			Point p = l.projection(c.c);
			Point i = (p - c.c).unit();
			Point j = i.spin(theta) * c.r, k = i.spin(-theta) * c.r;
			res.PB(c.c + j), res.PB(c.c + k);
		}
		return res;
	}
}

vector<pair<Point, Point>> segment;
vector<tuple<Point, Point, Point, Point>> arch; // center, a, b, p
Point pa[kN], pg[kN], vp[kN], d[kN];
int va[kN], vg[kN];
bool connect[kN];

bool check_segment(Point a, Point b) {
	vector<Point> v;
	for (pair<Point, Point> i : segment) if (segment_intersection(a, b, i.F, i.S)) return false;
	for (tuple<Point, Point, Point, Point> i : arch) {
		Circle c = Circle(get<0>(i), (get<1>(i) - get<0>(i)).abs());
		Line l = Line(a, b);
		v = CL_Intersection(c, l);
		for (Point j : v) {
			if (onsegment(j, a, b) &&
					dcmp((get<2>(i) - get<1>(i)) ^ get<3>(i)) == 
					dcmp((get<2>(i) - get<1>(i)) ^ (j - get<1>(i)))) return false;
		}
	}
	return true;
}


void solve(int n, int a, int g) {
	int sz, S = 0, T = a + g + 1, tot = 0;
	bool f;
	Point np, mid_point, nm_point;
	string s;
	segment.clear();
	arch.clear();
	for (int i = 1; i <= n; i++) {
		cin >> sz;
		for (int j = 1; j <= sz; j++) {
			cin >> vp[j].x >> vp[j].y >> s;
			if (s[0] == 'c') {
				connect[j] = true;
				cin >> d[j].x >> d[j].y;
			}
			else connect[j] = false;
		}
		vp[sz + 1] = vp[1];
		for (int j = 1; j <= sz; j++) {
			if (connect[j]) {
				mid_point = (vp[j] + vp[j + 1]) / 2;
				nm_point = mid_point + Point(vp[j + 1].y - vp[j].y, vp[j].x - vp[j + 1].x);
				np = Point(vp[j].x + d[j].y, vp[j].y - d[j].x);
				arch.PB({line_intersection(Line(mid_point, nm_point), Line(vp[j], np)), vp[j], vp[j + 1], d[j]});
			}
			else segment.PB({vp[j], vp[j + 1]});
		}
	}
	for (int i = 1; i <= a; i++) cin >> pa[i].x >> pa[i].y >> va[i];
	for (int i = 1; i <= g; i++) cin >> pg[i].x >> pg[i].y >> vg[i];
	for (int i = S; i <= T; i++) graph[i].clear();
	for (int i = 1; i <= a; i++) AddEdge(g + i, T, va[i]);
	for (int i = 1; i <= g; i++) AddEdge(S, i, vg[i]);
	for (int i = 1; i <= a; i++) for (int j = 1; j <= g; j++) {
		if (check_segment(pa[i], pg[j])) AddEdge(j, i + g, 1);
	}
	for (int i = 1; i <= a; i++) tot += va[i];
	if (Dinic(S, T) != tot) cout << "No\n";
	else cout << "Yes\n";
	return ;
}

int main() {
	int n, a, g, idx = 1;
	while (true) {
		cin >> n >> a >> g;
		if (n == 0 && a == 0 && g == 0) break;
		cout << "Case " << idx++ << ": ";
		solve(n, a, g);
	}
} 
