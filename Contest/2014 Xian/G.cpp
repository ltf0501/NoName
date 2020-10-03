#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 2e5 + 10;
const int kC = 26;

char s[kN], t[kN];
struct PAM {
	int fail[kN], len[kN], nxt[kN][kC], sz, last;
	int cnt[kN];
	int newnode(int l, int fl = -1) {
		len[sz] = l; fail[sz] = fl;
		cnt[sz] = 0;
		for(int i = 0; i < kC; i++) nxt[sz][i] = -1;
		return sz++;
	}
	void init() {
		sz = 0, last = 1;
		newnode(-1, 0);
		newnode(0, 0);
	}

	int get_fail(const char *s, int x, int pos) {
		while(pos - 1 - len[x] < 0 || s[pos - 1 - len[x]] != s[pos]) x = fail[x];
		return x;
	}

	void count() {
		for(int i = sz - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
	}

	void build(const char *s) {
		int n = int(strlen(s));
		for(int i = 0; i < n; i++) {
			int c = s[i] - 'a';
			int cur = get_fail(s, last, i);
			if(nxt[cur][c] == -1) {
				int now = newnode(len[cur] + 2);
				fail[now] = (len[now] == 1) ? 1 : nxt[get_fail(s, fail[cur], i)][c];
				nxt[cur][c] = now;
			}

			last = nxt[cur][c];
			cnt[last]++;
		}
		count();
	} 
}Stree, Ttree;

ll Dfs(int s_idx, int t_idx) {
	ll res = 0;
	for(int c = 0; c < 26; c++) {
		if(Stree.nxt[s_idx][c] != -1 && Ttree.nxt[t_idx][c] != -1) {
			int nxt_s_idx = Stree.nxt[s_idx][c];
			int nxt_t_idx = Ttree.nxt[t_idx][c];
			res += 1LL * Stree.cnt[nxt_s_idx] * Ttree.cnt[nxt_t_idx] + Dfs(nxt_s_idx, nxt_t_idx);
		}
	}
	return res;
}
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%s %s", s, t);
		Stree.init(), Ttree.init();
		Stree.build(s), Ttree.build(t);
		ll ans = Dfs(0, 0) + Dfs(1, 1);
		printf("Case #%d: %lld\n", ++cas, ans);	
	}
	return 0;
} 
