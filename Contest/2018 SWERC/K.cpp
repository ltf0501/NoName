#include <iostream>
using namespace std;
typedef long long int ll;
constexpr int kN = int(1E3 + 10), kMod = int(1E9 + 7), kP = 97;

ll val[kN], dp[kN][kN];

ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}

ll Rev(ll n) {return Pow(n, kMod - 2);}

ll Hash(int l, int r) {
	ll ans = (val[r] - val[l - 1] * Pow(kP, r - l + 1)) % kMod;
	if (ans < 0) return ans + kMod;
	else return ans;
}

bool same(int l, int x, int r) {
	ll left = Hash(l, x), all = Hash(l, r), tmp;
	tmp = Pow(kP, x - l + 1);
	left = left * (Pow(tmp, (r - l + 1) / (x - l + 1)) - 1) % kMod * Rev(tmp - 1) % kMod;
	return left == all;
}

int main() {
	int n;
	string s;
	cin >> n >> s;
	val[0] = 0;
	for (int i = 0; i < n; i++) val[i + 1] = (val[i] * kP + s[i] - 'a') % kMod;
	for (int i = 1; i <= n; i++) dp[i][i] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n - i; j++) {
			dp[j][j + i] = i + 1;
			for (int k = 1; k <= i; k++) {
				if ((i + 1) % k == 0) {
					if (same(j, j + k - 1, j + i)) dp[j][j + i] = min(dp[j][j + i], dp[j][j + k - 1]);
				}
				dp[j][j + i] = min(dp[j][j + i], dp[j][j + k - 1] + dp[j + k][j + i]);
			}
		}
	}
	cout << dp[1][n] << endl;
} 
