#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int line = 175147925;
const int cycle =91029304;
const int kB[] = {int(5e7), int(1e8), int(1.5e8), int(2e8), int(2.5e8), int(3e8)};
const int SZ = 6;
const int N = 350125310;
const int N1 = 100000000;
const int N2 = 200000000;
const int line1 = 50056830;
const int line2 = 100089173;
const int Line[] = { 25031296, 50056830, 75074286, 100089173, 125100277, 150119936};
const ll St[] = { 325792323073ll, 78802032994ll, 11901289737ll, 565345893787ll, 143677078963ll, 29466792348ll};


const int M = 182129209;
const int M1 = 100000000;
const int M2 = 200000000;
const int cycle1 = 49973217;
const int cycle2 = 99943309;

const int Cycle[] = { 24980216, 49973217, 74980113, 99943309, 124938593, 149947231};
const ll Mid[] = { 288299158592ll, 68635277779ll, 9149398605ll, 501290018134ll, 126301526553ll, 24767364459ll };

const ll  st = 1611516670ll;
//const ll  st1 = 78802032994ll;
//const ll  st2 = 565345893787ll;
const ll  mid = 516914ll;
//const ll mid1 = 68635277779ll;
//const ll mid2 = 501290018134ll;
vector<ll> v;
ll f(ll x) {
	constexpr ll mask = ((1ll << 40) - 1);
	return (x + (x >> 20) + 12345) & mask;
}
int main() {
	//ll now = st;
	//int cnt = 0;
	//int even = 1;
	//vector<ll> e, val;
	//while(true) {
	//	now = f(now);
	//	cnt++;
	//	for(int	i = 0; i < 6; i++) if(cnt == kB[i]) {
	//		e.push_back(even);
	//		val.push_back(now);
	//		break;
	//	}
	//	//if(cnt == M1 || cnt == M2) printf("even = %d, now = %lld\n", even, now);
	//	even += now & 1 ^ 1;
	//	if(cnt > 500000000) break;
	//}
	//puts("even");
	//printf("{ ");
	//for(int x : e) printf("%d, ", x); puts("}");
	//puts("val");
	//printf("{ ");
	//for(ll x : val) printf("%lldll, ", x); puts("}");

	ll n; scanf("%lld", &n);
	if(!n) return puts("0"), 0;
	n--;
	if(n <= N) {
		ll cnt = 0;
		ll now;
		bool flag = 0;
		for(int i = 0; i < SZ; i++) if(n < kB[i]) {
			if(i == 0) {
				cnt = 0;
				now = st;
			}
			else {
				cnt = Line[i - 1];
				now = St[i - 1];
				n -= kB[i - 1];
			}
			flag = 1;
			break;
		}
		if(!flag) {
			cnt = Line[SZ - 1];
			now = St[SZ - 1];
			n -= kB[SZ - 1];
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
		n -= N;
		cnt += 1LL * cycle * (n / M);
		n %= M;

		ll ccnt = 0, now;
		bool flag = 0;
		for(int i = 0; i < SZ; i++) if(n < kB[i]) {
			if(i == 0) {
				ccnt = 0;
				now = mid;
			}
			else {
				ccnt = Cycle[i - 1];
				now = Mid[i - 1];
				n -= kB[i - 1];
			}
			flag = 1;
			break;
		}
		if(!flag) {
			ccnt = Cycle[SZ - 1];
			now = Mid[SZ - 1];
			n -= kB[SZ - 1];
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
