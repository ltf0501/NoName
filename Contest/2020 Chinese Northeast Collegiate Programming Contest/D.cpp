#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(2E5 + 10);

int x[kN], c[kN];

void solve() {
	int n, h, H, winner = 1, ans, tmp;
	scanf("%d%d%d", &n, &h, &H);
	for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	auto val = [&](int i) -> int {
		if (x[i] % (H * 2) < H) {
			if ((x[i] - 1) % H + 1 <= h) return x[i] + c[i];
			else return H + (H - h) - ((x[i] - 1) % H + 1) + c[i] + x[i];
		}
		else {
			if ((H - (x[i] - 1) % H + 1) <= h) return x[i] + c[i];
			else return (H - (x[i] - 1) % H + 1) - h + c[i] + x[i];
		}
	};
	ans = val(1);
	for (int i = 2; i <= n; i++) {
		tmp = val(i);
		if (tmp < ans) {
			ans = tmp;
			winner = i;
		}
	}

	printf("%d\n", winner);
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) solve();
} 
