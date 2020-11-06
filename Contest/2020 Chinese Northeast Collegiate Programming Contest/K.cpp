#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e3 + 10;
const ll kInf = ll(1e18);
typedef pair<ll, int> pii;
#define F first
#define S second

int n, m, K, U;
int a[kN][kN];

deque<pii> col[kN], row;
ll dp[kN][kN];

static inline char GetRawChar() {
	static char buf[1 << 16], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
		p = buf;
	}
	return *p++;
}

static inline int R() {
	int n = 0, mul = 1;
	char c = GetRawChar();
	if (!c) return -1;
	if (c == '-') mul = -1, c = GetRawChar();
	do {
		n = n * 10 + (c - '0');
	} while ((c = GetRawChar()) && (unsigned)(c - '0') <= 10U);
	return n * mul;
}

int main() {
	while(true) {
		n = R();
		if (n == -1) break;
		m = R();
		K = R();
		U = R();
		//cerr << "!" << n <<  ' ' << m << ' ' << K << ' ' << U << '\n';
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= m; j++) a[i][j] = R();

		for(int j = 1; j <= m; j++) col[j].clear();
		for(int i = 0; i <= n; i++) {
			for(int j = 0; j <= m; j++) dp[i][j] = -1;
		}	
		dp[1][1] = a[1][1];
		for(int i = 1; i <= n; i++) {
			row.clear();
			for(int j = 1; j <= m; j++) {
				while(!col[j].empty() && col[j].front().S < i - K) col[j].pop_front();
				while(!row.empty() && row.front().S < j - K) row.pop_front();
				if(a[i][j] > 0) {
					if(~dp[i - 1][j]) dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i][j]);
					if(~dp[i - 1][j - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i][j]);
					if(~dp[i][j - 1]) dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);

					if(!col[j].empty()) dp[i][j] = max(dp[i][j], col[j].front().F + a[i][j] - U);
					if(!row.empty()) dp[i][j] = max(dp[i][j], row.front().F + a[i][j] - U);
				}

				if(dp[i][j] >= U) {
					while(!col[j].empty() && col[j].back().F <= dp[i][j]) col[j].pop_back();
					col[j].emplace_back(dp[i][j], i);
				}

				if(!col[j].empty()) {
					while(!row.empty() && row.back().F <= col[j].front().F) row.pop_back();
					row.emplace_back(col[j].front().F, j); 
				}
			}
		}

		//for(int i = 1; i <= n; i++) {
		//	for(int j = 1; j <= m; j++) printf("%lld ", dp[i][j]); puts("");
		//}
		if(dp[n][m] < 0) puts("-1");
		else printf("%lld\n", dp[n][m]); 
	}
	return 0;
} 
