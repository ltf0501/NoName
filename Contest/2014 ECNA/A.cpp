#include <bits/stdc++.h>
using namespace std;
#define PB push_back

typedef long long int ll;

ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}

struct Rational {
	ll p, q;
	Rational() {p = q = 0;}
	Rational(ll a, ll b) {
		p = a, q = b;
		pull();
	}
	void rev() {swap(p, q);}
	void operator += (ll x) {
		p += q * x;
		return ;
	}
	void pull() {
		bool f = false;
		ll tmp;
		if (q < 0) {
			q = -q;
			p = -p;
		}
		if (p < 0) {
			p = -p;
			f = true;
		}
		tmp = gcd(p, q);
		p /= tmp;
		q /= tmp;
		if (f) p = -p;
		return ;
	}
	Rational operator + (Rational a) {
		return Rational(p * a.q + a.p * q, q * a.q);
	}
	Rational operator - (Rational a) {
		return Rational(p * a.q - a.p * q, q * a.q);
	}
	Rational operator * (Rational a) {
		return Rational(p * a.p, q * a.q);
	}
	Rational operator / (Rational a) {
		return Rational(p * a.q, q * a.p);
	}
};

struct Fraction {
	vector<ll> v;
	Fraction() {}
	void in(int sz) {
		v.resize(sz);
		for (int i = 0; i < sz; i++) scanf("%lld", &v[i]);
		return ;
	}
	void out() {
		int sz = int(v.size());
		printf("%lld", v[0]);
		for (int i = 1; i < sz; i++) printf(" %lld", v[i]);
		printf("\n");
		return ;
	}
	Rational rational() {
		int sz = int(v.size());
		Rational ans(v[sz - 1], 1);
		for (int i = sz - 2; i >= 0; i--) {
			ans.rev();
			ans += v[i];
		}
		return ans;
	}
};

Fraction frac(Rational a) {
	Fraction ans;
	if (a.p < 0) {
		ans.v.PB((a.p + 1) / a.q - 1);
		a.p -= ((a.p + 1) / a.q - 1) * a.q;
		a.rev();
	}
	while (a.q > 0) {
		ans.v.PB(a.p / a.q);
		a.p %= a.q;
		a.rev();
	}
	return ans;
}

void solve(int n, int m) {
	Fraction a, b;
	a.in(n);
	b.in(m);
	frac(a.rational() + b.rational()).out();
	frac(a.rational() - b.rational()).out();
	frac(a.rational() * b.rational()).out();
	frac(a.rational() / b.rational()).out();
}

int main() {
	int n, m, idx = 1;
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		else {
			printf("Case %d:\n", idx++);
			solve(n, m);
		}
	}
} 
