#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = int(2E3 + 10);
constexpr double kPi = acos(-1);
struct Point {
	double x, y;
	Point() {}
	Point (double xx, double yy) {x = xx, y = yy;}
	Point operator + (Point b) const {return Point(x + b.x, y + b.y);}
	Point operator - (Point b) const {return Point(x - b.x, y - b.y);}
	Point operator * (double b) const {return Point(x * b, y * b);}
	Point operator / (double b) const {return Point(x / b, y / b);}
	Point spin(double o) const {
		double c = cos(o), s = sin(o);
		return Point(c * x - s * y, s * x + c * y);
	}
	void out() {
		printf("%.20lf %.20lf\n", x, y);
		return ;
	}
};


Point p[kN];
int sz[kN];
vector<int> graph[kN];

void dfs(int pos, int from, Point dir) {
	p[pos] = p[from] + dir;
	sz[pos] = 1;
	for (int i : graph[pos]) if (i != from) {
		dfs(i, pos, dir);
		dir = dir.spin(sz[i] * kPi / kN);
		sz[pos] += sz[i];
	}
	return ;
}

int main() {
	int n, l, r;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	//n = 1000;
	//for (int i = 2; i <= n; i++) {
	//	graph[1].PB(i); 
	//	graph[i].PB(1);
	//}
	p[1] = Point(0, -1);
	dfs(1, 1, Point(0, 1));
	for (int i = 1; i <= n; i++) p[i].out();
} 
