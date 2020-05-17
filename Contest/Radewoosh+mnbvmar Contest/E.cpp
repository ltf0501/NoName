#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(1E3 + 10), kMod = int(1E9 + 7), kS = int(1E6 + 10);
ll f[kS], inf[kS];
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
void pre() {
	f[0] = f[1] = inf[0] = inf[1] = 1;
	for (int i = 2; i < kS; i++) f[i] = f[i - 1] * i % kMod;
	inf[kS - 1] = Rev(f[kS - 1]);
	for (int i = kS - 2; i >= 2; i--) inf[i] = inf[i + 1] * (i + 1) % kMod;
	return ;
}
int a[kN][kN], pos[kN];
ll m[kN], mp[kN][kN], s[kN], sp[kN][kN], dp[kN];
vector<pair<int, int>> p, np;
vector<int> v[kN];
int main() {
	pre();
	int k, n;
	ll ans = 0;
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= k; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	for (int i = 1; i <= k; i++) a[i][n + 1] = n + 1;
	++n;
	for (int i = 1; i <= k; i++) { 
		for (int o = 1; o <= n; o++) pos[a[i][o]] = o;
		for (int o = 1; o <= n; o++) {
			int x = a[i][o];
			m[x] = 1;
			s[x] = pos[x] - 1;
		}
		
		p.clear();
		for (int x = 1; x <= n; x++) for (int y = x + 1; y <= n; y++) p.PB({a[i][y], a[i][x]});

		for (pair<int, int> i : p) mp[i.F][i.S] = 1, sp[i.F][i.S] = pos[i.F] - pos[i.S] - 1;

		for (int j = i + 1; j <= k; j++) {
			for (int x = 1; x <= n; x++) pos[a[j][x]] = x;
			np.clear();
			for (int x = 1; x <= n; x++) v[x].clear();
			for (pair<int, int> i : p) if (pos[i.F] > pos[i.S]) np.PB(i), v[i.F].PB(i.S);
			p = np;
			for (int o = 1; o <= n; o++) {
				int x = a[j][o];
				m[x] = m[x] * inf[s[x]] % kMod;
				m[x] = m[x] * inf[pos[x] - 1] % kMod;
				s[x] = (s[x] + pos[x] - 1) % kMod;
				m[x] = m[x] * f[s[x]] % kMod;
			}

			for (int o = 1; o <= n; o++) {
				int x = a[j][o];
				dp[x] = m[x] * f[j - i + 1] % kMod;
				for (int y : v[x]) {
					mp[x][y] = mp[x][y] * inf[sp[x][y]] % kMod;
					mp[x][y] = mp[x][y] * inf[pos[x] - pos[y] - 1] % kMod;
					sp[x][y] = (sp[x][y] + pos[x] - pos[y] - 1) % kMod;
					mp[x][y] = mp[x][y] * f[sp[x][y]] % kMod;
					dp[x] = (kMod + dp[x] - dp[y] * mp[x][y] % kMod * f[j - i + 1] % kMod) % kMod;
				}
			}
			ans = (ans + dp[n] * inf[j - i + 1] % kMod) % kMod;
		}
	}
	printf("%lld\n", ans);
} 
