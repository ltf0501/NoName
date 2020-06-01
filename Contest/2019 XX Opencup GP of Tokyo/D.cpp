#include <bits/stdc++.h> 
using namespace std;

typedef long long int ll;

bool ok(ll n, ll s, ll x, ll lim) {
	__int128 now = 0, l = 0, r = n;
	bool have = false;
	for (int i = 59; i >= 0; i--) if ((1LL << i) & lim) {
		if (x & (1LL << i)) {
			if (l == 0) {
				if (r & 1) {
					now += r * (1LL << i);
					if (r > 1) have = true;
				}
				else {
					now += (r - 1) * (1LL << i);
					r--;
					l++;
				}
			}
			else {
				if ((l + r) & 1) {
					now += (l + r) * (1LL << i);
					if (r > 1) have = true;
				}
				else if (r == 0) now += (l - 1) * (1LL << i);
				else {
					now += (l + r - 1) * (1LL << i);
					r--;
					l++;
				}
			}
		}
		else {
			if ((l + r) & 1) {
				now += (l + r - 1) * (1LL << i);
				if (r >= 1) {
					r--;
					l++;
				}
			}
			else {
				now += (l + r) * (1LL << i);
				if (r >= 1) have = true;
			}
		}
	}
	else {
		if (x & (1LL << i)) {
			if (l == 0) {
				if (have) {
					l += 2;
					r -= 2;
					now -= (1LL << i) * 3;
				}
				else return false;
			}
			else if (l & 1) now += l * (1LL << i);
			else now += (l - 1) * (1LL << i);
		}
		else {
			if (l & 1) now += (l - 1) * (1LL << i);
			else now += l * (1LL << i);
		}
	}
	return now >= s;
}


ll solve () {
	ll n, s, x, l, r, mid;
	scanf("%lld%lld%lld", &n, &s, &x);
	if (s < x || ((s - x) & 1)) return -1;
	if (s == 0) return 0;
	if (n == 1) {
		if (s == x) return x;
		else return -1;
	}
	if (n == 2) {
		vector<int> v;
		bool vis[65] = {};
		ll ans = 0;
		for(int i	= 0; i < 60; i++)
			if(x & (1LL << i)) vis[i] = 1, ans = 1LL << i;

		s -= x;
		for(int i = 1; i < 60; i++) if(s & (1LL << i)) {
			if(!i || vis[i - 1]) {
				return -1;
			}
			else ans += 1LL << (i - 1);
		}
		return ans;
	}
	else if (n == 3) {
		ll a = 0, b = 0, c = 0, now = s - x;
		auto ssort = [&]() {
			if (a > b) swap(a, b);
			if (b > c) swap(b, c);
			if (a > b) swap(a, b);
			return ;
		};
		for (int i = 59; i >= 0; i--) {
			ssort();
			if ((x & (1LL << i))) {
				if (now & (1LL << (i + 1))) {
					a += (1LL << i);
					b += (1LL << i);
					c += (1LL << i);
				}
				else a += (1LL << i);
			}
			else if (now & (1LL << (i + 1))) {
				b += (1LL << i);
				a += (1LL << i);
			}
		}
		return max({a, b, c});
	}
	l = 0, r = s;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (ok(n, s, x, mid)) r = mid;
		else l = mid;
	}
	return r;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) printf("%lld\n", solve());
} 
