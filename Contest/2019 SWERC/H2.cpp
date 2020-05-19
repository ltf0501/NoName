#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int line = 175147925;
const int cycle =91029304;

const int N = 350125310 - 1;
const int N1 = 100000000;
const int N2 = 200000000;
const int line1 = 50056830;
const int line2 = 100089173;

const int M = 182129209;
const int M1 = 100000000;
const int cycle1 = 49973217;
const int cycle2 = 99943309;

const ll  st = 1611516670ll;
const ll  st1 = 78802032994ll;
const ll  st2 = 565345893787ll;
const ll  mid = 516914ll;
const ll mid1 = 68635277779ll;
const ll mid2 = 501290018134ll;
vector<ll> v;
ll f(ll x) {
	constexpr ll mask = ((1ll << 40) - 1);
	return (x + (x >> 20) + 12345) & mask;
}
int main() {
	//ll now = mid;
	//int cnt = 0;
	//int even = 1;
	//while(true) {
	//	now = f(now);
	//	cnt++;
	//	if(cnt == M1 || cnt == M2) printf("even = %d, now = %lld\n", even, now);
	//	even += now & 1 ^ 1;
	//	if(cnt > 1000000000) break;
	//}
	ll n; scanf("%lld", &n);
	if(n == 0) return puts("0"), 0;
	n--;
	if(n <= N) {
		ll cnt = 0;
		ll now;
		if(n < M1) {
			cnt = 0;
			now = st;
		}
		else if(n < N2) {
			cnt = line1;
			now = st1;
			n -= N1;
		}
		else {
			cnt = line2;
			now = st2;
			n -= N2;
		}
		cnt += (now & 1) ^ 1;
		while(n--) {
			now = f(now);
			cnt += (now & 1) ^ 1;
		}
		printf("%lld\n", cnt);
	}
	else {
		ll cnt = line;
		n -= N + 1;
		cnt += 1LL * cycle * (n / M);
		n %= M;

		ll ccnt = 0, now;
		if(n < M1) {
			ccnt = 0;
			now = mid;
			//puts("A");
		}
		else {
			ccnt = cycle1;
			now = mid1;
			n -= M1;
			//puts("B");
		}
		ccnt += (now & 1) ^ 1;
		while(n--) {
			now = f(now);
			ccnt += (now & 1) ^ 1;
		}
		cnt += ccnt;
		printf("%lld\n", cnt);
	}
	return 0;
}
