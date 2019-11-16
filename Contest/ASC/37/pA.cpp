#include <bits/stdc++.h>
using namespace std;
int m, n;
int g[55][55];
vector<int> tour;
 
void euler(int x) {
	for (int y = 1; y <= n; y++) {
		if (g[x][y]) {
			int tmp = g[x][y];
			g[x][y] = g[y][x] = g[x][y] % 2 ? 0 : 1;
			euler(y);
			while (tmp > 2) {
				tour.emplace_back(y);
				tour.emplace_back(x);
				tmp -= 2;
			}
			tour.emplace_back(y);
		}
	}
}
 
int main() {
#ifdef ONLINE_JUDGE
	freopen("achromatic.in", "r", stdin);
	freopen("achromatic.out", "w", stdout);
#endif
	scanf("%d", &m);
	for(n = 50; n >= 0; n--) {
		int tmp = (n & 1) ? 0 : n / 2;
		if(m >= n * (n - 1) / 2 + tmp) {
			if(n == 2 && !((m - n * (n - 1) / 2 - tmp) & 1)) break;
			if(n >= 3) {
				if(n & 1)
				{if(m - n * (n - 1) / 2 != 1) break;}
				else {
					if(m - n * (n - 1) / 2>= n / 2) break;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) g[i][j] = g[j][i] = 1;
	}
	if(!(n & 1)) {
		for(int i = 1; i <= n / 2; i++) g[i][i + n / 2] = g[i + n / 2][i] = 2;
	}
	int tmp = (n & 1) ? 0 : n / 2;
	int k = m - n * (n - 1) / 2 - tmp;
	if(k == 1) {
		g[1][1 + n / 2]--, g[1 + n / 2][1]--;
		g[1][2]++, g[2][1]++;
		g[1 + n / 2][2]++, g[2][1 + n / 2]++; 
	}
	else { 
		if(k & 1) {
			g[1][2]++, g[2][1]++;
			g[1][3]++, g[3][1]++;
			g[2][3]++, g[3][2]++;
			k -= 3;
		}
		g[1][2] += k;
		g[2][1] += k;
	}
	euler(1);
	cout << n << '\n';
	for (int x : tour) cout << x << ' ';
	return 0;
}
