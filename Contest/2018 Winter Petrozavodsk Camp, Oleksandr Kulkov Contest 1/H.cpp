#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kMod = 1e9 + 7;
const int kN = 5e5 + 10;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}
int m; 
ll Cal(int a) {
	return 1LL * a * (a - 1) / 2 + 1LL * (m - a + 1) * (m - a) / 2;
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &m);
		int l = 0, r = m;
		int t;
		while(l + 1 < r) {
			int a = (l + r) >> 1;
			if(1LL * m * a <= Cal(a) && 1LL * m * (a + 1) >= Cal(a + 1)) {
				t = a;
				break;
			}
			if(1LL * m * a > Cal(a)) r = a;
			else l = a;
		}

		int ans = (m + t + 1) - 1LL * t * (t + 1) % kMod * Inv(m - t) % kMod;
		if(ans < 0) ans += kMod;
		ans = 1LL * ans * Inv(4) % kMod;
		printf("%d\n", ans);
	}
} 
