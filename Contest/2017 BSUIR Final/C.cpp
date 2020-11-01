#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
const double kEps = 1e-9;
const double kPi = 4 * atan(1);
constexpr int kN = int(1E5 + 10);
constexpr double kInf = 1E16;
int dcmp(double x) {
	if(fabs(x) < kEps) return 0;
	return x > 0 ? 1 : -1;
}
bool same(double a, double b) {
	return dcmp(a - b) == 0;
}
struct P {
	double x, y;
	P() {}
	P(double x, double y) : x(x), y(y) {}
	P operator + (P b) const {return P(x + b.x, y + b.y);}
	P operator - (P b) const {return P(x - b.x, y - b.y);}
	P operator * (double b) const {return P(x * b, y * b);}
	P operator / (double b) const {return P(x / b, y / b);}
	double operator * (P b) const {
		return x * b.x + y * b.y;
	}
	double operator ^ (P b) const {
		return x * b.y - y * b.x;
	}
};

vector<P> ConvexHull(vector<P> &ps) {
	vector<P> p;
	for(int i = 0; i < int(ps.size()); i++) {
		while(p.size() >= 2 && 
				((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0) 
			p.pop_back();
		p.push_back(ps[i]);
	}
	int t = int(p.size());
	for(int i = int(ps.size()) - 2; i >= 0; i--) {
		while(int(p.size()) > t && 
				((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0)
			p.pop_back();
		p.push_back(ps[i]);
	}
	p.pop_back();
	return p;
}

double Area(vector<P> p) {
	double res = 0;
	for(int i = 1; i < int(p.size()) - 1; i++) {
		res += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
	}
	return fabs(res * 0.5);
}

P p[kN];
pair<int, int> point[kN];

void update(double &ans, double tans, int x) {
	if (dcmp(fabs(ans - x) - fabs(tans - x)) == 0) {
		if (dcmp(ans - tans) == -1) ans = tans;
	}
	else if (fabs(ans - x) > fabs(tans - x)) ans = tans;
	return ;
}

int main() {
	int n, s, l, r, mid, sz, ts;
	double ans = kInf, tans;
	vector<int> v;
	vector<P> L, R;
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%d%d", &point[i].F, &point[i].S);
	sort(point + 1, point + n + 1);
	for (int i = 1; i <= n; i++) v.PB(point[i].F);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	sz = int(v.size());
	for (int i = 1; i <= n; i++) p[i] = P(point[i].F, point[i].S);
	ts = s;
	for (int o = 0; o < 2; o++) {
		l = 0, r = sz - 1;
		while (r - l > 1) {
			mid = (l + r) >> 1;
			L.clear();
			R.clear();
			for (int i = 1; i <= n; i++) if (point[i].F <= v[mid]) L.PB(p[i]);
			else R.PB(p[i]);
			tans = Area(ConvexHull(L)) - Area(ConvexHull(R));
			update(ans, fabs(tans), s);
			if (tans > ts) r = mid;
			else l = mid;
		}
		L.clear();
		R.clear();
		for (int i = 1; i <= n; i++) if (point[i].F <= v[l]) L.PB(p[i]);
		else R.PB(p[i]);
		tans = Area(ConvexHull(L)) - Area(ConvexHull(R));
		update(ans, fabs(tans), s);
		L.clear();
		R.clear();
		for (int i = 1; i <= n; i++) if (point[i].F <= v[r]) L.PB(p[i]);
		else R.PB(p[i]);
		tans = Area(ConvexHull(L)) - Area(ConvexHull(R));
		update(ans, fabs(tans), s);
		ts = -ts;
	}
	printf("%.20lf\n", ans);
} 
