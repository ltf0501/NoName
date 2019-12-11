#include <bits/stdc++.h>
using namespace std;
const int kInf = 1e9;
const int kN = 1e5 + 10;
const int kC = 4;
char s[kN];
int ans;
int n;
map<char, int> mp;
struct PAM { // 0-base
	int fail[kN], len[kN], nxt[kN][kC], sz, last;
	int cnt[kN];

	int dp[kN];
	int match[kN];
	int newnode(int l, int fl = -1) {
		len[sz] = l, fail[sz] = fl;
		cnt[sz] = 0;
		for(int i = 0; i < kC; i++) nxt[sz][i] = -1; 
		return sz++;
	}
	void init() {
		sz = 0, last = 1;
		match[0] = match[1] = 0;
		dp[1] = 1;
		newnode(-1, 0); // odd
		newnode(0, 0); // even
	}
	int get_fail(int x, int pos) {
		while(pos - 1 - len[x] < 0 || s[pos - 1 - len[x]] != s[pos]) x = fail[x];
		return x;
	}
	void build(char *s) {
		int n = strlen(s);
		for(int i = 0; i < n; i++) {
			int c = mp[s[i]];
			int cur = get_fail(last, i);	
			//printf("i = %d, cur = %d\n", i, cur);
			//printf("nxt[cur][c] = %d\n", nxt[cur][c]);
			if(nxt[cur][c] == -1) {
				int now = newnode(len[cur] + 2);
				//printf("len[%d] = %d\n", now, len[now]);
				int x;
				fail[now] = len[now] == 1 ? 1 : nxt[x = get_fail(fail[cur], i)][c];
				//printf("x = %d\n", x);
				//printf("fail[%d] = %d\n", now, fail[now]);
				nxt[cur][c] = now;

				if(len[now] <= 2) match[now] = 1;
				else {
					int tmp = match[cur];
					while(i - 1 - len[tmp] < 0 || s[i - 1 - len[tmp]] != s[i] 
							|| (len[tmp] + 2) * 2 > len[now]) tmp = fail[tmp];
					match[now] = nxt[tmp][c];
				} 

				if(len[now] & 1) {
					if(len[now] == 1) dp[now] = 1;
					else dp[now] = min(dp[cur] + 2, dp[match[now]] + len[now] - len[match[now]]);
				}
				else {
					dp[now] = min(dp[cur] + 1, dp[match[now]] + len[now] / 2 - len[match[now]] + 1);
				}
				//printf("match[%d] = %d, dp[%d] = %d\n", now, match[now], now, dp[now]);
				ans = min(ans, dp[now] + n - len[now]);
			}
			last = nxt[cur][c];
			cnt[last]++;
		}
	}
	void count() { // count the number of each palindromic string
		for(int i = sz - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
	} 
};

int main() {
	mp['A'] = 0, mp['T'] = 1, mp['C'] = 2, mp['G'] = 3;
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		PAM solver;
		solver.init();
		ans = kInf;
		n = strlen(s);
		solver.build(s);
		printf("%d\n", ans);
	}
	return 0;
}
