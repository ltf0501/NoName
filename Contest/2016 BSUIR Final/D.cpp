#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
typedef long long int ll;

constexpr int kMod = int(1E9 + 7), kN = int(1E5 + 10), kInf = int(1E9 + 10);

struct BIT {
	struct _ {
		int pos;
		BIT* bit;
		_(BIT* b, int n) {bit = b; pos = n;}
		operator ll() const {return bit->ask(pos);}
		void operator += (ll x) {bit->add(pos, x);}
	};
	ll val[kN];
	void init() {memset(val, 0, sizeof(val));}
	void add(int n, ll x) {
		while (n < kN) {
			val[n] = (val[n] + x) % kMod;
			n += n & -n;
		}
		return ;
	}
	ll ask(int n) {
		ll ans = 0;
		while (n) {
			ans += val[n];
			n ^= n & -n;
		}
		return ans % kMod;
	}
	_ operator [](int n) {return _(this, n);}
};

struct seg_tree {
	ll val[kN << 2], sz[kN << 2], flag[kN << 2];
	void init(int n, int l, int r) {
		val[n] = flag[n] = 0;
		sz[n] = r - l + 1;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void addtag(int n, ll x) {
		val[n] = (val[n] + sz[n] * x % kMod) % kMod;
		flag[n] = (flag[n] + x) % kMod;
		return ;
	}
	void pull(int n) {
		val[n] = (val[n << 1] + val[n << 1 | 1]) % kMod;
		return ;
	}
	void push(int n) {
		if (flag[n]) {
			addtag(n << 1, flag[n]);
			addtag(n << 1 | 1, flag[n]);
			flag[n] = 0;
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, ll x) {
		if (L <= l && r <= R) addtag(n, x);
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	void set(int n, int l, int r, int pos) {
		sz[n]--;
		if (l < r) {
			int mid = (l + r) >> 1;
			push(n);
			if (pos <= mid) set(n << 1, l, mid, pos);
			else set(n << 1 | 1, mid + 1, r, pos);
			pull(n);
		}
		return ;
	}
	ll ask(int n, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[n];
		else if (l > R || L > r) return 0;
		else {
			int mid = (l + r) >> 1;
			push(n);
			return (ask(n << 1, l, mid, L, R) + ask(n << 1 | 1, mid + 1, r, L, R)) % kMod;
		}
	}
};


BIT F[2], DP[2];
seg_tree J[2];
pair<int, int> p[kN];
int jpos[kN], nxt[kN], prv[kN];
ll dp[kN][2], f[kN][2];

int main() {
	int n, M, m;
	ll ans = 0;
	vector<int> x;
	vector<pair<int, int>> jx;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].S, &p[i].F);
	sort(p + 1, p + n + 1);

	for (int i = 1; i <= n; i++) x.PB(p[i].S);
	sort(x.begin(), x.end());
	x.resize(unique(x.begin(), x.end()) - x.begin());
	for (int i = 1; i <= n; i++) p[i].S = lower_bound(x.begin(), x.end(), p[i].S) - x.begin() + 2;
	//for (int i = 1; i <= n; i++) printf("p[%d] = %d\n", i, p[i].S);
	for (int i = 1; i <= n; i++) jx.PB({p[i].S, i});
	sort(jx.begin(), jx.end());
	jx.resize(unique(jx.begin(), jx.end()) - jx.begin());
	for (int i = 1; i <= n; i++) jpos[i] = lower_bound(jx.begin(), jx.end(), make_pair(p[i].S, i)) - jx.begin() + 1;
	for (int i = 1; i <= n; i++) nxt[i] = lower_bound(jx.begin(), jx.end(), make_pair(p[i].S + 1, 0)) - jx.begin() + 1;
	for (int i = 1; i <= n; i++) prv[i] = lower_bound(jx.begin(), jx.end(), make_pair(p[i].S, 0)) - jx.begin();
	//for (int i = 1; i <= n; i++) printf("%d = (%d, %d, %d)\n", i, prv[i], jpos[i], nxt[i]);

	DP[0].init(), DP[1].init();
	F[0].init(), F[1].init();
	J[0].init(1, 1, n), J[1].init(1, 1, n);

	F[0][1] += 1; F[1][n + 3] += 1;
	for (int i = 1, now = 1, lst = 1; i <= n;) {
		while (now <= n && p[now].F == p[i].F) {
			//printf("DP[1](%d, %d) = %lld\n", p[i].S, n + 3, ll(DP[1][n + 3] - DP[1][p[i].S]));
			//printf("J[1].ask(%d, %d) = %lld\n", jpos[i] + 1, n, J[1].ask(1, 1, n, jpos[i] + 1, n));
			dp[now][0] = (DP[1][n + 3] - DP[1][p[now].S] + J[1].ask(1, 1, n, nxt[now], n) + kMod) % kMod;
			dp[now][1] = (DP[0][p[now].S - 1] + J[0].ask(1, 1, n, 1, prv[now])) % kMod;
			f[now][0] = (F[1][n + 3] - F[1][p[now].S] + kMod) % kMod;
			f[now][1] = F[0][p[now].S - 1];
			//printf("J[1].add(%d, %d, %lld)\n", 1, jpos[now] - 1, f[now][1]); 
			//printf("J[0].add(%d, %d, %lld)\n", nxt[now], n, f[now][0]);
			now++;
		}
		//printf("i = %d, now = %d\n", i, now);
		while (lst < now) {
			J[0].set(1, 1, n, jpos[lst]);
			J[1].set(1, 1, n, jpos[lst]);
			lst++;
		}
		while (i < now) {
			//printf("i = %d, now = %d\n", i, now);
			F[0][p[i].S] += f[i][0];
			F[1][p[i].S] += f[i][1];
			DP[0][p[i].S] += dp[i][0];
			DP[1][p[i].S] += dp[i][1];
			J[0].add(1, 1, n, nxt[i], n, f[i][0]);
			J[1].add(1, 1, n, 1, prv[i], f[i][1]);
			i++;
		}
	}

	//for (int i = 1; i <= n; i++) {
	//	printf("dp[%d][0] = %lld, dp[%d][1] = %lld\n", i, dp[i][0], i, dp[i][1]);
	//	printf(" f[%d][0] = %lld,  f[%d][1] = %lld\n", i, f[i][0], i, f[i][1]);
	//}
	
	M = 0, m = kInf;
	for (int i = n, now = n; i >= 1;) {
		while (now >= 1 && p[now].F == p[i].F) {
			if (p[now].S >= M) ans += dp[now][0];
			if (p[now].S <= m) ans += dp[now][1];
			//if (p[now].S >= M) printf("M : %d\n", now);
			//if (p[now].S <= m) printf("m : %d\n", now);
			now--;
		}
		while (i > now) {
			M = max(M, p[i].S), m = min(m, p[i].S);
			i--;
		}
	}
	printf("%lld\n", ans % kMod);
} 
