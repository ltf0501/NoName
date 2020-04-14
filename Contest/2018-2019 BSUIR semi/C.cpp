#include <iostream>
using namespace std;
typedef long long int ll;
constexpr int kN = int(5E1), kMod = int(1E9 + 7);
string s[kN];
int sf[kN][kN][kN][10], sc[kN][kN][kN][10], p[kN]; 
bool wentdfs[kN][kN][kN];
int m, val[kN][kN][kN];
void dp(int l, int r, int d, int y);
void dfs(int l, int r, int d) {
	if (wentdfs[l][r][d]) return ;
	wentdfs[l][r][d] = true;
	for (int i = 0; i < 10; i++) dp(l, r, d, i);
	for (int i = 1; i < 10; i++) sf[l][r][d][i] = (sf[l][r][d][i] + sf[l][r][d][i - 1]) % kMod;
	for (int i = 1; i < 10; i++) sc[l][r][d][i] = (sc[l][r][d][i] + sc[l][r][d][i - 1]) % kMod;

	return ;
}
void dp(int l, int r, int d, int y) {
	int a = 0, b = 0, ta, tb, tta, ttb;
	if (l == r) {
		if (s[l][d] == '?' || s[l][d] - '0' == y) {
			if (d == m - 1) a = y, b = 1;
			else {
				dfs(l, l, d + 1);
				ta = sf[l][l][d + 1][9]; 
				tb = sc[l][l][d + 1][9];
				a = (ta + 1LL * tb * p[m - d - 1] % kMod * y) % kMod;
				b = tb;
			}
		}
	}
	else if (d == m - 1) {
		if (y > 0) {
			dfs(l, r - 1, d);
			dfs(r, r, d);
			ta = sf[l][r - 1][d][y - 1];
			tb = sc[l][r - 1][d][y - 1];
			tta = (1LL * kMod + sf[r][r][d][y] - sf[r][r][d][y - 1]) % kMod;
			ttb = (1LL * kMod + sc[r][r][d][y] - sc[r][r][d][y - 1]) % kMod;
			a = (1LL * ta * ttb + 1LL * tta * tb) % kMod;
			b = 1LL * tb * ttb % kMod;
		}
	}
	else {
		if (y > 0) {
			for (int i = r - 1; i >= l; i--) if (val[i + 1][r][d] == 10 || val[i + 1][r][d] == y) {
				dfs(l, i, d);
				dfs(i + 1, r, d + 1);
				tta = ttb = ta = tb = 0;
				tb = sc[i + 1][r][d + 1][9];
				ta = (sf[i + 1][r][d + 1][9] + 1LL * tb * p[m - d - 1] % kMod * (y * (r - i)) % kMod) % kMod;
				tta = sf[l][i][d][y - 1];
				ttb = sc[l][i][d][y - 1];
				a = (a + 1LL * tta * tb + 1LL * ta * ttb) % kMod;
				b = (b + 1LL * ttb * tb) % kMod;
			}
			else break;
		}
		if (val[l][r][d] == y || val[l][r][d] == 10) {
			dfs(l, r, d + 1);
			b = (b + 1LL * sc[l][r][d + 1][9]) % kMod;
			a = (a + sf[l][r][d + 1][9] + 1LL * sc[l][r][d + 1][9] * p[m - d - 1] % kMod * (y * (r - l + 1))) % kMod; 
		}
	}

	sf[l][r][d][y] = a;
	sc[l][r][d][y] = b;
	return ;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	ll ans = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	p[0] = 1;
	for (int i = 1; i < kN; i++) p[i] = 1LL * p[i - 1] * 10 % kMod;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) val[i][i][j] = (s[i][j] == '?' ? 10 : s[i][j] - '0');
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int d = 0; d < m; d++) {
		if (val[i][j - 1][d] == val[j][j][d]) val[i][j][d] = val[j][j][d];
		else if (val[i][j - 1][d] == 10) val[i][j][d] = val[j][j][d];
		else if (val[j][j][d] == 10) val[i][j][d] = val[i][j - 1][d];
		else val[i][j][d] = -1;
	}
	dfs(0, n - 1, 0);
	ans = sf[0][n - 1][0][9]; 
	cout << ans << endl;
} 
