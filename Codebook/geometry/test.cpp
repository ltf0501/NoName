#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
const int maxn = 1e5 + 10;
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
	double a, b, c, o;
	P pa, pb;
	Line(): a(0), b(0), c(0), o(0), pa(), pb() {}
	Line(P pa, P pb): a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), o(atan2(-a, b)), pa(pa), pb(pb) {}    
	P projection(P p) {return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs());}
	P reflection(P p) {return p + (projection(p) - p) * 2;}
	double get_ratio(P p) {return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs());}
	P dis(P p) {return ((pb - pa) ^ (p - pa)) / (pb - pa).abs();} // directed distance
};
bool is_parallel(Line l, Line r) {return same(l.a * r.b, l.b * r.a);}
P line_intersection(Line l, Line r) { // check l and r are not parallel first
	return P(l.b * r.c - l.c * r.b, l.c * r.a - l.a * r.c) / (l.a * r.b - l.b * r.a);
}
struct Circle {
	P c;
	double r;
	Circle(P c, double r = 0): c(c), r(r) {}
};
double dis(P a, P b) {return (a - b).abs();}
vector<P> ps;
bool is[maxn];
vector<P> convexhull(vector<P> ps) {
	vector<P> p;
	for(int i = 0; i < (int)ps.size(); i++) {
		while(p.size() >= 2) {
			double tmp = (ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2]);
			if(dcmp(tmp) == -1) break;
			p.pop_back();
			is[p.size() - 1] = 0;
			if(dcmp(tmp) == 0) {
				is[p.size() - 1] = 1;
				break;
			}
		}
		p.push_back(ps[i]);
	}
	int t = (int)p.size();
	for(int i = (int)ps.size() - 2; i >= 0; i--) {
		while(p.size() > t) {
			double tmp = (ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2]);
			if(dcmp(tmp) == -1) break;
			p.pop_back();
			is[p.size() - 1] = 0;
			if(dcmp(tmp) == 0) {
				is[p.size() - 1] = 1;
				break;
			}
		}
		p.push_back(ps[i]);
	}
	p.pop_back();
	return p;
}
bool ok1[maxn], ok2[maxn];
bool check(vector<P> ps) {
	vector<int> p;
	for(int i = 0; i < (int)ps.size(); i++) {
		while(p.size() >= 2) {
			double tmp = (ps[i] - ps[p[p.size() - 2]]) ^ (ps[p[p.size() - 1]] - ps[p[p.size() - 2]]);
			if(dcmp(tmp) <= 0) break;
			ok1[p.back()] = 0;
			p.pop_back();
		}
		p.push_back(i);
		ok1[i] = 1;
	}
	int t = (int)p.size();
	for(int i = (int)ps.size() - 2; i >= 0; i--) {
		while(p.size() > t) {
			double tmp = (ps[i] - ps[p[p.size() - 2]]) ^ (ps[p[p.size() - 1]] - ps[p[p.size() - 2]]);
			if(dcmp(tmp) <= 0) break;
			ok2[p.back()] = 0;
			p.pop_back();
		}
		p.push_back(i);
		ok2[i] = 1;
	}
	/*
	for(int i : p) cout << i << ' ' ; cout << '\n';
	for(int i = 0; i < ps.size(); i++) cout << ok1[i] << ' '; cout << '\n';
	for(int i = 0; i < ps.size(); i++) cout << ok2[i] << ' '; cout << '\n';
	*/
	for(int i = 0; i < ps.size(); i++)
		if(!(ok1[i] || ok2[i])) return 0;
	return 1;

}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n;
	while(cin >> n && n) {
		ps.clear();
		for(int i = 0; i < n; i++) {
			P p; cin >> p.x >> p.y;
			ps.push_back(p);
		}
		sort(ps.begin(), ps.end(), [&](P a, P b){return dcmp(a.x - b.x) == 0 ? a.y < b.y : a.x < b.x;});
		memset(is, 0, sizeof(is));
		memset(ok1, 0, sizeof(ok1));
		memset(ok2, 0, sizeof(ok2));
		vector<P> cvx = convexhull(ps);
		//for(P p : cvx) cout << p.x << ' ' << p.y << '\n';
		//for(int i = 0; i < cvx.size(); i++) cout << "is[" << i << "] = " << is[i] << '\n';
		bool flag = 1;
		bool tmp = check(ps);
		//cout << "tmp = " << tmp << '\n';
		if(!tmp) {cout << "NO\n"; continue;}
		if(cvx.size() > 6) flag = 0;
		else if(cvx.size() == 6) {
			for(int i = 0; i < 6; i++) 
				if(is[i] && is[(i + 1) % 6]) {flag = 0; break;}
		} 
		else if(cvx.size() == 5) {
			for(int i = 0; i < 5; i++) 
				if(is[i] && is[(i + 1) % 5] && is[(i + 2) % 5]) {flag = 0; break;}
		}
		else if(cvx.size() == 4) {
			int cnt = 0;
			for(int i = 0; i < 4; i++) 
				cnt += is[i];
			if(cnt <= 1) flag = 1;
			else if(cnt == 2) {
				int i = -1;
				for(i = 0; i < 4; i++) 
					if(is[i]) break;
				int j = -1;
				for(j = 0; j < 4; j++)
					if(j != i && is[j]) break;
				Line a = Line(cvx[i], cvx[(i + 1) % 4]);
				Line b = Line(cvx[j], cvx[(j + 1) % 4]);
				if(is_parallel(a, b)) flag = 0;
			}
			else if(cnt == 3) {
				int i = -1;
				for(i = 0; i < 4; i++)
					if(!is[i]) break;
				Vector a = cvx[(i + 2) % 4] - cvx[(i + 1) % 4];
				Vector c = cvx[(i + 4) % 4] - cvx[(i + 3) % 4];
				double tmp = c ^ a;
				if(dcmp(tmp) <= 0) flag = 0;
			}
			else flag = 0;
		}
		else flag = 1;
		cout << (flag ? "YES\n" : "NO\n");
	}
	return 0;
}
