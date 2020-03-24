#include <bits/stdc++.h>
using namespace std;
const int kN = 1e6 + 10;
typedef long long ll;
typedef pair<int, ll> pii;
#define F first
#define S second
int n;
pii Cal(const vector<int> &v) {
	pii res = {v[0], 1};
	for(int i = 1; i < int(v.size()); i++) {
		if(v[i] == res.F) res.S++; 
		else {
			if(!res.S) res = {v[i], 1};
			else res.S--;
		}
	}
	return res;
}
pii Merge(pii x, pii y) {
	if(x.F == y.F) return {x.F, x.S + y.S};
	if(x.S > y.S) return {x.F, x.S - y.S};
	return {y.F, y.S - x.S};
}
pii a[kN];
ll cnt[kN], len[kN];
int oper[kN], x[kN], y[kN];
vector<int> V[kN];
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int op; scanf("%d", &op);
			oper[i] = op;
			if(op == 1) {
				int k; scanf("%d", &k);
				V[i].resize(k);
				for(int j = 0; j < k; j++) scanf("%d", &V[i][j]);
				a[i] = Cal(V[i]);
			}
			else {
				scanf("%d%d", &x[i], &y[i]);
				a[i] = Merge(a[x[i]], a[y[i]]);
			}
		}
		int val = a[n].F;
		//puts("a");
		//for(int i = 1; i <= n; i++) printf("%d %lld\n", a[i].F, a[i].S);
		//puts("");
		//printf("val = %d\n", val);
		for(int i = 1; i <= n; i++) {
			if(oper[i] == 1) {
				int c = 0;
				for(int p : V[i]) c += p == val;
				cnt[i] = c;
				len[i] = int(V[i].size());
			}
			else {
				cnt[i] = cnt[x[i]] + cnt[y[i]];
				len[i] = len[x[i]] + len[y[i]];
			}
		}
		//printf("cnt = %lld, len = %lld\n", cnt[n], len[n]);
		if(2 * cnt[n] > len[n]) printf("%lld\n", 2 * (len[n] - cnt[n]));
		else printf("%lld\n", len[n]);
	}
	return 0;
} 
