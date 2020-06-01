#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 2e5 + 10;
const ll kInf = 1e18;
#define F first
#define S second

ll n, s;
int k, a[205];
bitset<kN> b[70];
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%d", &n, &s, &k);
		for(int i = 0; i < k; i++) scanf("%d", &a[i]);
		for(int i = 0; i <= 60; i++) b[i].reset();
		b[0][0] = true;
		for(int i = 0; i < 60; i++) { 
			if (n & 1) for (int j = 0; j < k; j++) b[i + 1] ^= b[i] << a[j];
			else b[i + 1] = b[i];
			
			b[i].reset();
			for (int j = 0; j < kN; j++) if (s - j >= 0 && !((s - j) & 1) && b[i + 1][j]) b[i][j >> 1] = true;
			b[i + 1] = b[i];
			s >>= 1;
			n >>= 1;
		}
		printf("%d\n", b[60].count() & 1);
	}
	return 0;
}
