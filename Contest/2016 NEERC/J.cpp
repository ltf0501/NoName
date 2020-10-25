#include <stdio.h>
#include <set>
#include <utility>
#include <vector>
using namespace std;
constexpr int kN = int(5E3 + 10), kInf = int(1E9 + 10);
#define F first
#define S second
#define PB push_back

vector<int> v[kN];
int sz[kN], lm[kN], rm[kN], l[kN], k[kN];
set<int> se;
pair<double, double> cen[kN];
			
pair<double, double> Merge(pair<double, double> ca, int sza, pair<double, double> cb, int szb) {
	return {(ca.F * sza + cb.F * szb) / (sza + szb), (ca.S * sza + cb.S * szb) / (sza + szb)};
}
pair<double, double> Sub(pair<double, double> ca, int sza, pair<double, double> cb, int szb) {
	return {(ca.F * sza - cb.F * szb) / (sza - szb), (ca.S * sza - cb.S * szb) / (sza - szb)};
}

void Add(pair<double, double> &ca, pair<double, double> p) {
	ca.F += p.F;
	ca.S += p.S;
	return ;
}

int main() {
	freopen("jenga.in", "r", stdin);	
	freopen("jenga.out", "w", stdout);	
	int n, w, h, m, nsz, ans = kInf;
	pair<double, double> ncen;
	scanf("%d%d%d%d", &n, &w, &h, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &l[i], &k[i]);
	for (int i = 1; i <= m; i++) v[l[i]].PB(k[i]);
	for (int i = 1; i <= n; i++) se.insert(i);
	for (int i = 1; i <= h; i++) {
		for (int j : v[i]) se.erase(j);
		if (se.empty()) {
			lm[i] = n + 1;
			rm[i] = 0;
		}
		else {
			lm[i] = *se.begin();
			rm[i] = *prev(se.end());
		}
		sz[i] = int(se.size());
		cen[i] = {0.5 * w * n, 0.5 * w * n};
		ncen = {0, 0};
		for (int j : v[i]) {
			if (i & 1) Add(ncen, {0.5 * w * n, (j - 0.5) * w});
			else Add(ncen, {(j - 0.5) * w, 0.5 * w * n});
		}
		//printf("cen[%d] = (%lf, %lf), sza = %d, ncen = (%lf, %lf)\n", i, cen[i].F, cen[i].S, n - sz[i], ncen.F, ncen.S);
		if (n - sz[i]) {
			if (sz[i] == 0) cen[i] = {0, 0};
			else {
				ncen.F /= n - sz[i];
				ncen.S /= n - sz[i];
				cen[i] = Sub(cen[i], n, ncen, n - sz[i]);
			}
		}
		for (int j : v[i]) se.insert(j);
	}
	//for (int i = 1; i <= h; i++) printf("%d : (%d, %d)\n", i, lm[i], rm[i]);
	//for (int i = 1; i <= h; i++) printf("cen[%d] = (%lf, %lf)\n", i, cen[i].F, cen[i].S);
	for (int i = m; i >= 1; i--) {
		nsz = sz[h];
		ncen = cen[h];
		for (int j = h - 1; j >= 1; j--) {
			//printf("i = %d, j = %d, nsz = %d\n", i, j, nsz);
			if (nsz) {
				//printf("ncen = (%lf, %lf)\n", ncen.F, ncen.S);
				//printf("(%d, %d)\n", lm[j], rm[j]);
				if (j & 1) {
					if ((lm[j] - 1) * w < ncen.S && ncen.S < rm[j] * w);
					else ans = i;
				}
				else {
					if ((lm[j] - 1) * w < ncen.F && ncen.F < rm[j] * w);
					else ans = i;
				}
			}
			ncen = Merge(ncen, nsz, cen[j], sz[j]);
			nsz += sz[j];
		}

		if (l[i] & 1) {
			cen[l[i]] = Merge(cen[l[i]], sz[l[i]], {0.5 * w * n, (k[i] - 0.5) * w}, 1);
		}
		else {
			cen[l[i]] = Merge(cen[l[i]], sz[l[i]], {(k[i] - 0.5) * w, 0.5 * w * n}, 1);
		}
		sz[l[i]]++;
		lm[l[i]] = min(lm[l[i]], k[i]);
		rm[l[i]] = max(rm[l[i]], k[i]);
	}
	//for (int i = 1; i <= h; i++) printf("sz[%d] = %d\n", i, sz[i]);
	//for (int i = 1; i <= h; i++) printf("%d : (%d, %d) cen = (%lf, %lf)\n", i, lm[i], rm[i], cen[i].F, cen[i].S);
	if (ans == kInf) printf("no\n");
	else printf("yes\n%d\n", ans);
} 
