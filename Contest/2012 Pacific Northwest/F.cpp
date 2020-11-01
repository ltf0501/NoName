#include <bits/stdc++.h>
#include <fenv.h>
using namespace std;
const double kEps = 1e-9;
const double kInf = 1e9;
const double kPi = 4 * atan(1);

int dcmp(double x) {
	if(fabs(x) < kEps) return 0;
	return x > 0 ? 1 : -1;
}
bool same(double a, double b) {
	return dcmp(a - b) == 0;
}

struct P {
	double x, y, val;
	bool type;
	explicit P(double x, double y, double val = 0, bool type = 0) : x(x), y(y), val(val), type(type) {}
	P operator + (P b) const {return P(x + b.x, y + b.y);}
	P operator - (P b) const {return P(x - b.x, y - b.y);}
	P operator * (double b) const {return P(x * b, y * b);}
	P operator / (double b) const {return P(x / b, y / b);}
	double operator * (P b) const {return x * b.x + y * b.y;}
	double operator ^ (P b) const {return x * b.y - y * b.x;}

	double abs() const {return hypot(x, y);}
	P unit() const {return *this / abs();}
	P rotate() const {return P(-y, x, this->val, this->type);}
};
double Getdis(P vv, P vec) {
	if(dcmp(vv.x) == 0) return vv.y / vec.y;
	return vv.x / vec.x;
}

struct C {
	P c;
	double r;
	C(P c, double r) : c(c), r(r) {}
};

C GetCircle(P a, P b, P c) {
	double a1, a2, b1, b2, c1, c2;
	//printf("a = (%f, %f), b = (%f, %f), c = (%f, %f)\n", a.x ,a.y, b.x, b.y, c.x, c.y);
	C res(P(0, 0), 0);
	a1 = 2 * (a.x - b.x);
	a2 = 2 * (a.x - c.x);
	b1 = 2 * (a.y - b.y);
	b2 = 2 * (a.y - c.y);
	c1 = a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y;
	c2 = a.x * a.x - c.x * c.x + a.y * a.y - c.y * c.y;

	res.c.x = (P(c1, b1) ^ P(c2, b2)) / (P(a1, b1) ^ P(a2, b2));
	res.c.y = (P(a1, c1) ^ P(a2, c2)) / (P(a1, b1) ^ P(a2, b2));
	res.r = (res.c - a).abs();
	//printf("c = (r = %f\n", res.r);
	return res;
}

bool onsegment(P p, P a, P b) {
	return dcmp((a - p) ^ (b - p)) == 0 && dcmp((a - p) * (b - p)) <= 0;
}

vector<P> Parse(string s, bool type) {
	vector<P> res;
	stringstream ss(s);
	string tmp;
	ss >> tmp;
	while(ss >> tmp) {
		if(tmp == "none") break;
		int x[2];   
		int num = 0, id = 0;
		for(char c : tmp) {
			if(c == '(') continue;
			else if(c == ',') {
				x[id] = num, num = 0, id++;
			}
			else if(c == ')') {
				x[id] = num;
			}
			else {
				num = 10 * num + (c - '0');
			}
		}

		res.push_back(P(x[0], x[1], 0, type));
	}
	return res;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	string s, t;
	while(getline(cin, s)) {
		getline(cin, t);
		vector<P> ps[2];
		ps[0] = Parse(s, 0), ps[1] = Parse(t, 1);
		int sz = int(ps[0].size());
		if(sz == 0 || sz == 1) {
			cout << 0 << '\n';
			continue;
		}

		double ans = kInf;
		for(int i = 0; i < int(ps[0].size()); i++) {
			for(int j = i + 1; j < int(ps[0].size()); j++) {
				P o = (ps[0][i] + ps[0][j]) / 2.0;
				C cc(o, (ps[0][i] - o).abs());
				vector<P> v[2];

				bool bye = 0;
				bool flag = 1;
				for(int k = 0; k < int(ps[0].size()); k++) if(k != i && k != j) {
					if(dcmp((ps[0][k] - o).abs() - cc.r) > 0) flag = 0;
					int type = dcmp((ps[0][j] - ps[0][i]) ^ (ps[0][k] - ps[0][i]));
					if(type == -1) v[0].push_back(ps[0][k]);
					else if(type == 1) v[1].push_back(ps[0][k]);
					else {
						if(!onsegment(ps[0][k], ps[0][i], ps[0][j])) {
							bye = 1;
							break;
						} 
					} 
				}

				for(auto p : ps[1]) {
					if(dcmp((p - o).abs() - cc.r) <= 0) flag =0;
					int type = dcmp((ps[0][j] - ps[0][i]) ^ (p - ps[0][i]));
					if(type == -1) v[0].push_back(p);
					else if(type == 1) v[1].push_back(p);
					else {
						if(onsegment(p, ps[0][i], ps[0][j])) {
							bye = 1;
							break;
						}
					}
				}
				if(flag) ans = min(ans, cc.r); 
				if(bye) continue; 
				
				for(P &p : v[0]) {
					p.val = ((p - ps[0][i]).unit()) * ((p - ps[0][j]).unit());
				}
				for(P &p : v[1]) {
					p.val = ((p - ps[0][i]).unit()) * ((p - ps[0][j]).unit());
				}
				//sort(v[0].begin(), v[0].end(), [&](P a, P b) { 
				//		int tmp = dcmp(a.val - b.val);
				//		if(tmp != 0) return tmp < 0;
				//		return a.type < b.type;
				//		});
				//sort(v[1].begin(), v[1].end(), [&](P a, P b) {
				//		int tmp = dcmp(a.val - b.val);
				//		if(tmp != 0) return tmp < 0;
				//		return a.type < b.type;
				//		});

				double lft[2], rht[2];
				lft[0] = lft[1] = -kInf, rht[0] = rht[1] = kInf;
				
				P vec = (ps[0][i] - o).rotate();

				for(P &p : v[0]) {
					C circle = GetCircle(ps[0][i], ps[0][j], p);
					double val = Getdis(circle.c - o, vec);

					if(p.type == 0) lft[0] = max(lft[0], val);
					else rht[1] = min(rht[1], val);
				}
				for(P &p : v[1]) {
					C circle = GetCircle(ps[0][i], ps[0][j], p);
					double val = Getdis(circle.c - o, vec);

					if(p.type == 0) rht[0] = min(rht[0], val);
					else lft[1] = max(lft[1], val);
				}

				if(dcmp(lft[0] - rht[0]) > 0 || dcmp(lft[1] - rht[1]) >= 0) continue; 
				if(dcmp(rht[0] - lft[1]) <= 0 || dcmp(rht[1] - lft[0]) <= 0) continue;

				double L = max(lft[0], lft[1]), R = min(rht[0], rht[1]);

				double result = min(fabs(L), fabs(R));
				P center = o + (vec * result);
				ans = min(ans, (center - ps[0][i]).abs());
			} 
		}

		if(same(ans, kInf)) cout << "The Orcs are close\n";
		else cout << fixed << setprecision(9) << ans << '\n'; 
	} 
	return 0;
} 
