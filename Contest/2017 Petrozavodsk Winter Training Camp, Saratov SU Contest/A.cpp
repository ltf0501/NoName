#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int ll;
constexpr int kN = int(5E5 + 10);

int a[kN], b[kN], c[kN], d;

ll Xsmall(int nx, int ny, int nz, int x[], int y[], int z[]) {
	ll yl = 1, yr = 0, zl = 1, zr = 0, ans = 0;
	for (int i = 1; i <= nx; i++) {
		while (yl <= ny) {
			if (y[yl] <= x[i]) yl++;
			else break;
		}
		while (yr < ny) {
			if (y[yr + 1] <= x[i] + d) yr++;
			else break;
		}
		while (zl <= nz) {
			if (z[zl] <= x[i]) zl++;
			else break;
		}
		while (zr < nz) {
			if (z[zr + 1] <= x[i] + d) zr++;
			else break;
		}
		ans += (zr - zl + 1) * (yr - yl + 1);
	}
	return ans;
}

ll Two(int nx, int ny, int nz, int x[], int y[], int z[]) {
	ll yl = 1, yr = 0, zl = 1, zr = 0, ans = 0;
	for (int i = 1; i <= nx; i++) {
		while (yl <= ny) {
			if (y[yl] < x[i]) yl++;
			else break;
		}
		while (yr < ny) {
			if (y[yr + 1] <= x[i]) yr++;
			else break;
		}
		while (zl <= nz) {
			if (z[zl] <= x[i]) zl++;
			else break;
		}
		while (zr < nz) {
			if (z[zr + 1] <= x[i] + d) zr++;
			else break;
		}
		ans += (zr - zl + 1) * (yr - yl + 1);
	}
	return ans;
}

ll Same(int nx, int ny, int nz, int x[], int y[], int z[]) {
	ll yl = 1, yr = 0, zl = 1, zr = 0, ans = 0;
	for (int i = 1; i <= nx; i++) {
		while (yl <= ny) {
			if (y[yl] < x[i]) yl++;
			else break;
		}
		while (yr < ny) {
			if (y[yr + 1] <= x[i]) yr++;
			else break;
		}
		while (zl <= nz) {
			if (z[zl] < x[i]) zl++;
			else break;
		}
		while (zr < nz) {
			if (z[zr + 1] <= x[i]) zr++;
			else break;
		}
		ans += (zr - zl + 1) * (yr - yl + 1);
	}
	return ans;
	
}

ll solve(int na, int nb, int nc) {
	ll ans = 0;
	for (int i = 1; i <= na; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= nb; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= nc; i++) scanf("%d", &c[i]);
	ans = Xsmall(na, nb, nc, a, b, c) + Xsmall(nb, na, nc, b, a, c) + Xsmall(nc, na, nb, c, a, b);
	ans += Two(na, nb, nc, a, b, c) + Two(na, nc, nb, a, c, b) + Two(nb, nc, na, b, c, a);
	ans += Same(na, nb, nc, a, b, c);
	return ans;
}

int main() {
	int na, nb, nc;
	while (scanf("%d%d%d%d", &d, &na, &nb, &nc) != EOF) printf("%lld\n", solve(na, nb, nc));
} 
