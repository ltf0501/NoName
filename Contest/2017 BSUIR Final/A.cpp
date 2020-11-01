#pragma GCC optimize("O3", "fast-math")
#pragma GCC target("tune=native,avx,avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kMod = 1e9 + 7;
const ll kInf = (1LL << 62) - 1;
typedef long double LD;

char GetRawChar() {
	static char buf[1 << 16], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
		p = buf;
	}
	return *p++;
}
ll GetLL() {
	char c;
	ll n = 0;
	while ((c = GetRawChar()) && (unsigned)(c - '0') <= 10U) n = n * 10 + (c - '0');
	return n;
}

ll n, k;
int fpow(int a, ll n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}

int add(int x, int y) {
	x += y;
	if(x >= kMod) x -= kMod;
	return x;
}
int sub(int x, int y) {
	x -= y;
	if(x < 0) x += kMod;
	return x;
}

ll cc[105][105];

ll C(ll n, int m) {
	if(n <= 100) return cc[n][m];
	ll res = 1;
	//printf("n = %lld, m = %d\n", n, m);
	long double ni = n, di = 1;
	for(int i = 1; i <= m; i++, ni -= 1, di += 1) {
		auto tmp = (long double)(res) * (n - i + 1) / i;
		if(tmp >= 1e18) return kInf;
		res = tmp;

		//ll g = __gcd(res, ll(i));
		//ll a = res / g, b = i / g;
		//assert((n - i + 1) % b == 0);
		//res = 1LL * (n - i + 1) / b * a;
		//printf("i = %d, n - i + 1 = %lld, res = %lld\n", i, n - i + 1, res);
	}
	//printf("res = %lld\n", res);
	return res;
}

void pre() {
	cc[0][0] = 1;
	for(int i = 1; i <= 100; i++) {
		cc[i][0] = cc[i][i] = 1;
		for(int j = 1; j < i; j++) {
			if(cc[i - 1][j] == kInf || cc[i - 1][j - 1] == kInf) cc[i][j] = kInf;
			cc[i][j] = cc[i - 1][j] + cc[i - 1][j - 1];
			if(cc[i][j] > ll(1e18)) cc[i][j] = kInf;
		}
	}
}
int main() {
	pre();
	ll T = GetLL();
	while(T--) {
		//scanf("%lld%lld", &n, &k);
		n = GetLL(), k = GetLL();
		if(n == 1) {
			if(k == 1) puts("1");
			else puts("-1");
			continue;
		}
		ll l = 1, r = 2e9;
		while(r - l > 1) {
			ll m = (l + r) >> 1;
			ll num = m * (m + 1) / 2;
			if(num >= n) r = m;
			else l = m;
		}

		ll rest = n - l * (l + 1) / 2;
		// 11...1(rest)0 00...0 ~ 11...1(rest)0 11...1
		// total length = r

		ll num_zero = r - rest - 1;
		//printf("r = %lld\n", r);
		//printf("k = %lld, num_zero = %lld, rest = %lld\n", k, num_zero, rest);
		if(num_zero == -1) {
			if(k > 1) puts("-1");
			else {
				printf("%d\n", fpow(2, r) - 1);
			}
			continue;
		}
		
		if(num_zero <= 62 && (1LL << num_zero) < k) {
			puts("-1"); continue;
		}
		if(k == 1) {
			int ans = sub(fpow(2, r), fpow(2, num_zero + 1));
			printf("%d\n", ans);
			continue;
		}

		int num_bit = 0;		
		ll presum = 1, cur = 1;
		for(int i = 1; ; i++) {
			auto tmp = (long double)(cur) * (num_zero - i + 1) / i;
			if(tmp > 1e18) {num_bit = i; break;}
			cur = tmp;
			if(presum + cur >= k) {
				num_bit = i; break;
			}
			presum += cur;
		}

		vector<ll> pos;
		ll tmp_k = k - presum;
		ll last = num_zero;
		//printf("num_bit = %d, tmp_k = %lld\n", num_bit, tmp_k);
		for(int i = num_bit; i > 0; i--) {
			ll l = 0, r = last;
			while(r - l > 1) {
				ll m = (l + r) >> 1;
				ll c;
				if((c = C(m, i)) < tmp_k) l = m;
				else r = m;
				//printf("C(%lld, %d) = %lld\n", m, i, c);
			}
			pos.push_back(l);
			last = l;
			tmp_k -= C(l, i);
		}
		
		int ans = 0;
		//printf("pos: ");
		//for(ll id : pos) printf("%lld ", id); puts("");
		for(ll id : pos) ans = add(ans, fpow(2, id));
		ans = add(ans, sub(fpow(2, r), fpow(2, num_zero + 1))); 
		printf("%d\n", ans); 
	}
	return 0;
} 
