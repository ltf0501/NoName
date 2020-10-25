#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(4E3 + 10);

int vf, vp, vh;

double dis(int ax, int ay, int bx, int by, int va) {
	double x = ax - bx, y = ay - by, d, h, ans;
	va -= vp;
	d = sqrt(x * x + y * y);
	h = d / vh * vp;
	ans = d / vh + h / va;
	return ans;
}

double d[kN][kN], dd[kN];
int x[kN], y[kN], v[kN];
bool went[kN];

void solve() {
	int sx, sy, tx, ty, n, idx, cnt = 0;
	double ans;
	scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
	scanf("%d%d%d", &vf, &vp, &vh);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) scanf("%d%d%d", &x[i], &y[i], &v[i]);
	for (int i = 1; i <= n; i++) went[i] = false;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j) 
		d[i][j] = dis(x[i], y[i], x[j], y[j], v[i]);
	ans = dis(x[0], y[0], tx, ty, v[0]);
	for (int i = 1; i <= n; i++) if (v[i] <= vp) {
		went[i] = true;
		dd[i] = ans;
		cnt++;
	}
	else dd[i] = dis(x[0], y[0], x[i], y[i], v[0]);
	while (cnt <= n) {
		idx = 0;
		for (int j = 1; j <= n; j++) if (!went[j]) {
			if (idx == 0) idx = j;
			else if (dd[j] < dd[idx]) idx = j;
		}
		went[idx] = true;
		for (int j = 1; j <= n; j++) if (!went[j]) dd[j] = min(dd[j], d[idx][j] + dd[idx]); 
		cnt++;
	}
	for (int i = 1; i <= n; i++) if (v[i] > vp) ans = min(ans, dis(x[i], y[i], tx, ty, v[i]) + dd[i]);
	printf("%.20lf\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}

