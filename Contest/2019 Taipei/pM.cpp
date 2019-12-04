#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const ll INF = 5e16;
#define F first
#define S second
int pw(int a, ll n, int p) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % p;
		n >>= 1, a = 1LL * a * a % p;
	}
	return res;
}
vector<int> fac;
void init(int p, int r, int& pr) {
	fac.clear();
	pr = 1;
	for(int i = 0; i < r; i++) pr *= p;
	fac.resize(pr + 5);
	fac[0] = 1;
	for(int i = 1; i < pr; i++) {
		if(i % p == 0) fac[i] = fac[i - 1];
		else fac[i] = 1LL * fac[i - 1] * i % pr;
	}
	//for(int i = 1; i < pr; i++) printf("%d ", fac[i]); puts("");
}
ll Vp(ll x, int p) { //v_p(x!)
	if(!x) return 0;
	return x / p + Vp(x / p, p);
}
int f(ll x, int p, int pr) {
	if(x == 0) return 1;
	int res = 1LL * f(x / p, p, pr) * fac[x % pr] % pr;
	res = 1LL * res * pw(fac[pr - 1], x / pr, pr) % pr;
	//if((x / pr) & 1) res = pr - res;
	//printf("x = %lld, res = %d, pr = %d\n", x, res, pr);
	return res;
}
template<typename T>
tuple<T, T, T> Extgcd(T a, T b) {
	if(!b) return make_tuple(a, 1, 0);
	T d, x, y;
	tie(d, x, y) = Extgcd(b, a % b);
	return make_tuple(d, y, x - (a / b) * y);
}
int Inv(int a, int d) {
	int tmp, x, y;
	tie(tmp, x, y) = Extgcd(a, d);
	x %= d;
	if(x < 0) x += d;
	assert(1LL * a * x % d == 1);
	return x;
}
int CRT(vector<int> rres, vector<int> mod) {
	int n = int(mod.size());
	int mmod = 1, x = 0;
	for(int i = 0; i < n; i++) mmod *= mod[i];
	for(int i = 0; i < n; i++) {
		int w = mmod / mod[i];
		auto t = Extgcd(mod[i], w);
		x = (x + 1LL * get<2>(t) * w * rres[i] % mmod) % mmod;
	}
	x %= mmod;
	if(x < 0) x += mmod;
	return x;
}
int main() {
	ll m, n; int d;
	scanf("%lld%lld%d", &m, &n, &d);
	int D = d;
	vector<pii> vp;
	for(int i = 2; i * i <= d; i++) {
		if(d % i == 0) {
			int cnt = 0;
			while(d % i == 0) d /= i, cnt++;
			vp.emplace_back(i, cnt);
		}
	}
	if(d != 1) vp.emplace_back(d, 1);
	ll k = -1;
	map<int, pair<ll, int>> mp;
	for(auto v : vp) {
		int p = v.F, r = v.S;
		int pr;
		init(p, r, pr);
		//printf("pr = %d\n", pr);
		ll tmp = Vp(m, p) - Vp(n, p) - Vp(m - n, p);
		if(k == -1) k = tmp / r;
		else k = min(k, tmp / r);

		int res = 1LL * f(m, p, pr) * Inv(f(n, p, pr), pr) % pr * Inv(f(m - n, p, pr), pr) % pr;
		//printf("tmp = %lld, res = %d\n", tmp, res);
		mp[p] = {tmp, res};
	}
	//printf("k = %lld\n", k);
	vector<int> rres, mod;
	for(auto v : vp) {
		int p = v.F, r = v.S;
		int pr = 1;
		for(int i = 0; i < r; i++) pr *= p;
		mod.push_back(pr);

		auto vv = mp[p];
		//printf("%lld %d\n", vv.F, vv.S);
		ll num = vv.F - k * r;
		int res = vv.S;
		for(int i = 0; i < num; i++) res = 1LL * res * p % pr;
		res = 1LL * res * Inv(pw(D / pr, k, pr), pr) % pr;
		rres.push_back(res);
	}
	//for(int x : rres) printf("%d ", x); puts("");
	//for(int x : mod) printf("%d ", x); puts("");
	printf("%d\n", CRT(rres, mod)); 
	return 0;
}
