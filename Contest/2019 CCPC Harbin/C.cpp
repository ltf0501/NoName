#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long int ll;
__int128 gcd(__int128 a, __int128 b) {return b ? gcd(b, a % b) : a;}
struct Frac {
	__int128 a, b;
	void pull() {
		__int128 tmp = gcd(a, b);
		a /= tmp, b /= tmp;
		return ;
	}
	Frac(){}
	Frac(__int128 x, __int128 y) {a = x, b = y; pull();}
	void operator += (Frac f) {
		a *= f.b;
		a += b * f.a;
		b *= f.b;
		pull();
	}
	void operator /= (__int128 x) {
		b *= x;
		pull();
	}
};

constexpr int kN = 10100, kM = 20;
int mp[kN], gp[kN], games[kN], matches[kN], a[kM];
bool bye[kN];
Frac mwp[kN], gwp[kN];
vector<int> opponents[kN];
void solve() {
	int n, m, p1, p2, w1, w2, d, cnt = 0; 
	vector<int> v;
	Frac ogw, omw;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) opponents[i].clear();
	for (int i = 1; i <= n; i++) mp[i] = gp[i] = games[i] = matches[i] = 0;
	for (int i = 1; i <= n; i++) bye[i] = false;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) bye[j] = true;
		for (int j = 1; j <= a[i]; j++) {
			scanf("%d%d%d%d%d", &p1, &p2, &w1, &w2, &d);
			if (w1 > w2) mp[p1] += 3;
			else if (w1 < w2) mp[p2] += 3;
			else mp[p1]++, mp[p2]++;
			gp[p1] += 3 * w1 + d;
			gp[p2] += 3 * w2 + d;
			matches[p1]++, matches[p2]++;
			games[p1] += w1 + w2 + d;
			games[p2] += w1 + w2 + d;
			opponents[p1].PB(p2);
			opponents[p2].PB(p1);
			bye[p1] = bye[p2] = false;
		}
		for (int j = 1; j <= n; j++) if (bye[j]) {
			mp[j] += 3;
			gp[j] += 6;
			games[j] += 2;
			matches[j]++;
		}
		for (int j = 1; j <= n; j++) {
			if (matches[j] == 0) mwp[j] = Frac(1, 3);
			else if (matches[j] >= mp[j]) mwp[j] = Frac(1, 3);
			else mwp[j] = Frac(mp[j], matches[j] * 3);
			if (games[j] == 0) gwp[j] = Frac(1, 3);
			else if (games[j] >= gp[j]) gwp[j] = Frac(1, 3);
			else gwp[j] = Frac(gp[j], games[j] * 3);
		}
		printf("Round %d\n", i);
		for (int j = 1; j <= n; j++) {
			if (opponents[j].empty()) ogw = omw = Frac(1, 3); 
			else {
				ogw = omw = Frac(0, 1);
				for (int k : opponents[j]) ogw += gwp[k], omw += mwp[k];
				ogw /= int(opponents[j].size());
				omw /= int(opponents[j].size());
			}
			printf("%d %lld/%lld %lld/%lld %lld/%lld\n", mp[j], ll(omw.a), ll(omw.b), ll(gwp[j].a), ll(gwp[j].b), ll(ogw.a), ll(ogw.b)); 
		}
	}
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
